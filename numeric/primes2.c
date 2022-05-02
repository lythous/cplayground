#include <stdio.h>
#include <stdlib.h>

unsigned long *findPrimesLessThan(unsigned long, unsigned long*);
int isDivisbleBy(unsigned long, unsigned long*, unsigned long);
void printList(unsigned long *, unsigned long);
unsigned long pickFromSieve(unsigned long *, char*, unsigned long);
unsigned long countSieve(char*, unsigned long);

int main(void) {
    unsigned long count = 0;
    unsigned long *primes = findPrimesLessThan(10000000, &count);
    //printList(primes, count);
    printf("%lu", count);
    free(primes);
    return 0;
}

unsigned long *findPrimesLessThan(unsigned long n, unsigned long* count) {
    char *sieve = (char*) malloc(n*sizeof(char)); 
    unsigned long i, j;
    
    for (i = 0; i<n; i++) sieve[i] = 1;
    sieve[0] = 0;
    sieve[1] = 0;
    
    for (i = 2; i < n; i++) {
        if (sieve[i] != 0) {
            for (j=i*i; j < n; j += i) {
                sieve[j] = 0;
            }
        }
    }
    *count = countSieve(sieve, n);
    unsigned long *primes = (unsigned long *) malloc(*count * sizeof(unsigned long));
    pickFromSieve(primes, sieve, n);
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
