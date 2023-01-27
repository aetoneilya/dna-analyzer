PROJECT_NAME=dna-analyzer

CXX=g++
CXXFLAGS=-c -pedantic -Wall -Wextra -Wshadow -Wconversion -Wunreachable-code -std=c++17
LDFLAGS=-lm -lpthread

DEBUG ?= 1

ifeq ($(DEBUG),1)
	CXXFLAGS+=-g
	CXXFLAGS+=-DDEBUG
else
	CXXFLAGS+=-O2
	CXXFLAGS+=-Werror
endif

MAINSRC=main.cc
MAINOBJ=$(MAINSRC:.cc=.o)
TESTSRC=test.cc
TESTOBJ=$(TESTSRC:.cc=.o)
SRC=$(filter-out ./$(MAINSRC) ./$(TESTSRC), $(shell find . -type f -name "*.cc" -not -path "./view/*"))
OBJ=$(SRC:.cc=.o)


EXECUTABLE=$(PROJECT_NAME)
TESTEXECUTABLE="$(PROJECT_NAME)-test"

.PHONY: all build style cpplint clean rebuild

all: build

build:  $(MAINOBJ) $(OBJ)
	$(CXX) $^ -o $(EXECUTABLE) $(LDFLAGS)

test: LDFLAGS+=-lgtest
test: $(TESTOBJ) $(OBJ)
	$(CXX) $^ -o $(TESTEXECUTABLE) $(LDFLAGS)
	./$(TESTEXECUTABLE)


%.o: %.cc
	$(CXX) $(CXXFLAGS) $^ -o $@

style: cppcheck clang cpplint

cppcheck:
	cppcheck --std=c++17 --enable=all --suppress=missingIncludeSystem ./
	@# --suppress=unusedFunction --suppress=constParameter

clang:
	@clang-format -i $(shell find . -type f \( -name "*.h" -o -name "*.cc" \))
	clang-format -n $(shell find . -type f \( -name "*.h" -o -name "*.cc" \))

cpplint:
	cpplint --extensions=cc,h --filter=-runtime/references --recursive ./

clean:
	rm -rf $(OBJ) $(EXECUTABLE) $(MAINOBJ) $(TESTOBJ) $(TESTEXECUTABLE)

rebuild: clean all
