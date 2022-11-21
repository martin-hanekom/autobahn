IDIR = ../include
CC = g++
CFLAGS = -I.
LIBS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lm
DEPS =
OBJ = main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f *.o main
