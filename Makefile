#INCS = -I. -I/usr/include -I/usr/local/include -I
#LIBS = -L/usr/lib -L/usr/local/lib -lpcap

INCS = -I. -I/usr/x86_64-w64-mingw32/include/
LIBS = -L/usr/x86_64-w64-mingw32/lib -lws2_32

CXXFLAGS = -std=c++11 -Wall -pedantic -pipe -O2 ${INCS} -ggdb
LDFLAGS = -g ${LIBS}

CXX = x86_64-w64-mingw32-g++
#CXX = clang++

SOURCES := $(wildcard src/*.cpp) $(wildcard src/RSC/*.cpp) $(wildcard src/RSC/model/*.cpp)
OBJECTS := $(SOURCES:src/%.cpp=bin/%.o)

all: mkbin options $(OBJECTS) autoemu.exe

mkbin:
	@mkdir -p bin/RSC/model

options:
	@echo autoemu.exe build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "CXXFLAGS = ${CXXFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CXX      = ${CXX}"

bin/%.o: src/%.cpp
	@echo CXX $<
	@${CXX} -o $@ -c ${CXXFLAGS} $<

autoemu.exe:
	@echo CXX -o $@
	@${CXX} -static -o $@ ${OBJECTS} ${LDFLAGS}
	@echo $@ finished compiling.

clean:
	@echo cleaning
	@rm -rf bin/* autoemu.exe
