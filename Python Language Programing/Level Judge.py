# GradeLevelJudge

grade = eval(input())
if grade < 0 or grade > 100:
    print('ERROR')
elif grade > 90 and grade <= 100:
    print('A')
elif grade > 80:
    print('B')
elif grade > 70:
    print('C')
elif grade > 60:
    print('D')
else:
    print('E')
