.SUFFIXES: .cpp .o .x .h

DIR = kolejki_komunikatow

NAME1 = serwer
NAME2 = klient
NAME3 = kolejki

# serwer
EXEC1  = $(NAME1).x  
OBJS1  = $(NAME1).o

# klient
EXEC2  = $(NAME2).x
OBJS2  = $(NAME2).o 

# kolejki
OBJS3 = $(NAME3).o

# biblioteka statyczna
LIB = libkolejki.a

# opcje kompilatora i linkera
CFLAGS = -Wall -pedantic -O 
LFLAGS = -Wall -pedantic -O

# kompilator i linker
CO = g++
LD = $(CO)

# program archiwizer do tworzenia bibliotek statycznych
AR = ar
# opcje archiwizera
ARFLAGS = rcs

%.o: %.cpp %.h
	$(CO) $(CFLAGS) -c $<
    
    %.o: %.cpp
	$(CO) $(CFLAGS) -c $<
	
	
.PHONY: all
	all: $(EXEC1) $(EXEC2)
		
# tworzenie biblioteki statycznej
$(LIB): $(OBJS3)
	$(AR) $(ARFLAGS) $@ $?
		

$(EXEC1): $(OBJS1) $(LIB) 
	$(LD) -o $@ $(LFLAGS) $^
	
$(EXEC2): $(OBJS2) $(LIB)
	$(LD) -o $@ $(LFLAGS) $^
			    
# uruchamianie
.PHONY: serwer
serwer: $(EXEC1) 
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
