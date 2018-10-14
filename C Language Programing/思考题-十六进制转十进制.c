#include <stdio.h>
#include <math.h>

char old_char [80];
int new_int [80];

int main (void)
{
    int store = 0,i;
    long sum = 0;
    printf ("Please input a string.\n");
    gets (old_char);

    for (i = 0;old_char [i] != '\0';i ++)
    {
        if (old_char [i] <= '9' && old_char [i] >= '0')
        {
            new_int [store] = old_char [i] - 48;
            store ++;
        }
        else if (old_char [i] <= 'f' && old_char [i] >= 'a')
        {
            new_int [store] = old_char [i] - 87;
            store ++;
        }
        else if (old_char [i] <= 'F' && old_char [i] >= 'A')
        {
            new_int [store] = old_char [i] - 55;
            store ++;
        }
    }
    store --;
    for (i = 0;i <= store;i ++)
        sum += new_int [i] * pow (16,store - i);
    printf ("\n%ld",sum);

    return 0;
}

