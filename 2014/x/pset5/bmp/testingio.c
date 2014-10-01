#include <stdio.h>
#include <cs50.h>

int main(void){
    char msg [] = "mdr";
    printf("%c",msg[1]);
	FILE* inputfile = fopen("hello.txt", "w");
	fprintf(inputfile,"Just testing... \n");
	printf("The size of integer is %zu\n", sizeof(int));
	fclose(inputfile);
}
