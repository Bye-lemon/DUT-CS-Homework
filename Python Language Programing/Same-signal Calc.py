# CalcWiththeSameSignal

n = eval(input())
abs = abs(n)
plus = abs + 10
sub = abs - 10
times = abs * 10
print (abs, plus if plus*n >= 0 else -plus, sub if sub*n > 0 else -sub, times if times*n >= 0 else -times)
