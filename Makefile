CC			= g++
CFLAGS		= -g -Wall -std=c++0x
LIBS		= -lSDL -lSDL_ttf

headers		= activity.h		\
			  basic.h			\
			  board.h			\
			  button.h			\
			  card.h			\
			  card-pawn.h		\
			  const.h			\
			  engine.h			\
			  game.h			\
			  player.h			\
			  tile.h			\
			  unit.h			\
			  activity-main.h	\
			  activity-battle.h

objects		= activity.o		\
			  board.o			\
			  button.o			\
			  card.o			\
			  card-pawn.o		\
			  engine.o			\
			  game.o			\
			  player.o			\
			  tile.o			\
			  unit.o			\
			  main.o			\
			  activity-main.o	\
			  activity-battle.o

%.o : %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(objects)
	$(CC) $(CFLAGS) -o program $(objects) $(LIBS)

$(objects) : $(headers)

clean:
	rm *.o program

.PHONY:
	clean
