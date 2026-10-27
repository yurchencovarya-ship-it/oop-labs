#include"property.h"
using namespace std;
Property::Property()
    : type("Квартира"), area(35.0), price(50000.0), address() {
}
Property::Property(const string& t, double ar, double pr, const Address& addr)
    : type(t), area(ar), price(pr), address(addr) {
}

void Property::display() const {
    cout << "Тип: " << type << ", Площадь: " << area
        << " кв.м., Цена: $" << price << ", Адрес: ";
    address.display();
}
string Property::getType() const { return type; }
double Property::getArea() const { return area; }
double Property::getPrice() const { return price; }
Address Property::getAddress() const { return address; }
void Property::setPrice(double pr) { price = pr; }