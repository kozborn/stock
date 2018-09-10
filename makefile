PROG = main
SOURCE = main.cpp
CC = g++
CPPFLAGS = -std=c++11
FLTK = fltk-config --ldflags

all: $(PROG)

$(PROG): $(SOURCE)
	$(CC) $(CPPFLAGS) $(SOURCE) -o $(PROG) `$(FLTK)`

run:
	./$(PROG)

clean:
	rm -f $(PROG)