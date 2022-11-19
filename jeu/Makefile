all: projet

projet: joue.o projet.o 
	gcc joue.o projet.o -o projet
	
projet.o : projet.c
	gcc -c projet.c
	
joue.o : joue.c joue.h
	gcc -c joue.c
	
clean : 
	@echo "on efface les fichiers objets"
	rm *.o


