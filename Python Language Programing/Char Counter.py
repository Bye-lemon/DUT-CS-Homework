# ChapCounter

def count_letter(str, ch):
    count = 0
    for char in str:
        if char == ch:
            count += 1
    return count

string=input()
char=input()
print(count_letter(string,char))
