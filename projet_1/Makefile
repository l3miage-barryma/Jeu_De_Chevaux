all: projet_1

projet_1: communication.o projet_1.o 
	gcc communication.o projet_1.o -o projet_1
	
projet_1.o : projet_1.c
	gcc -c projet_1.c
	
communication.o : communication.c communication.h
	gcc -c communication.c
	
clean : 
	@echo "on efface les fichiers objets"
	rm *.o


