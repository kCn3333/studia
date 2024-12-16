DIR = wielomian

.PHONY: demo
demo: demo.exe
	./demo

demo.exe: demo.cpp
	g++ -Wall -pedantic -o demo zespolone.cpp wielomian.cpp demo.cpp

.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.x core core* a.out
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )	
