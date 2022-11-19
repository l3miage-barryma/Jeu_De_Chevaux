all: projet0

projet0: projet0.o 
	gcc projet0.o -o projet0
	
projet0.o : projet0.c projet0.h 
	gcc -c projet0.c
	


clean : 
	@echo "on efface tous le fichiers objets"
	rm -f *.o
