# Function: Output input number's power

from math import pow

temp = eval(input())
if temp == int(temp):
    print(1, temp, temp*temp, temp*temp*temp, temp*temp*temp*temp, temp*temp*temp*temp*temp)
else:
    print(pow(temp, 0), pow(temp, 1), pow(temp, 2), pow(temp, 3), pow(temp, 4), pow(temp, 5))
