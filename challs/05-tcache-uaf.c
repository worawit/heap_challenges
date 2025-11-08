#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NOTE_SIZE 0x20
static char *g_note;

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
