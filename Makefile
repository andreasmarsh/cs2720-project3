compile: BankSimulation

BankSimulation: QueType.o PriorityQueue.o Customer.o BankSimulation.cpp
	g++ -Wall -g -o BankSimulation QueType.o PriorityQueue.o Customer.o BankSimulation.cpp

PriorityQueue.o: PriorityQueue.cpp PriorityQueue.h
	g++ -Wall -c -std=c++14 -O0 -pedantic-errors -g PriorityQueue.cpp

QueType.o: QueType.cpp QueType.h
	g++ -Wall -c -std=c++14 -O0 -pedantic-errors -g QueType.cpp

Customer.o: Customer.cpp Customer.h
	g++ -Wall -c -std=c++14 -O0 -pedantic-errors -g Customer.cpp

run:
	./BankSimulation

clean:
	/bin/rm *.o BankSimulation


compile2: BankSimulation2

BankSimulation2: QueType.o PriorityQueue.o Customer.o BankSimulationProto.cpp
	g++ -Wall -g -o BankSimulation2 QueType.o PriorityQueue.o Customer.o BankSimulationProto.cpp

run2:
	./BankSimulation2

clean2:
	/bin/rm *.o BankSimulation2
