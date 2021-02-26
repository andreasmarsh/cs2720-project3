#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "QueType.cpp"
#include "PriorityQueue.cpp"
#include "Customer.h"

ostream& operator << (ostream& out, Customer& s) {
	out << s.name << " " << s.wait << "  wait  service " << s.service << "\n";
	return out;
}
istream& operator >> (istream& in, Customer& s) {
	in >> s.name >> s.arrival >> s.service >> s.wait;
	return in;
}

// Function : takes in int[] teller and modifies passed in min and minIndex variables
//            to match min and minIndex of [] teller
// Pre: teller is initialized and numTellers in size of teller
// Post: min and minIndex hold min and index of min from teller
void findMinAndIndex(int teller[], int& min, int& minIndex, int numTellers) {
    int minTemp = teller[0];
    int minIndexTemp = 0;
    for(int i = 1; i < numTellers; i++) {
        if (teller[i] < minTemp) {
            minTemp = teller[i];
            minIndexTemp = i;
        }
    }
    min = minTemp;
    minIndex = minIndexTemp;
}

// Function : uses teller [] to calculate when customer will be processed and what expected
//            start, wait, departure, and service time will be as well as
//            updates teller accordingly
// Pre: customer, teller, and numTells have been initialized correctly
// Post: teller and customer are updated to simulate running bank
void ProcessCustomer(Customer &customer, int teller[], int numTells) {
    // assign customer to first avaliable teller
    // update teller avaliability
    // calculate customer.wait and customer.departure
    int serviceStartTime; // time when customer will be served
    int min = 0;
    int minIndex = 0;
    int numTellers = numTells;
    findMinAndIndex(teller, min, minIndex, numTellers);
    // std::cout << min << " " << minIndex << endl;
    // if arrival time >= min, teller is avaliable at arrival
    if (customer.getCustomerArrival() >= min) {
        customer.setCustomerWait(0);
        serviceStartTime = customer.getCustomerArrival();
    } else {
        customer.setCustomerWait(min - customer.getCustomerArrival());
        serviceStartTime = min;
    }
    customer.setCustomerDeparture(serviceStartTime + customer.getCustomerService());
    customer.setCustomerStart(serviceStartTime);
    customer.setCustomerService(customer.getCustomerService() +
                                customer.getCustomerWait() +
                                customer.getCustomerArrival());

    // update teller avaliability
    teller[minIndex] = customer.getCustomerDeparture();
}

