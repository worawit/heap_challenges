#include <cstdio>
#include <cstdlib>
#include <cstring>

class String
{
    int len;
    int cap;
    char* s;

public:
    String() {
        len = 0;
        cap = 0;
        s = NULL;
    }

    String(const char* txt) {
        len = strlen(txt);
        cap = (len + 1 + 7) & (~0x7);
        s = new char[cap];
        strcpy(s, txt);
    }

    String(String& str) {
        len = str.len;
        cap = str.cap;
        s = new char[cap];
        strcpy(s, str.s);
    }

    ~String() {
        free(s);
    }

    void assign(const char* txt) {
        len = strlen(txt);
        strcpy(s, txt);
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

class Array
{
    size_t count;
    int *data;

public:
    Array(size_t count) {
        this->count = count;
        data = (int*) calloc(count, sizeof(int));
    }

    ~Array() {
        free(data);
    }

    int get(int i) const {
        if (i < count)
            return data[i];
        return 0;
    }

    void set(int i, int val) {
        if (i < count)
            data[i] = val;
    }

    void print_address() {
        printf("Array this address: %p\n", this);
        printf("Array this->data address: %p\n", this->data);
    }
};

int main()
{
    int key = 0x1234;
    char buf[256];

    String *msg = new String("Hello world");
    Array *arr = new Array(8);

    printf("current key value: %#x\n", key);
    printf("key address: %p\n", &key);
    msg->print_address();
    arr->print_address();

    fgets(buf, sizeof(buf), stdin);
    msg->assign(buf);

    // set array element value
    int idx, val;
    fgets(buf, sizeof(buf), stdin);
    sscanf(buf, "%d %d", &idx, &val);
    arr->set(idx, val);

    printf("\nkey value: %#x\n", key);
    if (key == 0x1337cafe) {
        puts("Congratulations... You wins.");
    } else {
        puts("Nah...");
    }

    return 0;
}
