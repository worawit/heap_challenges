
FILES := $(wildcard *.c)
TARGETS := $(patsubst %.c,%,$(FILES))

all: $(TARGETS)

$(TARGETS): %: %.c
	gcc -o $@ $^

clean:
	rm $(TARGETS)

