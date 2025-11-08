#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	void* p1 = malloc(0x48);
	void* p2 = malloc(0x38);
	void* p3 = malloc(0x58);
	printf("p1: %p\n", p1);
	printf("p2: %p\n", p2);
	printf("p3: %p\n", p3);

	size_t len = ((size_t)p3) - ((size_t)p1);
	printf("Data length: %ld\n", len);
	printf("Your data: ");
	fflush(stdout);
	if (read(0, p1, len) != len) {
		puts("not enough data");
		return -1;
	}

	puts("freeing p1");
	free(p1);
	puts("freeing p2");
	free(p2);
	puts("freeing p3");
	free(p3);

	puts("\nCongratulations... You wins.");
	return 0;
}
