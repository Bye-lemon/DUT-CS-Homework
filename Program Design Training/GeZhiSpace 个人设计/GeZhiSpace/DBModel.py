from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from flask_script import Manager

app = Flask(__name__)

app.config['SQLALCHEMY_DATABASE_URI'] = 'mysql+pymysql://root:password@140.143.186.223:3306/GeZhiSpace'
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = True

db = SQLAlchemy(app)
manager = Manager(app)


class Users(db.Model):
    __tablename__ = 'users'
    name = db.Column(db.String(100), unique=False)
    id = db.Column(db.Integer, primary_key=True)
    password = db.Column(db.String(100), unique=False)
    phoneNumber = db.Column(db.VARCHAR(20), unique=False)
    isAllowed = db.Column(db.Integer, unique=False)

    def __init__(self, id, name, password, phoneNumber):
        self.name = name
        self.id = id
        self.password = password
        self.phoneNumber = phoneNumber
        self.isAllowed = 0  # 管理员审核是否可以批准

    def __repr__(self):
        return '<User %r>' % self.id


class Boxes(db.Model):
    __tablename__ = 'boxes'
    id = db.Column(db.Integer, primary_key=True)
    isEmpty = db.Column(db.Integer, unique=False)
    isWanted = db.Column(db.Integer, unique=False)
    usedPerson = db.Column(db.Integer, unique=False)
    wantedPerson = db.Column(db.Integer, unique=False)

    def __init__(self, id):
        self.id = id
        self.isEmpty = 0
        self.isWanted = 0
        self.usedPerson = 0
        self.wantedPerson = 0

    def __repr__(self):
        return '<Box %r>' % self.id


class Powerbars(db.Model):
    __tablename__ = 'powerbars'
    id = db.Column(db.Integer, primary_key=True)
    isUsed = db.Column(db.Integer, unique=False)
    usedPerson = db.Column(db.Integer, unique=False)

    def __init__(self, id):
        self.id = id
        self.isUsed = 0
        self.usedPerson = 0

    def __repr__(self):
        return '<PowerBar %r>' % self.id


if __name__ == '__main__':
    manager.run()
