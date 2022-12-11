main.exe: main.o functions.o classes.o
	g++ -o main main.o functions.o classes.o

main.o: main.cpp
	g++ -c main.cpp

functions.o: functions.cpp 
	g++ -c functions.cpp

classes.o: classes.cpp
	g++ -c classes.cpp