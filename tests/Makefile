.PHONY: clean test
CC=g++-10
LDFLAGS=
CCFLAGS=-Wall -std=c++20 -g


LD_INCLUDES=-I../include

.PHONY: $(INTERNAL_TEST_LIBRARIES)

LD_LIBS=-L../lib -lauto_test
LDTEST_INCLUDES=-Isrc

SRC_HEADERS=$(wildcard ../include/*.hpp)
SRC_HEADERS+=$(wildcard ../include/*/*.hpp)
SRC_HEADERS+=$(wildcard ../include/*/*/*.hpp)
SRC_HEADERS+=$(wildcard ../include/*/*/*/*.hpp)
SRC_HEADERS+=$(wildcard ../include/*/*/*/*/*.hpp)

SRC_IMPLEMENTATION=$(wildcard ../src/*.cpp)
SRC_IMPLEMENTATION+=$(wildcard ../src/*/*.cpp)
SRC_IMPLEMENTATION+=$(wildcard ../src/*/*/*.cpp)
SRC_IMPLEMENTATION+=$(wildcard ../src/*/*/*/*.cpp)
SRC_IMPLEMENTATION+=$(wildcard ../src/*/*/*/*/*.cpp)

TEST_SOURCES=$(wildcard src/*.cpp)
TEST_SOURCES+=$(wildcard src/*/*.cpp)
TEST_SOURCES+=$(wildcard src/*/*/*.cpp)
TEST_SOURCES+=$(wildcard src/*/*/*/*.cpp)
TEST_OBJECTS=$(addprefix obj/, $(patsubst src/%, %, $(TEST_SOURCES:.cpp=.o)))

test: test_build
	make test_build
	./test_build

test_build: $(TEST_OBJECTS) ../lib/libauto_test.a
	$(CC) $(TEST_OBJECTS) $(CCFLAGS) $(LDFLAGS) $(LD_LIBS) -o $@ 
	
../lib/libauto_test.a: $(SRC_HEADERS) $(SRC_IMPLEMENTATION)
	make -C ../ lib/libauto_test.a

$(TEST_OBJECTS): obj/%.o: src/%.cpp obj/%.dir $(SRC_HEADERS)
	$(CC) $(CCFLAGS) -o $@ -c $< $(LD_INCLUDES) $(LDTEST_INCLUDES)
	
obj/%.dir:
	mkdir -p $@

clean:
	rm -rf obj
	mkdir obj
	rm -f test_build