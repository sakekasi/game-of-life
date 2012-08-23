CXX = g++
HEADERS = `pkg-config gtkmm-3.0 cairomm-1.0 --cflags`
LIBS = `pkg-config gtkmm-3.0 cairomm-1.0 --libs`

all:main

game-of-life.o : game-of-life.hh game-of-life.cc
	$(CXX) $*.cc -fPIC -dPIC -O -o $@ $(HEADERS) $(LIBS)

main-window.o : main-window.hh main-window.cc
	$(CXX) $*.cc -fPIC -dPIC -O -o $@ $(HEADERS) $(LIBS)

static: static-library
static-library : game-of-life.o main-window.o
	ar rcs libgame-of-life.a game-of-life.o main-window.o

shared: shared-library
shared-library: game-of-life.o main-window.o
	$(CXX) -shared -Wl,-soname,libgame-of-life.so -o libgame-of-life.so  game-of-life.o main-window.o

main: main.cc shared-library
	$(CXX) $@.cc -g -o main -L. -lgame-of-life $(HEADERS) $(LIBS)

.PHONY: clean
clean:
	rm *~ *.o main *.so *.a
