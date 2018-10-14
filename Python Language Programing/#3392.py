# PrintMultis

for row in range(1, 10):
    for col in range(1, row+1):
        print("{}*{}={}".format(col, row, row*col), end=' ')
    print('\n')
