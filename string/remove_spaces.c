#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_spaces(char* str) {
    char *fw = str;
    while (*fw) {
        while(*fw==' '){
			fw++;
        }
        *str = *fw;
		str++;
		fw++;
    }
}
int main(void) {
    char *ex = malloc(sizeof(char)*64);
	strcpy(ex, "   S A  LAM   \n s d ! $ \n \0");
	remove_spaces(ex);
	printf("{%s}\n", ex);
	free(ex);
    return 0;
}
