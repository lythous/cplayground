#include <stdio.h>
#include <stdlib.h>

char* prime(unsigned long, unsigned long*);
int isDivisbleBy(unsigned long, unsigned long*, unsigned long);
void printList(char*, unsigned long);

int main(void) {
  unsigned long c = 0;
	char *p = prime(10, &c);

	printList(p, 10);
	return 0;
}

char* prime(unsigned long n, unsigned long* c) {
  char *primes = malloc(n*sizeof(char));	
  unsigned long count = 1;
	unsigned long i, j;
	
	for (i = 0; i<n; i++) primes[i] = 1;
	primes[0] = 0;
	primes[1] = 0;
	
	for (i = 2; i < n; i++) {
		if (primes[i] != 0) {
			for (j=2*i; j < n; j += i) {
				primes[j] = 0;
			}
		}
	}
	*c = count;
  return primes;     
}

int isDivisbleBy(unsigned long n, unsigned long *list, unsigned long count) {
	for (unsigned long i = 0; i < count; i++) {
		if (n%list[i] == 0) return 1;
	}
	return 0;
}

void printList(char *list, unsigned long count) {
	unsigned long i;
	for (i = 0; i < count - 1; i++) {
		printf("%lu, ", list[i]);
	}
  printf("%lu\n", list[i]);
}
