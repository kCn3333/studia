# ------------------------------------ #
# -----------m-a-k-e-f-i-l-e---------- #
# ------------------------------------ #


NAME = 4
# -------- program wykonawczy -------- #
EXEC = $(NAME).exe
# ----------- object files ----------- #
OBJS = $(NAME).o
# --- opcje kompilatora i linkera ---- #
CFLAGS = -O
LFLAGS = -O
# ------- kompilator i linker -------- #
CO = g++
LD = $(CO)
# -----------------------------------  #
%.o: %.cpp %.h
	$(CO) $(CFLAGS) -c $<
%.o: %.cpp
	$(CO) $(CFLAGS) -c $<
# ------------------------------------ #
$(EXEC): $(OBJS)
	$(LD) -o $@ $(CFLAGS) $^
run: $(EXEC)
	./$(EXEC)
# ----------- sprzataczka ------------ #
clean:
	rm -f *.o *~ *.a core core* a.out
