#include "address.h"
using namespace std;
Address::Address()
    : city("Минск"), street("Ленина"), houseNumber(1), apartmentNumber(1) {
}
Address::Address(const string& c, const string& s, int h, int a)
    : city(c), street(s), houseNumber(h), apartmentNumber(a) {
}
void Address::display() const {
    cout << "г. " << city << ", ул. " << street
        << ", д. " << houseNumber << ", кв. " << apartmentNumber;
}
string Address::getCity() const { return city; }
string Address::getStreet() const { return street; }
int Address::getHouseNumber() const { return houseNumber; }
int Address::getApartmentNumber() const { return apartmentNumber; }