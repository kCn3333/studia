.SUFFIXES: .cpp .o .x .h

DIR = pamiec_dzielona

NAME1 = producent
NAME2 = klient
NAME3 = pd
NAME4 = semafor

# producent
EXEC1  = $(NAME1).x  
OBJS1  = $(NAME1).o

# klient
EXEC2  = $(NAME2).x
OBJS2  = $(NAME2).o 

# pamiec dzielona
OBJS3 = $(NAME3).o

#semafory
OBJS4 = $(NAME4).o

#pliki naglowkowe - semafory i pamiec
HEAD3 = $(NAME3).h
HEAD4 = $(NAME4).h

#biblioteka dynamiczna - semafory i pamiec
LIB = libsemafory_pamiec.so
LIBFLAG = -lsemafory_pamiec

# opcje kompilatora i linkera
CFLAGS = -Wall -pedantic -fPIC -O 
LFLAGS = -L.

# kompilator i linker
CO = g++
LD = $(CO)

# biblioteka dynamiczna
AR = g++
# opcje archiwizera
ARFLAGS = -shared -fPIC -o

%.o: %.cpp %.h
	$(CO) $(CFLAGS) -c $<
    
    %.o: %.cpp
	$(CO) $(CFLAGS) -c $<
	
.PHONY: all
	all: $(EXEC1) $(EXEC2)
		
# tworzenie biblioteki statycznej 
$(LIB): $(OBJS3) $(OBJS4)
	$(AR) $(ARFLAGS) $@ $?

$(EXEC1): $(OBJS1) $(LIB) 
	$(LD) -o $@ $(LFLAGS) $(LIBFLAG) $(OBJS1)	
$(EXEC2): $(OBJS2) $(LIB)
	$(LD) -o $@ $(LFLAGS) $(LIBFLAG) $(OBJS2)
			    
# uruchamianie
.PHONY: producent
producent: $(EXEC1) 
	./$(EXEC1)
			
.PHONY: klient
klient: $(EXEC2)
	./$(EXEC2)
							
# sprzataczka 
.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.x core core* a.out
# archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
