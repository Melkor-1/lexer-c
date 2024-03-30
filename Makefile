CC	:= gcc-13

CFLAGS 	+= -std=c2x
CFLAGS 	+= -DNDEBUG
CFLAGS 	+= -g3
CFLAGS 	+= -ggdb
CFLAGS 	+= -fPIC
CFLAGS 	+= -gdwarf-4
CFLAGS 	+= -Wall
CFLAGS 	+= -Wextra
CFLAGS 	+= -Wwrite-strings
CFLAGS 	+= -Wno-parentheses
CFLAGS 	+= -Wpedantic
CFLAGS 	+= -Warray-bounds
CFLAGS 	+= -Wconversion
CFLAGS 	+= -Wno-unused-function
CFLAGS 	+= -Wstrict-prototypes
CFLAGS 	+= -fanalyzer

BINDIR  	:= bin
TEST_BINDIR := tests/bin

SRCDIRS 	:= lexer repl token util
SRCS 		:= $(filter-out repl/repl.c, $(wildcard $(addsuffix /*.c, $(SRCDIRS))))

TESTDIR 	:= tests
TEST_SRCS 	:= $(wildcard $(TESTDIR)/*.c)

TARGET 		:= $(BINDIR)/repl
TEST_TARGET := $(TEST_BINDIR)/lexer_test

all: $(TARGET)

$(TARGET): repl/repl.c $(SRCS) | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^

$(TEST_TARGET): $(SRCS) $(TEST_SRCS) | $(TEST_BINDIR)
	$(CC) $(CFLAGS) -o $@ $^

test: $(TEST_TARGET)
	@echo "Running tests..."
	@./$<	

$(BINDIR) $(TEST_BINDIR):
	mkdir -p $@

clean:
	rm -rf $(BINDIR)

fclean_repl:
	rm $(TARGET) 

fclean_test:
	rm $(TEST_TARGET)

.PHONY: all test clean fclean_repl fclean_test

.DELETE_ON_ERROR:
