CC=g++
CFLAGS=-Wall -lglut -lGLU -lGL -lm
DEPS=objects.h hh_fabs.h
OBJ=main.o objects.o hh_fabs.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hw2: main.o objects.o hh_fabs.o
	$(CC) -o hw2 main.o objects.o hh_fabs.o $(CFLAGS)
