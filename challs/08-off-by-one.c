#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct Note {
    int cap;
    int nuse;
    char data[0];
} Note;

#define MAX_NOTE 64
static Note *notes[MAX_NOTE];

static int read_int()
{
    char buf[16];
    fgets(buf, sizeof(buf), stdin);
    return (int)strtoul(buf, NULL, 0);
}

static int read_line(char *buf, size_t size)
{
    fgets(buf, size, stdin);
    int len = (int) strlen(buf);
    // remove last newline from fgets
    if (buf[len - 1] == '\n') {
        buf[len - 1] = '\0';
        len--;
    }

    return len;
}

static int find_free_index()
{
    for (int i = 0; i < MAX_NOTE; i++) {
        if (notes[i] == NULL)
            return i;
    }

    return -1;
}

static int create_note()
{
    int idx = find_free_index();
    if (idx != -1) {
        int size = read_int();
        if (size >= 1200) {
            puts("too large");
            return -1;
        }
        Note* note = malloc(sizeof(Note) + size);
        note->cap = size;
        note->nuse = 0;
        read(0, note->data, size);
        note->data[size] = '\x00';
    }

    return idx;
}

static int get_index()
{
    int idx = read_int();
    if (idx >= 0 || idx < MAX_NOTE)
        return idx;
    return -1;
}

static void read_note()
{
    int idx = get_index();
    if (idx != -1 && notes[idx] != NULL) {
        printf("data: %s\n", notes[idx]->data);
        notes[idx]++;
    }
}

static void update_note()
{
    int idx = get_index();
    if (idx != -1 && notes[idx] != NULL) {
        Note* note = notes[idx];
        read(0, note->data, note->cap);
        note->data[note->cap - 1] = 0;
        notes[idx]++;
    }
}

static void delete_note()
{
    int idx = get_index();
    if (idx != -1 && notes[idx] != NULL) {
        free(notes[idx]);
        notes[idx] = NULL;
    }
}

static void stat_note()
{
    int idx = get_index();
    if (idx != -1 && notes[idx] != NULL) {
        Note* note = notes[idx];
        printf("cap: %d, use cnt: %d, len: %d\n", note->cap, note->nuse, (int)strlen(note->data));
    }
}

static void menu()
{
	printf("Menu\n");
	printf("1. Create Note\n");
	printf("2. Read Note\n");
	printf("3. Update Note\n");
	printf("4. Delete Note\n");
	printf("5. View Note Stat\n");
	printf("Choice: ");
	fflush(stdout);
}

int main()
{
    int op = 0;
    printf("op address: %p\n", &op);
    while (op != -1) {
        menu();
        op = read_int();

        switch (op) {
            case 1:
                printf("New note id: %d\n", create_note());
                break;
            case 2:
                read_note();
                break;
            case 3:
                update_note();
                break;
            case 4:
                delete_note();
                break;
            case 5:
                stat_note();
                break;
            default:
                op = -1;
                break;
        }
    }

    return 0;
}
