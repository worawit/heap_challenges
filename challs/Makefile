
FILES := $(wildcard *.c)
TARGETS := $(patsubst %.c,%,$(FILES))

PPFILES := $(wildcard *.cpp)
PPTARGETS := $(patsubst %.cpp,%,$(PPFILES))

all: $(TARGETS) $(PPTARGETS)

$(TARGETS): %: %.c
	gcc -g -o $@ $^

$(PPTARGETS): %: %.cpp
	g++ -o $@ $^

clean:
	rm $(TARGETS) $(PPTARGETS)
