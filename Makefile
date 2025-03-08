CFLAGS = -g -W -Wall

OBJECTS = command.o main.o string_parser.o

pseudo-shell: main.o command.o string_parser.o
	gcc -g -o $@ $^

main.o: main.c command.h string_parser.h
command.o: command.c command.h
string_parser.o: main.c string_parser.h

clean:
	rm -f $(OBJECTS)

