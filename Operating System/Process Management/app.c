#include "unistd.h"
#include "string.h"

int main(void) {
    char exp[40], para[40];
    int i;

    printf("Meta Info:  This is a sample for exec function family.\n");
	printf("            Support max, min with 2 integer and average with 3 integer.\n");
	printf("e.g.        min(3, 8)\n");
    while (1) {
        printf("Please enter an expression or press q to exit.\n");
        scanf("%s", exp);
        if ('q' == exp[0]) {
            break;
        } else {
            para[0] = '\"';
            for (i = 0; exp[i] != '\0'; i ++)
                para[i + 1] = exp[i];
            para[i + 1] = '\"';
            execl((char *)"/home/public/call", (char *)"./call", (char *)exp, NULL);
            perror("Failed to create calculate process.\n");
        }
    }

    return 0;
}
