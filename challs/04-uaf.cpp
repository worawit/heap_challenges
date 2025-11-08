#include <cstdio>
#include <cstdlib>
#include <cstring>

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

class String
{
    int len;
    int cap;
    char* s;

public:
    String(int cap) {
        len = 0;
        this->cap = cap;
        s = (char*) malloc(cap);
    }

    String(const char* txt) {
        len = strlen(txt);
        cap = (len + 1 + 7) & (~0x7);
        s = new char[cap];
        strcpy(s, txt);
    }

    ~String() {
        free(s);
        s = NULL;
    }

    void read() {
        len = read_line(s, cap);
    }

    char* txt() const {
        return s;
    }

    int length() const {
        return len;
    }

    void print_address() {
        printf("String this address: %p\n", this);
        printf("String this->s address: %p\n", this->s);
    }
};

#define MAX_NOTE 4
static String *notes[MAX_NOTE];
static int note_cnt;

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
        char buf[256];
        read_line(buf, sizeof(buf));
        notes[idx] = new String(buf);
        note_cnt++;
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
    if (idx != -1) {
        if (notes[idx] != NULL)
            printf("%s\n", notes[idx]->txt());
    }
}

static void update_note()
{
    int idx = get_index();
    if (idx != -1) {
        if (notes[idx] != NULL)
            notes[idx]->read();
    }
}

static void delete_note()
{
    int idx = get_index();
    if (idx != -1) {
        delete notes[idx];
        note_cnt--;
    }
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
    int key = 0x1234;
    printf("current key value: %#x\n", key);
    printf("key address: %p\n", &key);

    int op = 0;
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
            default:
                op = -1;
                break;
        }
    }

    printf("\nkey value: %#x\n", key);
    if (key == 0x1337cafe) {
        puts("Congratulations... You wins.");
    } else {
        puts("Nah...");
    }

    return 0;
}
