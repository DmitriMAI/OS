
pi: main_no_dyn.o libpi.a libsss.a
	gcc -o pi main_no_dyn.o -L. -lpi -lsss

main_no_dyn.o: main_no_dyn.c
	gcc -c main_no_dyn.c

libpi.a: pi.o
	ar cr libpi.a pi.o

libsss.a: sss.o
	ar cr libsss.a sss.o

pi.o: pi.c
	gcc -c pi.c

sss.o: sss.c
	gcc -c sss.c

clean:
	rm -f *.o *.a
