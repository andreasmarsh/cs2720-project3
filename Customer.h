#pragma once

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <string>
using namespace std;

class Customer {

public:

    // Function: constructor for class Customer
    // Pre: all ints are 0 or greater
    // Post: Custimer is initialized
    Customer(string namez, int arrivalz, int servicez,
             int waitz, int startz, int departurez);

    // Function: constructor for class Customer
    // Pre: all ints are 0 or greater
    // Post: Custimer is initialized
    Customer(string namez, int arrivalz, int servicez, int waitz);

    // Function: constructor for class Customer
    // Pre: all ints are 0 or greater
    // Post: Custimer is initialized
    Customer(string namez, int arrivalz, int servicez);

    // Function: constructor for class Customer
    // Pre: none
    // Post: Custimer is initialized
    Customer();


    // Function: returns custoemrName
    // Pre: Customer is initialized
    // Post: returns name
    const string getCustomerName() const; // returns customerName

    // Function: returns customerArrival
    // Pre: Customer is initialized
    // Post: returns arrival
    const int getCustomerArrival() const; // returns customerArrival

    // Function: returns customerService
    // Pre: Customer is initialized
    // Post: returns service
    const int getCustomerService() const; // returns customerService

    // Function: returns customerWait
    // Pre: Customer is initialized
    // Post: returns wait
    const int getCustomerWait() const; // returns customerWait

    // Function: returns customerStart
    // Pre: Customer is initialized
    // Post: returns start
    const int getCustomerStart() const; // returns customerStart

    // Function: returns customerDeparture
    // Pre: Customer is initialized
    // Post: returns departure
    const int getCustomerDeparture() const; // returns customerDeparture

    // Function: sets customerName
    // Post: Customer's name is set
    void setCustomerName(string customerNamez); // sets customerName

    // Function: sets customerArrival
    // Pre: parameter value is 0 or greater and in the value of int minutes
    // Post: Customer's arrival is set
    void setCustomerArrival(int customerArrivalz); // sets customerArrival

    // Function: sets customerService
    // Pre: parameter value is 0 or greater and in the value of int minutes
    // Post: Customer's service is set
    void setCustomerService(int customerServicez); // sets customerService

    // Function: sets customerWait
    // Pre: parameter value is 0 or greater and in the value of int minutes
    // Post: Customer's wait is set
    void setCustomerWait(int customerWaitz); // sets customerWait

    // Function: sets customerStart
    // Pre: parameter value is 0 or greater and in the value of int minutes
    // Post: Customer's start is set
    void setCustomerStart(int customerStartz); // sets customerStart

    // Function: sets customerDeparture
    // Pre: parameter value is 0 or greater and in the value of int minutes
    // Post: Customer's departure is set
    void setCustomerDeparture(int customerDeparturez); // sets customerDeparture


    // Function: sees if two Customers have same arrival
    // Post: returns if both customer have same arrival time or not
    bool equals(const Customer & s) const;

    // Function: sees if Customer calling has earlier arrival
    // Post: return true if Customer calling has earlier arrival, false otherwise
    bool lesser(const Customer & s) const;

    // Function: sees if Customer calling has later arrival
    // Post: returns true if customer calling has later arrival time, false otherwise
    bool greater(const Customer & s) const;

    // overide of == operator
    bool operator==(const Customer &s) const;

    // overide of != operator
    bool operator!=(const Customer &s) const;

    // overide of < operator
    bool operator<(const Customer &s) const;

    // overide of > operator
    bool operator>(const Customer &s) const;

// Customer parameters
private:
    string name;
    int arrival;
    int service;
    int wait;
    int start;
    int departure;

    // friend overides of >> and << operators
    friend ostream& operator << (ostream& out, Customer&);
    friend istream& operator >> (istream& in, Customer&s);
};
#endif
