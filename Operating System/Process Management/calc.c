#include "unistd.h"
#include "string.h"

#define LENS 10

int main(int argc, char *argv[]) {
	char *para1, *para2, *para3;
	char *exp;

	para1 = (char*)malloc(sizeof(char) * 4 * LENS);
	para2 = (char*)malloc(sizeof(char) * 4 * LENS);
	para3 = (char*)malloc(sizeof(char) * 4 * LENS);
	exp = (char*)malloc(sizeof(char) * 4 * LENS);

	if (2 != argc) {
		printf("Usage: ./call <expression>\n");
		printf("Note:  Support max, min with 2 integer and average with 3 integer.\n");
		printf("e.g.   ./call \"min(3, 8)\"\n");
	}
	strcpy(exp, argv[1]);
	switch (argv[1][1]) {
		case 'a':
			// max
			para1 = strtok(argv[1], "(");
			para1 = strtok(NULL, "(");
			para2 = strtok(para1, ",");
			para2 = strtok(NULL, ")");
			printf("%s=%d", exp, (atoi(para1) > atoi(para2))? atoi(para1): atoi(para2));
			break;
		case 'i':
			// min
			para1 = strtok(argv[1], "(");
			para1 = strtok(NULL, "(");
			para2 = strtok(para1, ",");
			para2 = strtok(NULL, ")");
			printf("%s=%d", exp, (atoi(para1) < atoi(para2))? atoi(para1): atoi(para2));
			break;
		case 'v':
			// average
			para1 = strtok(argv[1], "(");
			para1 = strtok(NULL, "(");
			para2 = strtok(para1, ",");
			para2 = strtok(NULL, ",");
			para3 = strtok(NULL, ",");
			para3 = strtok(para3, ")");
			printf("%s=%.2f", exp, (atoi(para1) + atoi(para2) + atoi(para3))/3.0);
			break;
		default:
			printf("Usage: ./call <expression>\n");
			printf("Note:  Support max, min with 2 integer and average with 3 integer.\n");
			printf("e.g.   ./call \"min(3, 8)\"\n");
			break;
	}

	return 0;
}
