.SUFFIXES: .cpp .o .x .h

DIR = kalendarz

NAME1 = kalendarz
NAME2 = data

EXEC1  = $(NAME1).x  
OBJS1  = $(NAME1).o

OBJS2 = $(NAME2).o

# biblioteka statyczna
LIB = libdata.a

# opcje kompilatora i linkera
CFLAGS = -wall -pedantic -o 
LFLAGS = -wall -pedantic -o

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
	all: $(EXEC1)
			
# tworzenie biblioteki statycznej
$(LIB): $(OBJS2)
	$(AR) $(ARFLAGS) $@ $?
		

$(EXEC1): $(OBJS1) $(LIB) 
	$(LD) -o $@ $(LFLAGS) $^
	
# uruchamianie
.PHONY: kalendarz
kalendarz: $(EXEC1) 
	./$(EXEC1)
			
# sprzataczka 
.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.x core core* a.out
# archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
