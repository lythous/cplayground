#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
 * Find string between two strings limits:
 * Source string will not change.
 * If start_limit = "": 	result = from start to end_limit
 * If end_limit = "": 		result = from start_limit to end 
 */
void limit_str_limit(const char *src, const char *start_limit, const char *end_limit, char **res) {
    char *pch_s, *pch_e;
    pch_s = strstr(src, start_limit);
    if (pch_s!=NULL) {
        if (*end_limit!=0){
            pch_e = strstr(pch_s, end_limit);
            if (pch_e!=NULL) {
                size_t len_s = strlen(start_limit);
                strncpy(*res, pch_s+len_s, pch_e-pch_s-len_s);
            }
        } 
        else {
            size_t len_s = strlen(start_limit);
            strcpy(*res, pch_s+len_s);      
        }
    } 
}

void example(void) {
	char *str = malloc(sizeof(char)*64);
	char *A = malloc(sizeof(char)*64);
	char *B = malloc(sizeof(char)*64);
	char *other = malloc(sizeof(char)*64);
	strcpy(str, "AA:=BB<-CDEF");
	
	limit_str_limit(str, "", ":=", &A);
	limit_str_limit(str, ":=", "<-", &B);
	limit_str_limit(str, "<-", "", &other);
	printf("%s\n", A);
	printf("%s\n", B);
	printf("%s\n", other);
	
	free(str), free(A), free(B), free(other);
}

/* OUTPUT:
 * AA
 * BB
 * CDEF
 */

int main(void) {
	example();
    return 0;
}

