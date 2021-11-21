#include <stdio.h>
#include <limits.h>

void print_binray(unsigned long long n);

int main(void) {
	unsigned long long n;
	print_binray(ULLONG_MAX);
	while (1) {
		printf("Enter a number: ");
		scanf("%llu", &n);
		print_binray(n);
	}

}

void print_binray(unsigned long long n) {
	for(int i=8*sizeof(n); i; i--) {
		if (1ULL<<(i-1) & n) printf("1");
		else printf("0");
	}
	
	printf("\n");
}
