#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

static void init_random()
{
	int fd = open("/dev/urandom", O_RDONLY);
	unsigned int seed;
	read(fd, &seed, sizeof(seed));
	srand(seed);
	close(fd);
}

int main()
{
	init_random();
	// no buffer. so, no need flushing
	setvbuf(stdout, NULL, _IONBF, 0);

	puts("Answer the value of chunk size field of allocating size 5 times");
	char buf[16];
	for (int i = 0; i < 5; i++) {
		int sz = rand() % 0x200;
		printf("[%d/5] Allocating size %#x, chunk->size value is: ", i, sz);
		fgets(buf, sizeof(buf), stdin);
		int answer = strtoul(buf, NULL, 0);
		printf("  Your answer is: %#x,   ", answer);

		size_t* p1 = malloc(sz);
		int chunk_size = (int)p1[-1];
		if (chunk_size != answer) {
			printf("Wrong!!!, correct answer is %#x\n", chunk_size);
			exit(1);
		}

		printf("Correct\n");
	}

	puts("\nCongratulations... You wins.");
	return 0;
}
