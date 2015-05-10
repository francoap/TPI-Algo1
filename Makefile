CC = g++ -std=c++11
OBJS = Juego.cpp Nivel.cpp Flor.cpp Vampiro.cpp main.cpp
OBJ_NAME = tpi


all : $(OBJS)
	$(CC) $(OBJS) -o $(OBJ_NAME)

clean:
	rm ./tpi
	rm *.o
	
