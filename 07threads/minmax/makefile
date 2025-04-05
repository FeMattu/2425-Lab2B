# definizione del compilatore e dei flag di compilazione
CC = gcc
CFLAGS = -std=c11 -Wall -g -O -pthread
LDLIBS = -lm -pthread

# nome dell’eseguibile da generare
EXECS = minmax.out

# regola di default: genera tutti gli eseguibili
all: $(EXECS)

# regola per la creazione degli eseguibili usando xerrori.o
%.out: %.o xerrori.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

# regola per compilare i .o da .c, includendo xerrori.h
%.o: %.c xerrori.h
	$(CC) $(CFLAGS) -c $<

# pulizia degli oggetti e degli eseguibili
clean:
	rm -f *.o $(EXECS)

# esecuzione con valgrind (puoi modificare gli argomenti)
valgrind: minimax.out
	valgrind --leak-check=full ./minmax.out mini1 mini2

# archivio zip con tutti i file di progetto
zip:
	zip minimax.zip *.c *.h makefile

.PHONY: all clean valgrind zip
