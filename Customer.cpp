// Customer class member and friend function definition
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>

#include "Customer.h" // Customer class definition
using namespace std;

// Customer class parameters
string name;
int arrival;
int service;
int wait;
int start;
int departure;

// Function: constructor for class Customer
// Pre: all ints are 0 or greater
// Post: Custimer is initialized
Customer::Customer(string namez, int arrivalz, int servicez,
                   int waitz, int startz, int departurez) {
    name = namez;
    arrival = arrivalz;
    service = servicez;
    wait = waitz;
    start = startz;
    departure = departurez;
}

// Function: constructor for class Customer
// Pre: all ints are 0 or greater
// Post: Custimer is initialized
Customer::Customer(string namez, int arrivalz, int servicez, int waitz) {
    name = namez;
    arrival = arrivalz;
    service = servicez;
    wait = waitz;
    start = 0;
    departure = 0;
}

// Function: constructor for class Customer
// Pre: all ints are 0 or greater
// Post: Custimer is initialized
Customer::Customer(string namez, int arrivalz, int servicez) {
    name = namez;
    arrival = arrivalz;
    service = servicez;
    wait = 0;
    start = 0;
    departure = 0;
}

// Function: constructor for class Customer
// Pre: None
// Post: Custimer is initialized
Customer::Customer() {
    name = "error";
    arrival = 0;
    service = 0;
    wait = 0;
    start = 0;
    departure = 0;
}

// Function: returns custoemrName
// Pre: Customer is initialized
// Post: returns name
const string Customer::getCustomerName() const {
    return name;
}

// Function: returns customerArrival
// Pre: Customer is initialized
// Post: returns arrival
const int Customer::getCustomerArrival() const {
    return arrival;
}

// Function: returns customerService
// Pre: Customer is initialized
// Post: returns service
const int Customer::getCustomerService() const {
    return service;
}

// Function: returns customerWait
// Pre: Customer is initialized
// Post: returns wait
const int Customer::getCustomerWait() const {
    return wait;
}

// Function: returns customerStart
// Pre: Customer is initialized
// Post: returns start
const int Customer::getCustomerStart() const {
    return start;
}

// Function: returns customerDeparture
// Pre: Customer is initialized
// Post: returns departure
const int Customer::getCustomerDeparture() const {
    return departure;
}

// Function: sets customerName
// Post: Customer's name is set
void Customer::setCustomerName(string customerNamez) {
    name = customerNamez;
}

// Function: sets customerArrival
// Pre: parameter value is 0 or greater and in the value of int minutes
// Post: Customer's arrival is set
void Customer::setCustomerArrival(int customerArrivalz) {
    arrival = customerArrivalz;
}

// Function: sets customerService
// Pre: parameter value is 0 or greater and in the value of int minutes
// Post: Customer's service is set
void Customer::setCustomerService(int customerServicez) {
    service = customerServicez;
}

// Function: sets customerWait
// Pre: parameter value is 0 or greater and in the value of int minutes
// Post: Customer's wait is set
void Customer::setCustomerWait(int customerWaitz) {
    wait = customerWaitz;
}

// Function: sets customerStart
// Pre: parameter value is 0 or greater and in the value of int minutes
// Post: Customer's start is set
void Customer::setCustomerStart(int customerStartz) {
    start = customerStartz;
}

// Function: sets customerDeparture
// Pre: parameter value is 0 or greater and in the value of int minutes
// Post: Customer's departure is set
void Customer::setCustomerDeparture(int customerDeparturez) {
    departure = customerDeparturez;
}

// Function: sees if two Customers have same arrival
// Post: returns if both customer have same arrival time or not
bool Customer::equals(const Customer &s) const {
    if (getCustomerArrival() == s.getCustomerArrival()) {
        return true;
    } else {
        return false;
    }
}

// Function: sees if Customer calling has earlier arrival
// Post: return true if Customer calling has earlier arrival, false otherwise
bool Customer::lesser(const Customer &s) const {
    if (getCustomerArrival() < s.getCustomerArrival()) {
        return true;
    } else {
        return false;
    }
}

// Function: sees if Customer calling has later arrival
// Post: returns true if customer calling has later arrival time, false otherwise
bool Customer::greater(const Customer &s) const {
    if (getCustomerArrival() > s.getCustomerArrival()) {
        return true;
    } else {
        return false;
    }
}

// overide of == operator
bool Customer::operator==(const Customer& s) const {
    bool temp = this->equals(s);
    return temp;
}
/*
// overide of == operator
bool Customer::operator==(const long int s) const {
    if this->
    return temp;
    }*/

// overide of != operator
bool Customer::operator!=(const Customer& s) const {
    bool temp = !(this->equals(s));
    return temp;
}

// overide of < operator
bool Customer::operator<(const Customer& s) const {
    bool temp = this->lesser(s);
    return temp;
}

// overide of > operator
bool Customer::operator>(const Customer& s) const {
    bool temp = this->greater(s);
    return temp;
}

/*ostream& operator<<(ostream& out, const Student&) {
  out << getStudentID() << " " << getStudentName();
  return out;
  } */
