# Makefile
# Use `make run` to build and run the program.

# Remote and local's directory structure should match.
SRC=src
LOG=log
OUT=build

SOURCES=$(SRC)/main.c $(SRC)/utils.c $(SRC)/mem.c $(SRC)/probe.c
TARGET=$(OUT)/main
RESULT:=$(LOG)/csv-$(shell date +%Y-%m-%d).md
TIMESTAMPS:=$(LOG)/timestamps-$(shell date +%Y-%m-%d).md

.PHONY: build run clean reset

build:
	gcc -march=native -o $(TARGET) $(SOURCES)

run:
	./$(TARGET) >> $(RESULT); \

clean:
	rm $(TARGET)

reset:
	rm $(LOG)/*.md
