#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NOTE_SIZE 0x20
static char *g_note;

static void disable_tcache()
{
    // use large size to make it to unsorted bin when free (for getting address in main_arena struct)
    size_t* first = (size_t*) malloc(1234);
	// need second chunk to prevent first chunk get merged into top
	char* second = (char*) malloc(1122);

	free(first);
	// first_chunk->fd points to main_arena.bins[0]
	size_t* pi = (size_t*) first[0];
	do {
	    // search from tcache_bins, tcache_max_bytes and tcache_cnt
		if (pi[0] == 0x40 && pi[1] == 0x408 && pi[2] == 0x7 && pi[3] == 0) {
		    // found malloc_par, set tcache_bins and tcache_cnt to disable tcache
			pi[0] = 0; // tcache_bins
			pi[2] = 0; // tcache_cnt
            break;
        }
	} while (--pi);

	// after finding all needed malloc struct, clear allocated chunk
    // below free will merge backward (first) and top
    // so, after this free, the heap will be the same as start of function
	free(second);
}

void shell()
{
    puts("Executing shell...");
    char *argv[] = { "/bin/sh", NULL };
    execve(argv[0], argv , NULL);
}

static int read_int()
{
    char buf[16];
    fgets(buf, sizeof(buf), stdin);
    return (int)strtoul(buf, NULL, 0);
}

static void menu()
{
	printf("Menu\n");
	printf("1. Create Note\n");
	printf("2. Read Note\n");
	printf("3. Update Note\n");
	printf("4. Delete Note\n");
	printf("Choice: ");
	fflush(stdout);
}

int main()
{
    disable_tcache();
    printf("shell address: %p\n", shell);
    int op = 0;
    printf("op address: %p\n", &op);
    while (op != -1) {
        menu();
        op = read_int();

        switch (op) {
            case 1:
                g_note = (char*) malloc(NOTE_SIZE);
                break;
            case 2:
                puts(g_note);
                break;
            case 3:
                fgets(g_note, NOTE_SIZE, stdin);
                break;
            case 4:
                free(g_note);
                break;
            default:
                op = -1;
                break;
        }
    }

    return 0;
}
