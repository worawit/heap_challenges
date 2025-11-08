#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// gets() is deprecrated. since glibc 2.16, glibc header files don't expose the function declaration
extern char *gets(char *s);

// 1st arg: input
// 2nd arg: result
typedef void (*work_fn)(void*, char*);

typedef struct Worker {
    work_fn fn;
    char result[64];
} Worker;

Worker* new_worker()
{
    Worker* worker = (Worker*) malloc(sizeof(Worker));
    worker->fn = (work_fn)strcpy;
    return worker;
}

void worker_run(Worker* worker, void* input)
{
    worker->fn(worker->result, input);
}

int main()
{
    printf("system address: %p\n", system);

    char* name = (char*) malloc(64);
    Worker* worker = new_worker();

    printf("name address: %p\n", name);
    printf("worker address: %p\n", worker);

    printf("Enter your name: ");
    fflush(stdout);
    gets(name);
    worker_run(worker, name);
    printf("Hello %s\n", worker->result);

    free(worker);
    free(name);
    return 0;
}
