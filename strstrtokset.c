#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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


char *strstrtokset(char **str, const char *delimiters[], int len) {
	char *srchres;
	for(int i=0; i<len; i++) {
		srchres = strstrtok(str, delimiters[i]);
		if (srchres!=*str) {
			return srchres;
		}
	}
	return *str;
}


int main(void) {
	char *str = malloc(sizeof(char)*64);
	const char *delimiters_set[] = {"<-", "==", "<<"};
	unsigned int delimiters_set_size = 3;
	char *func_name;
	
	strcpy(str, "tan == sin/cos");	
	func_name = strstrtokset(&str, delimiters_set, delimiters_set_size);
	printf("func_name: %s\n", func_name);

	strcpy(str, "tan << sin/cos");
	func_name = strstrtokset(&str, delimiters_set, delimiters_set_size);
	printf("func_name: %s\n", func_name);
	
	strcpy(str, "tan <- sin/cos");
	func_name = strstrtokset(&str, delimiters_set, delimiters_set_size);
	printf("func_name: %s\n", func_name);	
	
	free(str);
    return 0;
}

/* OUTPUT:
 * func_name: tan
 * func_name: tan
 * func_name: tan
 */
