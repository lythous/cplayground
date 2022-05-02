#include <stdio.h>
#include <stdlib.h>

unsigned long* prime(unsigned long, unsigned long*);
int isDivisbleBy(unsigned long, unsigned long*, unsigned long);
void printList(unsigned long*, unsigned long);

int main(void) {
  unsigned long c = 0;
	unsigned long *p = prime(1000000, &c);
	
	printf("%lu\n", c);
	printf("%lu\n", p[999]);
	return 0;
}

unsigned long* prime(unsigned long n, unsigned long* c) {
  unsigned long *primes = malloc(1*sizeof(unsigned long));
  primes[0] = 2;	
  unsigned long count = 1;
	unsigned long i;
	
	for (i = 2; i<n; i++) {
		if (!isDivisbleBy(i, primes, count)) {
			count++;
			primes = realloc(primes, count*sizeof(unsigned long));
			primes[count-1] = i;
		}
	}
	*c = count;
  // need free()
  return primes;     
}

int isDivisbleBy(unsigned long n, unsigned long *list, unsigned long count) {
	for (unsigned long i = 0; i < count; i++) {
		if (n%list[i] == 0) return 1;
	}
	return 0;
}

void printList(unsigned long *list, unsigned long count) {
	unsigned long i;
	for (i = 0; i < count - 1; i++) {
		printf("%lu, ", list[i]);
	}
	printf("%lu\n", list[i]);
}
