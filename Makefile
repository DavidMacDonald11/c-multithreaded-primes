SHELL 		:= /bin/bash

SOURCES := $(wildcard $(patsubst %, %/*.c, src))
OBJECTS := $(patsubst src%, bin%, $(SOURCES:.c=.o))
EXE := bin/main

.DEFAULT_GOAL := run

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
	cc $^ -o $@
	-$(RM) bin/*.o

$(OBJECTS):
	$(eval OFILE := $@)
	$(eval SFILE := $(patsubst bin/%.o, src/%.c, $(OFILE)))
	cc -c $(SFILE) -o $(OFILE)

.PHONY: clean
clean:
	-$(RM) $(EXE)

mem: all
	valgrind make test
