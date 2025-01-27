CC      = clang
CFLAGS  = -g -Wall
RM      = rm -f


default: all

all: main.exe

main.exe: main.c
	$(CC) $(CFLAGS) -o main.exe main.c

clean veryclean:
	$(RM) main.exe
	$(RM) main.ilk
	$(RM) main.pdb

debug: main.c
	$(CC) $(CFLAGS) -o main.exe main.c -DDEBUG

test: main.exe
	./main.exe 66 < data.txt