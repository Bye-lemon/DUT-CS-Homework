from flask import Flask, request, render_template
import json
from DBModel import db, Users, Boxes, Powerbars

app = Flask(__name__)

app.config['SQLALCHEMY_DATABASE_URI'] = 'mysql+pymysql://root:password@140.143.186.223:3306/GeZhiSpace'
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = True

db.init_app(app)

url = 'http://127.0.0.1:5000'


# 处理页面推送请求
@app.route('/')
def sign_in():
    return render_template("login.html", judgeLoginPath=url + '/login', registerPath=url + '/signUpPage')


@app.route('/main')
def main_function(user=None):
    if request.values:
        id = int(request.values.get('id'))
        user = Users.query.get(id)
    return render_template("main.html", user=user, rentPath=url + '/rent', backPath=url + '/back')


@app.route('/signUpPage')
def sign_up_page():
    return render_template("signup.html", judgeSignUpPath=url + '/signUp', loginPath=url)


@app.route('/CreateQRCode')
def code():
    id = str(request.values.get('student_id'))
    box_id = str(request.values.get('box_id'))
    box = Boxes.query.get(int(box_id))
    box.isEmpty = 1
    box.usedPerson = int(id)
    if box.isWanted and box.wantedPerson == id:
        box.isWanted = 0
        box.wantedPerson = 0
    db.session.commit()
    content = json.dumps([{'id': id, 'box_id': box_id, 'action': 'rent'}])
    img_url = 'http://qr.liantu.com/api.php?text=' + content
    return render_template("qrcode.html", imgpath=img_url, backUrl=url + '/rent?student_id=' + id)


@app.route('/powerControl')
def power_bar_control():
    id = int(request.values.get('student_id'))
    pb_id = int(request.values.get('power_bar_id'))
    connect = int(request.values.get('connect'))
    pb = Powerbars.query.get(pb_id)
    pb.isUsed = connect
    if connect:
        pb.usedPerson = id
    else:
        pb.usedPerson = 0
    db.session.commit()
    return render_template('tips.html', content='操作成功！', backUrl=url + '/rent?student_id=' + str(id))


@app.route('/orderControl')
def order_box_control():
    id = int(request.values.get('student_id'))
    box_id = int(request.values.get('box_id'))
    control = int(request.values.get('control'))
    box = Boxes.query.get(box_id)
    box.isWanted = control
    if control:
        box.wantedPerson = id
    else:
        box.wantedPerson = 0
    db.session.commit()
    if control:
        return render_template('tips.html', content='操作成功！', backUrl=url + '/rent?student_id=' + str(id))
    else:
        return render_template('tips.html', content='操作成功！', backUrl=url + '/back?student_id=' + str(id))


@app.route('/back')
def back_tool_page():
    id = int(request.values.get('student_id'))
    user = Users.query.get(id)
    boxes = Boxes.query.filter(Boxes.usedPerson == id).all()
    boxes_od = Boxes.query.filter(Boxes.wantedPerson == id).all()
    return render_template('back.html', user=user, boxes=boxes, boxes_od=boxes_od, backQRCodePath=url + '/backQRCode',
                           cancelOrderPath=url + '/orderControl', mainUrl=url + '/main?id=' + str(id))


@app.route('/backQRCode')
def back_code():
    id = str(request.values.get('student_id'))
    box_id = str(request.values.get('box_id'))
    box = Boxes.query.get(int(box_id))
    box.isEmpty = 0
    box.usedPerson = 0
    db.session.commit()
    content = json.dumps([{'id': id, 'box_id': box_id, 'action': 'back'}])
    img_url = 'http://qr.liantu.com/api.php?text=' + content
    return render_template("qrcode.html", imgpath=img_url, backUrl=url + '/back?student_id=' + id)


@app.route('/signUp', methods=["POST"])
def signup():
    id = int(request.form['id'])
    pwd = request.form['password']
    name = request.form['name']
    phnum = request.form['phonenumber']
    user = Users(id, name, pwd, phnum)
    db.session.add(user)
    db.session.commit()
    return render_template('tips.html', content='注册成功', backUrl=url)


@app.route('/login', methods=["POST"])
def login():
    id = int(request.form['id'])
    pwd = request.form['password']
    user = Users.query.get(id)
    password = user.password
    if not pwd == password:
        return render_template('tips.html', content='您输入的学号或密码不正确，请返回上一页重新输入。', backUrl=url)
    else:
        html = main_function(user)
        return html


@app.route('/rent', methods=["GET"])
def all_box_query():
    boxes = Boxes.query.all()
    powerbars = Powerbars.query.all()
    id = int(request.values.get('student_id'))
    user = Users.query.get(id)
    return render_template("rent.html", user=user, boxes=boxes, powerbars=powerbars, QRCodePath=url + '/CreateQRCode',
                           orderPath=url + '/orderControl', powerPath=url + '/powerControl',
                           mainUrl=url + '/main?id=' + str(id))


# 单片机访问接口
@app.route('/thisPersonIsAllowed/<int:student_id>', methods=["GET"])
def gate_forbidden_system_judge(student_id):
    user = Users.query.get(student_id)
    if user:
        return '1'
    else:
        return '0'


@app.route('/thisPowerbarIsNeededToUsed/<int:power_bar_id>', methods=["GET"])
def power_bar_query_proxy(power_bar_id):
    power_bar = Powerbars.query.get(power_bar_id)
    if power_bar.isUsed:
        return '1'
    else:
        return '0'


@app.route('/thisPersonOpenThisBoxIsAllowed', methods=["POST"])
def box_gate_forbidden_judge():
    return '1'
    # 现有逻辑无需使用此接口


if __name__ == '__main__':
    app.run()
