CC       =  gcc
CFLAGS   = -Wall -O2 -g
LIB      = -lSDL -lSDL_image -lGLU -lGL -lm  
INCLUDES = 

OBJ      = main.o background.o collision.o enemy.o
RM       = rm -f
BIN      = jeu
DIRNAME  = $(shell basename $$PWD)
BACKUP   = $(shell date +`basename $$PWD`-%m.%d.%H.%M.tgz)
STDNAME  = $(DIRNAME).tgz

all : $(BIN)

$(BIN) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) $(INCLUDES)  -o $(BIN)
	@echo "--------------------------------------------------------------"
	@echo "                 to execute type: ./$(BIN) &"
	@echo "--------------------------------------------------------------"

main.o : main.c header.h
	@echo "compile jeu"
	$(CC) $(CFLAGS) -c $<  
	@echo "done..."

background.o : background.c header.h
	@echo "compile background"
	$(CC) $(CFLAGS) -c $<  
	@echo "done..."

collision.o : collision.c header.h
	@echo "compile collision"
	$(CC) $(CFLAGS) -c $<  
	@echo "done..."

enemy.o : enemy.c header.h
	@echo "compile enemy"
	$(CC) $(CFLAGS) -c $<  
	@echo "done..."

clean :	
	@echo "**************************"
	@echo "CLEAN"
	@echo "**************************"
	$(RM) *~ $(OBJ) $(BIN) 

tar : clean 
	@echo "**************************"
	@echo "TAR"
	@echo "**************************"
	cd .. && tar cvfz $(BACKUP) $(DIRNAME)


