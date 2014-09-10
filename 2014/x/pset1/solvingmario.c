#include <cs50.h>
#include <stdio.h>

int main (void) {
int hash;
int height;
int space;
int nl;

height = GetInt();
for(nl = 0; nl < height + 1; nl++)
{
printf("\n");
printf("%d", nl);
for(space = height - 1 ; space >= nl ; space--) 
{
printf(" ");
printf("%d", space);
}
for(hash = height - nl ; hash < height + 2 ; hash++)
{
printf("#");
}
}
}
