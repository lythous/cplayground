#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_chars(char *, const char *);
void remove_char(char *, const char);
void remove_wspaces(char *);

/* Remove multiple chars (each treated as a single char) from input string */
void remove_chars(char *str, const char *rmvchars) {
    while (*rmvchars!='\0') {
    	remove_char(str, *rmvchars);
    	rmvchars++;
    }
}

/* Remove single char from input string */
void remove_char(char *str, const char rmvchar) {
    char *fw = str;
    while (*fw) {
        while(*fw==rmvchar){
			fw++;
        }
        *str = *fw;
		str++;
		fw++;
    }
    *str = '\0';
}

/* Remove whitespaces from input string */
void remove_wspaces(char *str) {
    remove_chars(str, " \t\n\v\f\r");
}

void example() {
    char *ex = malloc(sizeof(char)*64);
	strcpy(ex, " ^^  ^ M#S M^$# # $$ $#@ a\n \t s");
    printf("{%s}\n", ex);
    //remove_char(ex, ' ');
	//remove_chars(ex, " \n#^$@");
    remove_wspaces(ex);
	printf("{%s}\n", ex);
	free(ex);

}


int main(void) {
    example();
    return 0;
}
