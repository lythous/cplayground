#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/* strstrtok gets a string pointer and and a string delimiter and returns delimited string as output */
/* and change input string pointer to point after delimited text. */
/* Example:     *str = "salambarali; delimiter="bar"; */
/*              ==> Output="salam"; *str = "ali"; */
char *strstrtok(char **pstr, const char *delimiter){
    char *pch1 = strstr(*pstr, delimiter);
    if (pch1!=NULL) {
        char *pch2;
        pch2 = *pstr;
        *pch1 = '\0';
        *pstr = pch1 + strlen(delimiter);
        return pch2;
    }
    else return *pstr;   /* If delimiter not found in input string => output is the same as input. */
}


void example() {
    char *str = malloc(sizeof(char)*64);
    strcpy(str, "a{break}b{break}c");
    const char *delimiter = "{break}";
    char *find;

    while (find!=str) {
        find = strstrtok(&str, delimiter);
        printf("%s\n", find);
    }
}
/* OUTPUT:
 * a
 * b
 * c
 */



int main()
{
    example();
    return 0;
}
