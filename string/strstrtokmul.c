#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


/* strstrtok gets a string pointer and and a string delimiter and returns delimited string as output */
/* and change input string pointer to point after delimited text. */
/* Example:     *str = "salambarali; delimiter="bar"; */
/*              ==> Output="salam"; *str = "ali";*/
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


/*
 * strstrtokmul takes an string and tokenize it by arbitrary number of delimiters (string type)
 */
char *strstrtokmul(char **pstr, ...) {
	va_list delimiters_list;
	va_start(delimiters_list, pstr); /* ?? pstr or **pstr ?? */
	
	char *delimiter;
	char *srchres;
	delimiter = va_arg(delimiters_list, char *);
	/* Last argument must be 0 */
	while (delimiter!=0) {
		srchres = strstrtok(pstr, delimiter);
		
		if (srchres!=*pstr) {
			return srchres;
		}
		delimiter = va_arg(delimiters_list, char *);
	}
	va_end(delimiters_list);
	return *pstr;
}


void example() {
    char *str = malloc(sizeof(char)*64);
	char *str_orig = str;
	char *func_name;
	strcpy(str, "tan == sin/cos");	
	
	func_name = strstrtokmul(&str, "<=", "<-", "==", 0);
	printf("func_name: %s\n", func_name);
	
	free(str_orig);
}

/* OUTPUT:
 * func_name: tan
 */

int main(void) {
	example();
    return 0;
}
