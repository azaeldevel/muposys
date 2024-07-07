
#include <stdio.h>

int main(int argc, char *argv[])
{
    int number = 0;
    scanf("%i", &number);

    number++;

    printf("Content-type: text/html\n\n");
    printf("%i",number);

	return 0;
}
