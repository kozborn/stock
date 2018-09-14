PROG = main.out
CC = g++
CPPFLAGS = -std=c++11
OBJS = main.o GUI.o Graph.o Simple_window.o Window.o
WITHOUT_MAIN = GUI.o Graph.o Simple_window.o Window.o
FLTK = fltk-config --ldflags

all : $(OBJS)
	$(CC) $(CPPFLAGS) -o $(PROG) $(OBJS) `$(FLTK)`

run :
	./$(PROG)

compile: main.cpp
	$(CC) $(CPPFLAGS) -o $(PROG) main.cpp $(WITHOUT_MAIN) `$(FLTK)`

main.o: main.cpp
	$(CC) -c $(CPPFLAGS) main.cpp

GUI.o: ./GUI.cpp ./GUI.h
	$(CC) -c $(CPPFLAGS) ./GUI.cpp

Graph.o: ./Graph.cpp ./Graph.h
	$(CC) -c $(CPPFLAGS) ./Graph.cpp

Simple_window.o: ./Simple_window.cpp ./Simple_window.h
	$(CC) -c $(CPPFLAGS) ./Simple_window.cpp

Window.o: ./Window.cpp ./Window.h
	$(CC) -c $(CPPFLAGS) ./Window.cpp

clean:
	 rm -f $(OBJS) $(PROG)
