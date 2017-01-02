
CC = g++
DEBUG = -g -O0 -pedantic-errors
CFLAGS = -Wall -std=c++11 -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

cat: cat.o
	$(CC) $(LFLAGS) -o cat cat.o

cat.o: cat.cpp
	$(CC) $(CFLAGS) cat.cpp

penv: penv.o
	$(CC) $(LFLAGS) -o penv penv.o

penv.o: penv.cpp
	$(CC) $(CFLAGS) penv.cpp

pwd: pwd.o
	$(CC) $(LFLAGS) -o pwd pwd.o

pwd.o: pwd.cpp
	$(CC) $(CFLAGS) pwd.cpp

ls: ls.o
	$(CC) $(LFLAGS) -o ls ls.o

ls.o: ls.cpp
	$(CC) $(CFLAGS) ls.cpp

chmod: chmod.o
	$(CC) $(LFLAGS) -o chmod chmod.o

chmod.o: chmod.cpp
	$(CC) $(CFLAGS) chmod.cpp

stat: stat.o
	$(CC) $(LFLAGS) -o stat stat.o

stat.o: stat.cpp
	$(CC) $(CFLAGS) stat.cpp

ln: ln.o
	$(CC) $(LFLAGS) -o ln ln.o

ln.o: ln.cpp
	$(CC) $(CFLAGS) ln.cpp

rm: rm.o
	$(CC) $(LFLAGS) -o rm rm.o

rm.o: rm.cpp
	$(CC) $(CFLAGS) rm.cpp

mv: mv.o
	$(CC) $(LFLAGS) -o mv mv.o

mv.o: mv.cpp
	$(CC) $(CFLAGS) mv.cpp

mkdir: mkdir.o
	$(CC) $(LFLAGS) -o mkdir mkdir.o

mkdir.o: mkdir.cpp
	$(CC) $(CFLAGS) mkdir.cpp

clean: 
	rm -f *.o
	rm -f cat penv pwd ls chmod stat ln rm mv mkdir
