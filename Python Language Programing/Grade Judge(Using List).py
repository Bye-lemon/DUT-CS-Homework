# Grade

n = eval(input())
if n < 0:
    print('ERROR')
else:
    list = []
    counter = 0
    passer = 0
    failer = 0
    for i in range(n):
        ioin = eval(input())
        if ioin < 0 or ioin > 100:
            break
        list.append(ioin)
        counter += 1
        if ioin >= 60:
            passer += 1
        else:
            failer += 1
    print(list)
    print(counter)
    print("及格 {}\n不及格 {}".format(passer, failer))
