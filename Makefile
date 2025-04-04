CC = g++
CFLAGS = -c

all: atm_program

atm_program: Account.o ATMachine.o Main.o
	$(CC) Account.o ATMachine.o Main.o -o atm_program

Account.o: Account.cpp Account.h
	$(CC) $(CFLAGS) Account.cpp -o Account.o

ATMachine.o: ATMachine.cpp ATMachine.h Account.h
	$(CC) $(CFLAGS) ATMachine.cpp -o ATMachine.o

Main.o: Main.cpp Account.h ATMachine.h
	$(CC) $(CFLAGS) Main.cpp -o Main.o

clean:
	rm -f *.o atm_program