programs = prog1 prog2 prog3

all: $(programs)

CC = gcc
override CFLAGS += -g -Wno-everything -pthread 

LIBS = -lm

ALIBS = libProg%.a 

CDIR = Source

OBJDIR = Objects

COMMON_ = tDocumento.o tLista.o tListaHash.o tPalavra.o tPredicao.o tPropriedadeDoc.o tPropriedadePal.o tProximidade.o tTipo.o utils.o

COMMON = $(patsubst %,$(OBJDIR)/%,$(COMMON_))

MAINPROG1 = $(OBJDIR)/mainProg1.o 

MAINPROG2 = $(OBJDIR)/mainProg2.o 

MAINPROG3 = $(OBJDIR)/mainProg3.o 

PROGLIB1 = $(OBJDIR)/tProg1.o

PROGLIB2 = $(OBJDIR)/tProg2.o

PROGLIB3 = $(OBJDIR)/tProg3.o

prog%: $(ALIBS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

libProg1.a: $(MAINPROG1) $(PROGLIB1) $(COMMON)
	ar -cvq $@ $^
	
libProg2.a: $(MAINPROG2) $(PROGLIB2) $(COMMON)
	ar -cvq $@ $^
	
libProg3.a: $(MAINPROG3) $(PROGLIB2) $(PROGLIB3) $(COMMON)
	ar -cvq $@ $^

$(OBJDIR)/t%.o: $(CDIR)/t%.c
	$(CC) $(CFLAGS) -c -o $@ $^ $(LIBS)
	
$(OBJDIR)/u%.o: $(CDIR)/u%.c
	$(CC) $(CFLAGS) -c -o $@ $^ $(LIBS)
	
$(OBJDIR)/main%.o: main%.c
	$(CC) $(CFLAGS) -c -o $@ $^ $(LIBS)
	
clean:
	rm -f prog1 prog2 prog3 *.a $(OBJDIR)/*.o
