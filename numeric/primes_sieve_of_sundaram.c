#include <stdio.h>
#include <stdlib.h>
#include <math.h>


unsigned long *findPrimesLessThan(unsigned long, unsigned long*);
int isDivisbleBy(unsigned long, unsigned long*, unsigned long);
void printList(unsigned long *, unsigned long);
unsigned long pickFromSieve(unsigned long *, char*, unsigned long);
unsigned long countSieve(char*, unsigned long);


int main(void) {
    unsigned long count;
    unsigned long *primes = findPrimesLessThan(1000000000, &count);
    printList(primes, count);
    printf("%lu", count);
    free(primes);
    return 0;
}


/*********************
/* Sieve of Sundaram *
**********************/
unsigned long *findPrimesLessThan(unsigned long n, unsigned long* count) {
    unsigned long i, j, k;
    k = (unsigned long) (n-1) / 2;
    char *sieve = (char*) malloc((k+1)*sizeof(char)); 
    
    for (i = 0; i < k+1; i++) sieve[i] = 1;
    
    for (i = 1; i < (unsigned long)sqrt(k) + 1; i++) {
        j = i;
        while (i+j+2*i*j <= k) {
            sieve[i+j+2*i*j] = 0;
            j++;
        }
    }
    
    *count = countSieve(sieve, n);
    unsigned long *primes = (unsigned long *) malloc(*count * sizeof(unsigned long));
    pickFromSieve(primes, sieve, n);
    primes[0] = 2;
    for (i = 1; i <= *count; i++) {
        primes[i] = 2*primes[i] + 1;
    }        
    return primes;     
}


unsigned long pickFromSieve(unsigned long *primes, char* sieve, unsigned long totalN) {
    unsigned long count = 0;
    
    for (unsigned long i = 0; i < totalN; i++) {
        if (sieve[i]==1) {
            primes[count] = i;
            count++;
        }
    }
    
    return count;
}


unsigned long countSieve(char* sieve, unsigned long totalN) {
    unsigned long count = 0;
    
    for (unsigned long i = 0; i < totalN; i++) {
        if (sieve[i]==1) {
            count++;
        }
    }
    
    return count;
}


void printList(unsigned long *list, unsigned long count) {
    unsigned long i;
    
    for (i = 0; i < count - 1; i++) {
        printf("%lu, ", list[i]);
    }
    
  printf("%lu\n", list[i]);
}
