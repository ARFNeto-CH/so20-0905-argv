#include <stdio.h>
int main(void)
{
    char    sub_str[10][20];

    for (int i = 0; i < 10; i += 1)
        sprintf(
            sub_str[i],
            "%16s%03d",
            "This is string ", i+1
        );

    for (int i = 0; i < 10; i += 1)
        printf(
            "%2d  %s len(%zd)\n",
            i, sub_str[i], strlen(sub_str[i])
        );
    return 0;
};
