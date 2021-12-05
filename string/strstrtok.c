#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char *strstrtok(char **str, const char *delimiter){
    char *pch1 = strstr(*str, delimiter);
    if (pch1!=NULL) {
        char *pch2;
        pch2 = *str;
        *pch1 = '\0';
        *str = pch1 + strlen(delimiter);
        return pch2;
    }
    else return *str;
}


int main()
{
    char *str = malloc(sizeof(char)*64);
    strcpy(str, "a{break}b{break}c");
    const char *delimiter = "{break}";
    char *find;

    while (find!=str) {
        find = strstrtok(&str, delimiter);
        printf("%s\n", find);
    }
    return 0;
}

/* OUTPUT:
 * a
 * b
 * c
 */
