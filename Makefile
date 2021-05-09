SHELL 		:= /bin/bash

SOURCES := $(wildcard $(patsubst %, %/*.c, src))
OBJECTS := $(patsubst src%, bin%, $(SOURCES:.c=.o))
EXE := bin/main

.DEFAULT_GOAL := all

.git:
	git init
	git add .
	git commit -m "Create initial project"

.PHONY: init
init: .git

run: all
	./$(EXE)

all: clean $(EXE)

$(EXE): $(OBJECTS)
	cc $^ -o $@ -lpthread -lm
	-$(RM) bin/*.o

$(OBJECTS):
	$(eval OFILE := $@)
	$(eval SFILE := $(patsubst bin/%.o, src/%.c, $(OFILE)))
	cc -c $(SFILE) -o $(OFILE)

.PHONY: clean
clean:
	-$(RM) $(EXE)
	-$(RM) bin/*.o

mem: all
	valgrind make test