int main()
{
    ofstream outFile;
	ifstream inFile;
	string cusName;
    string waste;
    int numTell;
    int numCus;
    int serviceTime;
    int arrivalTime;
    int count = 0;
    double avgWait = 10;
    bool first = true;
    streampos oldpos;

    outFile.open("outFile.txt");
	inFile.open("input.txt");

    if(!inFile)
	{
		std::cout << "error openning input file" << endl;
		return 1;
	}

    if(!outFile)
	{
		std::cout << "error openning output file" << endl;
		return 1;
	}

    // Print  name and how output will be displayed
    outFile << "This project is done by Andreas Marsh\nI will print the"
            << " wait queue every 5 customers\nand the customer currently"
            << " at teller(s) every 5 customer\n" << endl;

    //create and set numTellers and numCustomers
    inFile >> waste;
    inFile >> numTell;
    inFile >> waste;
    inFile >> numCus;

    // create queues
    QueType<Customer> leftBank(numCus);
    PriorityQueue<Customer> atTeller;
    QueType<Customer> waitQ(numCus-numTell);
    QueType<Customer> arrivalQ(numCus);

    // runs until an avgWait less than or equal to 5 is found
    while (avgWait > 5) {
        oldpos = inFile.tellg();
        // create teller array
        int tellers[numTell] = {0};

        // enque all customers to arrivalQ
        int dec = numCus;
        while (dec > 0) {
            inFile >> cusName;
            inFile >> waste;
            inFile >> arrivalTime;
            inFile >> waste;
            inFile >> serviceTime;
            Customer temp(cusName, arrivalTime, serviceTime);
            // std::cout << temp;
            try {arrivalQ.enqueue(temp);}
            catch (QueueOverflow) {
                std::cout << "oflow line 119" << endl;
                return 1;
            }
            dec--;
        }

        // loops until arrivalQ or waitQ aren't empty
        while (!arrivalQ.isEmpty() || !waitQ.isEmpty()) {
            // remove a customer from arrivalQ and update tellers
            Customer temp;
            if (!arrivalQ.isEmpty()) {
                arrivalQ.dequeue(temp);
                ProcessCustomer(temp, tellers, numTell); // processes customer
                // if no open spot at teller put customer in waitQ
                // otherwise put them at teller
                if (temp.getCustomerWait() > 0) {
                    try { waitQ.enqueue(temp); }
                    catch (QueueOverflow) {
                        std::cout << "oflow line 143" << endl;
                    }
                } else {
                    try { atTeller.enqueue(temp, temp.getCustomerDeparture()); }
                    catch (QueueOverflow) {
                        std::cout << "oflow line 148" << endl;
                    }
                }
            }
            // if people are in waitQ, check if a spot has opened at teller and
            // move first memeber of waitQ to that spot
            // as well as move person from teller to leftBank if appropriate
            while (!waitQ.isEmpty() &&
                   (temp.getCustomerArrival() > atTeller.peek().getCustomerDeparture())) {
                // remove a customer from atTeller
                Customer temp2;
                atTeller.dequeue(temp2);
                // insert customer into leftStore
                try { leftBank.enqueue(temp2); }
                catch (QueueOverflow) {
                    std::cout << "oflow line 160" << endl;
                }
                // insert peek of waitQ into atTeller
                Customer temp3;
                waitQ.dequeue(temp3);
                try { atTeller.enqueue(temp3, temp3.getCustomerDeparture()); }
                catch (QueueOverflow) {
                    std::cout << "oflow line 167" << endl;
                }
            }
            // print every 5 customers who is in wait queue
            count++;
            if (count % 5 == 0 && first) {
                outFile << "Wait Queue at customer " << count <<
                    " arrival:" << endl;
                waitQ.printQueue(outFile);
                outFile << "Teller Queue at customer " << count <<
                    " arrival:" << endl;
                atTeller.printQueue(outFile);
                outFile << "\n\n";
            }
            // if no one is entering store anymore, process remainder of
            // waitQ through teller and into leftBank
            if (arrivalQ.isEmpty()) {
                while (!waitQ.isEmpty()) {
                    // remove a customer from atTeller
                    Customer temp2;
                    atTeller.dequeue(temp2);
                    // insert customer into leftStore
                    try { leftBank.enqueue(temp2); }
                    catch (QueueOverflow) {
                        std::cout << "oflow line 160" << endl;
                    }
                    // insert peek of waitQ into atTeller
                    Customer temp3;
                    waitQ.dequeue(temp3);
                    try { atTeller.enqueue(temp3, temp3.getCustomerDeparture()); }
                    catch (QueueOverflow) {
                        std::cout << "oflow line 167" << endl;
                    }
                }
                while (!atTeller.isEmpty()) {
                    // remove a customer from atTeller
                    Customer temp4;
                    atTeller.dequeue(temp4);
                    // insert customer into priorityQ
                    try { leftBank.enqueue(temp4); }
                    catch (QueueOverflow) {
                        std::cout << "oflow line 202" << endl;
                    }
                }
            }
        }

        avgWait = 0; // resets avgWait for calculation to be performed

        // Print output on first iteration and calculates avgWait
        if (first) outFile << "Departure queue:" << endl;
        while (!leftBank.isEmpty()) {
            Customer temp3;
            leftBank.dequeue(temp3);
            avgWait += temp3.getCustomerWait();
            if (first) outFile << temp3;
        }

        // calc avgWait
        avgWait /= numCus;
        // print avgWait on first iteration
        if (first) outFile << "Average waiting time = " << avgWait << "\n\n";
        first = false;

        numTell++;
        // move back to set cursor for repeat if avgWait didn't make the cut
        inFile.seekg(oldpos);
    }
    numTell--;
    // prints number of tellers for required wait time
    outFile << "Number of tellers for required wait time is " << numTell << "\n";
    // prints closing remarks
    outFile << "\nHere's a little explination of my code:\n"
            << "My implementation assesses inputs as minutes and createas a \n"
            << "QueType arrivalQ that hold customers upon entering the store, \n"
            << "QueType waitQ that holds customers waiting to be serviced, \n"
            << "PriorityQueue atTeller that mimics customers at the tellers"
            << " and sorts them based on departure time, \n"
            << "and a QueType leftStore that holds customers once they leave\n"
            << "so that they can be printed at the end of my code in sorted order"
            << " based on departure time.\n"
            << "If you would like to see my implementation with 3 queues\n"
            << "use commands make compile2, make run2, and make clean2\n"
            << "as this will run another version of BankSimulation called BankSimulationProto\n"
            << "If you have any questions or concerns, please"
            << " email me @ andreas.marsh@uga.edu\nThank You! :)" << endl;
    return 0;
}
