# ------------------------------------ #
# -----------m-a-k-e-f-i-l-e---------- #
# ------------------------------------ #

LINK_TARGET = demo.exe
OBJS =  \
    ls.o \
    demo.o
   
REBUILDABLES = $(OBJS) $(LINK_TARGET)

clean : 
	rm -f $(REBUILDABLES)
 all : $(LINK_TARGET)
$(LINK_TARGET) : $(OBJS)
%.o : %.cpp
	g++ -g -o $@ -c $<

demo.o : ls.h 
ls.o : ls.h 
