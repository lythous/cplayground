#include <stdio.h>
#include <stdlib.h>
#include <math.h>


unsigned long *findPrimesLessThan(unsigned long);
unsigned long pickFromSieve(unsigned long *, char*, unsigned long);
unsigned long countSieve(char*, unsigned long);
void printList(int *, int);
int sumOfPorperDivisors(int);
int findAbundantNumbersLessThan(int n, int **abundantNumbersAddress);
void sumOfAbundantNumbersPairs(char* sumList, int* abundantNumbers, int n, int count);
void printZeroCharList(char *list, int count) ;

unsigned long *primes;
int *abundantNumbers;

int main(void) {    
    int count;
	int n = 28123;
	int *abundantNumbers;
	char* sumList;
	sumList = calloc(2*n, sizeof(char));
	
	primes = findPrimesLessThan(n);
    count = findAbundantNumbersLessThan(n, &abundantNumbers);
	
	sumOfAbundantNumbersPairs(sumList, abundantNumbers, n, count);
    
	//printf("There are %d abundant numbers less than %d:\n",count, n);
	//printf("List of abundant numbers less than %d:\n", n);
	//printList(abundantNumbers, count);
	//printf("\nList of numbers which are not sum of two abundant numbers:\n", n);	
	printZeroCharList(sumList, n);
    
	free(primes);
    free(abundantNumbers);	
    return 0;
}

void sumOfAbundantNumbersPairs(char* sumList, int* abundantNumbers, int n, int count) {

	for(int i=0; i<count; i++) {
		for (int j=0; j<count; j++) {
			sumList[abundantNumbers[i]+abundantNumbers[j]] = 1;
		}
	}
}


int findAbundantNumbersLessThan(int n, int **abundantNumbersAddress) {
    
    int count = 0;
	*abundantNumbersAddress = calloc(0, sizeof(int));
    for (int i=1; i<n; i++) {
        if (sumOfPorperDivisors(i)>i){
			count++;
			*abundantNumbersAddress = realloc(*abundantNumbersAddress, count*sizeof(int));
            (*abundantNumbersAddress)[count-1] = i;
        }
    }
    return count;
}


int sumOfPorperDivisors(int n) {
    int i = 0;
    int j = 0;
    int sum = 1;
    int prod = 1;
    int n_org = n;
    
    while (n>=primes[i]) {
        while (n%primes[i]==0) {
            n /= primes[i];
            j++;
            prod += pow(primes[i], j);
        }
        sum *= prod;
        prod = 1;
        j = 0;
        i++;
    }
    return sum - n_org;
}


/*********************
/* Sieve of Sundaram *
**********************/

unsigned long *findPrimesLessThan(unsigned long n) {
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
    
    unsigned long count = countSieve(sieve, n);
    unsigned long *primes_ = (unsigned long *) malloc(count * sizeof(unsigned long));
    pickFromSieve(primes_, sieve, n);
    free(sieve);
    primes_[0] = 2;
    for (i = 1; i <= count; i++) {
        primes_[i] = 2*primes_[i] + 1;
    }        
    return primes_;     
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


void printList(int *list, int count) {
	int i;
    for (i = 0; i < count-1; i++) {
        printf("%lu, ", list[i]);
    }
	printf("%lu", list[i]);
}

void printZeroCharList(char *list, int count) {
	int i;
	long sum = 0;
    for (i = 0; i < count; i++) {
		if (list[i] == 0) {
			//printf("%d, ", i);
			sum += i;
		}
    }
	printf("\n Sum = %lu", sum);
}
