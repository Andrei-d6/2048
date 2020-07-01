MML = Move/MoveLeft
MMU = Move/MoveUp
MMR = Move/MoveRight
MMD = Move/MoveDown

all: build

run:
	./2048

build: exec.o Draw/Draw.o GP/GenerarePozitii.o Random2,4/Random2,4.o Menu/Menu.o BestMove/BestMove.o $(MML)/MoveLeft.o $(MMU)/MoveUp.o $(MMR)/MoveRight.o $(MMD)/MoveDown.o GameOver/GameOver.o
	gcc -Wall exec.o Draw/Draw.o GP/GenerarePozitii.o Random2,4/Random2,4.o Menu/Menu.o BestMove/BestMove.o $(MML)/MoveLeft.o $(MMU)/MoveUp.o $(MMR)/MoveRight.o $(MMD)/MoveDown.o GameOver/GameOver.o  -lcurses -o 2048

exec.o:	exec.c
	gcc -Wall -c exec.c -lcurses

GP/GenerarePozitii.o:	GP/GenerarePozitii.c GP/GenerarePozitii.h
	gcc -Wall -c GP/GenerarePozitii.c -o GP/GenerarePozitii.o

Random2,4/Random2,4.o:	Random2,4/Random2,4.c Random2,4/Random2,4.h
	gcc -Wall -c Random2,4/Random2,4.c -o Random2,4/Random2,4.o

Draw/Draw.o:	Draw/Draw.c Draw/Draw.h GP/GenerarePozitii.h Random2,4/Random2,4.h
	gcc -Wall -c Draw/Draw.c -lcurses -o Draw/Draw.o

Menu/Menu.o:	Menu/Menu.c Menu/Menu.h
	gcc -Wall -c Menu/Menu.c  -lcurses -o Menu/Menu.o

BestMove/BestMove.o:	BestMove/BestMove.c BestMove/BestMove.h
	gcc -Wall -c BestMove/BestMove.c -o BestMove/BestMove.o

Move/MoveLeft/MoveLeft.o: $(MML)/MoveLeft.c $(MML)/MoveLeft.h
	gcc -Wall -c $(MML)/MoveLeft.c -o $(MML)/MoveLeft.o

Move/MoveUp/MoveUp.o: $(MMU)/MoveUp.c $(MMU)/MoveUp.h
	gcc -Wall -c $(MMU)/MoveUp.c -o $(MMU)/MoveUp.o

Move/MoveRight/MoveRight.o: $(MMR)/MoveRight.c $(MMR)/MoveRight.h
	gcc -Wall -c $(MMR)/MoveRight.c -o $(MMR)/MoveRight.o

Move/MoveDown/MoveDown.o: $(MMD)/MoveDown.c $(MMD)/MoveDown.h
	gcc -Wall -c $(MMD)/MoveDown.c -o $(MMD)/MoveDown.o

GameOver/GameOver.o: GameOver/GameOver.c GameOver/GameOver.h
	gcc -Wall -c GameOver/GameOver.c -o GameOver/GameOver.o

clean:
	rm -f exec.o Draw/Draw.o GP/GenerarePozitii.o Random2,4/Random2,4.o Menu/Menu.o BestMove/BestMove.o $(MML)/MoveLeft.o $(MMU)/MoveUp.o $(MMR)/MoveRight.o $(MMD)/MoveDown.o GameOver/GameOver.o 2048











