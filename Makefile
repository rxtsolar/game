CC			= g++
CFLAGS		= -g -Wall -std=c++0x
LIBS		= -lSDL

headers		= basic.h	\
			  board.h	\
			  engine.h	\
			  game.h	\
			  player.h	\
			  tile.h	\
			  unit.h

objects		= board.o	\
			  engine.o	\
			  game.o	\
			  player.o	\
			  tile.o	\
			  unit.o	\
			  main.o

%.o : %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(objects)
	$(CC) $(CFLAGS) -o program $(objects) $(LIBS)

$(objects) : $(headers)

clean:
	rm *.o program

.PHONY:
	clean
