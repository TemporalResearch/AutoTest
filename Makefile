.PHONY: clean test
CC=g++-10
LDFLAGS=
CCFLAGS=-Wall -std=c++20 -g

LD_INCLUDES=-Iinclude

SRC_HEADERS=$(wildcard include/*.hpp)
SRC_HEADERS+=$(wildcard include/*/*.hpp)
SRC_IMPLEMENTATION=$(wildcard src/*.cpp)
SRC_IMPLEMENTATION+=$(wildcard src/*/*.cpp)
SRC_OBJECTS=$(addprefix obj/, $(patsubst src/%, %, $(SRC_IMPLEMENTATION:.cpp=.o)))

lib/libauto_test.a: $(SRC_OBJECTS)
	echo $(SRC_OBJECTS)
	ar ru $@ $^
	ranlib $@
	
$(SRC_OBJECTS): obj/%.o: src/%.cpp include/%.hpp obj/%.dir
	$(CC) $(CCFLAGS) -o $@ -c $< $(LD_INCLUDES)

obj/%.dir:
	mkdir -p $@
	
test:
	make -C ./tests test

clean:
	rm -rf obj
	rm -rf lib
	mkdir obj
	mkdir lib

