# DayDayUp

n = eval(input())
up = pow(n/1000+1, 365)
down = pow(1-n/1000, 365)
rate = int(up // down)
print("{:.2f},{:.2f},{}".format(up, down, rate))
