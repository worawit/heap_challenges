#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1st arg: input
typedef void (*work_fn)(char*);

typedef struct Worker {
    work_fn fn;
    char data[64];
} Worker;

static int read_int()
{
    char buf[16];
    fgets(buf, sizeof(buf), stdin);
    return (int)strtoul(buf, NULL, 0);
}

static void menu()
{
	printf("Menu\n");
	printf("1. Use\n");
	printf("2. Allocate\n");
	printf("3. Free\n");
	printf("Choice: ");
	fflush(stdout);
}

int main()
{
    printf("system address: %p\n", system);

    Worker* worker = (Worker*) malloc(sizeof(Worker));
    worker->fn = (work_fn)puts;
    strcpy(worker->data, "Hello");

    printf("worker address: %p\n", worker);

    int op = 0;
    while (op != -1) {
        menu();
        op = read_int();

        switch (op) {
            case 1:
                worker->fn(worker->data);
                break;
            case 2:
                int len = read_int();
                char* data = (char*) malloc(len);
                fgets(data, len, stdin);
                break;
            case 3:
                free(worker);
                break;
            default:
                op = -1;
                break;
        }
    }

    return 0;
}
