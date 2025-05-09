# Makefile for HH_ATM1 project

CC = g++
CFLAGS = -std=c++11 -Wall -g
SRC = main.cpp ATMachine.cpp Account.cpp CustomerSvc.cpp Statistics.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = atm_program

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)
	./$(EXEC)
	rm -f main.o ATMachine.o Account.o CustomerSvc.o Statistics.o atm_program

main.o: main.cpp ATMachine.h Account.h CustomerSvc.h Statistics.h
	$(CC) $(CFLAGS) -c main.cpp

ATMachine.o: ATMachine.cpp ATMachine.h Account.h CustomerSvc.h Statistics.h
	$(CC) $(CFLAGS) -c ATMachine.cpp

Account.o: Account.cpp Account.h
	$(CC) $(CFLAGS) -c Account.cpp

CustomerSvc.o: CustomerSvc.cpp CustomerSvc.h Account.h
	$(CC) $(CFLAGS) -c CustomerSvc.cpp

Statistics.o: Statistics.cpp Statistics.h Account.h ATMachine.h
	$(CC) $(CFLAGS) -c Statistics.cpp

clean:
	rm -f main.o ATMachine.o Account.o CustomerSvc.o Statistics.o atm_program
