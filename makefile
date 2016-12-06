
FLAGS = -g -Wall -std=c++11

all:	schedule.exe

schedule.exe:	Planner.o schedule.o
	g++ $(FLAGS) Planner.o schedule.o -o schedule.exe

schedule.o:	schedule.cpp
	g++ $(FLAGS) -c schedule.cpp -o schedule.o

Planner.o: Planner.h
	g++ $(FLAGS) -c Planner.cpp -o Planner.o


clean:
	rm -f *.o schedule.exe







