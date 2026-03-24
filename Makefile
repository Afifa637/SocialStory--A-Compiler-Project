# SocialStoryScript build system (MSYS2/MinGW64-friendly)

CC ?= gcc
FLEX ?= flex
BISON ?= bison
PYTHON ?= $(shell command -v python3 2>/dev/null || command -v python 2>/dev/null || command -v py 2>/dev/null)
BISONFLAGS ?= -Wno-conflicts-sr

CFLAGS ?= -std=c11 -Wall -Wextra -Werror -O2
GEN_CFLAGS ?= -Wno-unused-function -Wno-unused-parameter
LDFLAGS ?= -lm

TARGET := socialstory
OBJS := main.o socialstory_parser.tab.o lex.yy.o

HEADERS := compiler.h ast_functions.h symbol_table.h statistics.h tac_generator.h optimizer.h interpreter.h socialstory_tokens.h

HAVE_FLEX := $(shell command -v $(FLEX) >/dev/null 2>&1 && echo 1 || echo 0)
HAVE_BISON := $(shell command -v $(BISON) >/dev/null 2>&1 && echo 1 || echo 0)

.PHONY: build clean distclean run test regen tools-check submission-clean

build: $(TARGET)

tools-check:
	@echo "make:  $$(command -v make 2>/dev/null || echo MISSING)"
	@echo "gcc:   $$(command -v $(CC) 2>/dev/null || echo MISSING)"
	@echo "flex:  $$(command -v $(FLEX) 2>/dev/null || echo MISSING)"
	@echo "bison: $$(command -v $(BISON) 2>/dev/null || echo MISSING)"

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

main.o: main.c compiler.h
	$(CC) $(CFLAGS) -c -o $@ $<

socialstory_parser.tab.o: socialstory_parser.tab.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<

lex.yy.o: lex.yy.c socialstory_parser.tab.h socialstory_tokens.h
	$(CC) $(CFLAGS) $(GEN_CFLAGS) -c -o $@ $<

socialstory_parser.tab.c socialstory_parser.tab.h: socialstory_parser.y
ifeq ($(HAVE_BISON),1)
	$(BISON) $(BISONFLAGS) -d -o socialstory_parser.tab.c socialstory_parser.y
else
	@test -f socialstory_parser.tab.c -a -f socialstory_parser.tab.h || \
		(echo "Error: bison not found and generated parser files are missing." && \
		echo "Install with: pacman -S --needed flex bison" && false)
	@echo "Warning: bison not found; using shipped generated parser files."
endif

lex.yy.c: socialstory.l socialstory_parser.tab.h
ifeq ($(HAVE_FLEX),1)
	$(FLEX) -o lex.yy.c socialstory.l
else
	@test -f lex.yy.c || \
		(echo "Error: flex not found and generated lexer file is missing." && \
		echo "Install with: pacman -S --needed flex bison" && false)
	@echo "Warning: flex not found; using shipped generated lexer file."
endif

regen:
	@if [ "$(HAVE_BISON)" != "1" ] || [ "$(HAVE_FLEX)" != "1" ]; then \
		echo "Error: regen requires flex and bison. Install with: pacman -S --needed flex bison"; \
		exit 1; \
	fi
	$(BISON) $(BISONFLAGS) -d -o socialstory_parser.tab.c socialstory_parser.y
	$(FLEX) -o lex.yy.c socialstory.l

run: build
	@if [ -z "$(INPUT)" ]; then \
		echo "Usage: make run INPUT=sample_programs/01_account_baseline_report.txt"; \
		exit 1; \
	fi
	./$(TARGET) $(INPUT)

test: build
	@if [ -z "$(PYTHON)" ]; then \
		echo "Error: no Python interpreter found (python3/python/py)."; \
		exit 1; \
	fi
	@if [ -f ./$(TARGET).exe ]; then \
		$(PYTHON) tests/run_tests.py ./$(TARGET).exe; \
	else \
		$(PYTHON) tests/run_tests.py ./$(TARGET); \
	fi

clean:
	rm -f $(TARGET) $(TARGET).exe $(OBJS)
	-rm -f output_*.txt

distclean: clean
	rm -f socialstory_parser.tab.c socialstory_parser.tab.h lex.yy.c

submission-clean: clean
	-rm -rf .vscode
	@echo "Submission cleanup complete: removed build/output/editor artifacts."
