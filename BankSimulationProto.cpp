/* PROTOTYPE FOR BANK SIMULATION, USE BANKSIMULATION.CPP FOR OPTIMUN OUTPUT
 */
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "QueType.cpp"
#include "PriorityQueue.cpp"
#include "Customer.h"

ostream& operator << (ostream& out, Customer& s) {
	out << s.name << " " << s.wait << "  wait  service " << s.departure << "\n";
	return out;
}
istream& operator >> (istream& in, Customer& s) {
	in >> s.name >> s.arrival >> s.service >> s.wait;
	return in;
}

// takes in int[] teller and modifies passed in min and minIndex variables
// to match min and minIndex of [] teller
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

// uses teller [] to calculate when customer will be processed and what expected
// start, wait, departure, and service time will be as well as
// updates teller accordingly
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
    customer.setCustomerDeparture(customer.getCustomerArrival() +
                                  customer.getCustomerService() +
                                  customer.getCustomerWait());
    customer.setCustomerStart(serviceStartTime);
    // customer.setCustomerService(customer.getCustomerService());

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
            << " wait queue every 5 customers\n" << endl;

    //create and set numTellers and numCustomers
    inFile >> waste;
    inFile >> numTell;
    inFile >> waste;
    inFile >> numCus;

    // create queues
    PriorityQueue<Customer> priorityQ;
    PriorityQueue<Customer> waitQ;
    QueType<Customer> arrivalQ(numCus);

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

        while (!arrivalQ.isEmpty() || !waitQ.isEmpty()) {
            // remove a customer from arrivalQ and update tellers
            Customer temp;
            if (!arrivalQ.isEmpty()) {
                arrivalQ.dequeue(temp);
                ProcessCustomer(temp, tellers, numTell);
                if (temp.getCustomerWait() > 0) {
                    try { waitQ.enqueue(temp, temp.getCustomerStart()); }
                    catch (QueueOverflow) {
                        std::cout << "oflow line 129" << endl;
                    }
                } else {
                    try { priorityQ.enqueue(temp, temp.getCustomerDeparture()); }
                    catch (QueueOverflow) {
                        std::cout << "oflow line 134" << endl;
                    }
                }
            }
            while (!waitQ.isEmpty() &&
                   (temp.getCustomerArrival() > waitQ.peek().getCustomerStart())) {
                // remove a customer from waitQ
                Customer temp2;
                waitQ.dequeue(temp2);
                // insert customer into priorityQ
                try { priorityQ.enqueue(temp2, temp2.getCustomerDeparture()); }
                catch (QueueOverflow) {
                    std::cout << "oflow line 143" << endl;
                }
            }
            count++; // print every 5 customers who is in wait queue
            if (count % 5 == 0 && first) {
                outFile << "Wait Queue at customer " << count <<
                    " arrival (in order of earliest departure):" << endl;
                waitQ.printQueue(outFile);
                outFile << "\n";
            }
            if (arrivalQ.isEmpty()) {
                while (!waitQ.isEmpty()) {
                    // remove a customer from waitQ
                    Customer temp2;
                    waitQ.dequeue(temp2);
                    // insert customer into priorityQ
                    try { priorityQ.enqueue(temp2, temp2.getCustomerDeparture()); }
                    catch (QueueOverflow) {
                        std::cout << "oflow line 143" << endl;
                    }
                }
            }
        }

        avgWait = 0;

        // Print outout on first iteration and calc avgWait
        if (first) outFile << "Departure queue:" << endl;
        while (!priorityQ.isEmpty()) {
            Customer temp3;
            priorityQ.dequeue(temp3);
            avgWait += temp3.getCustomerWait();
            if (first) outFile << temp3;
        }

        // calc avgWait
        avgWait /= numCus;
        // print avgWait
        if (first) {
            outFile << "Average waiting time = " << avgWait << "\n\n";
            numTell = 0;
            avgWait = 6;
        }
        first = false;
        numTell++;
        // move back to set cursor for repeat
        inFile.seekg(oldpos);
    }
    numTell--;
    // find number of tellers for required wait time
    outFile << "Number of tellers for required wait time is " << numTell << "\n";
    return 0;
}
