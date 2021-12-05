#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


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


char *strstrtokmul(char **str, ...) {
	va_list delimiters_list;
	va_start(delimiters_list, **str);
	
	char *delimiter;
	char *srchres;
	delimiter = va_arg(delimiters_list, char *);
	/* Last argument must be 0 */
	while (delimiter!=0) {
		srchres = strstrtok(str, delimiter);
		
		if (srchres!=*str) {
			return srchres;
		}
		delimiter = va_arg(delimiters_list, char *);
	}
	va_end(delimiters_list);
	return *str;
}


int main(void) {
	char *str = malloc(sizeof(char)*64);
	char *func_name;
	strcpy(str, "tan == sin/cos");	
	
	func_name = strstrtokmul(&str, "<=", "<-", "==", 0);
	printf("func_name: %s\n", func_name);
	
	free(str);
    return 0;
}

/* OUTPUT:
 * func_name: tan
 */
