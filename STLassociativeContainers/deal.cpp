#include "deal.h"
#include <iomanip>
using namespace std;

Deal::Deal() : dealId(0), dealType("Продажа") {}
Deal::Deal(int id, const string& dt, const Property& prop, const Person& cl, const Agent& ag)
    : dealId(id), dealType(dt), property(prop), client(cl), agent(ag) {
}
void Deal::displayTable() const {
    std::cout << "\nСделка номер " << dealId
        << " | Тип: " << dealType
        << " | Клиент: " << client.getName()
        << " | Агент: " << agent.getName()
        << " | Объект: " << property.getType()
        << " | Цена: $" << property.getPrice() << "\n";
}
void Deal::displayFull() const {
    cout << "ID сделки: " << dealId << "\n"
        << "Тип сделки: " << dealType << "\n"
        << "Клиент: " << client.getName() << " (" << client.getPhone() << ")\n"
        << "Агент: " << agent.getName() << " (ID: " << agent.getId() << ")\n"
        << "Объект: " << property.getType() << ", Площадь: " << property.getArea() << " кв.м, Цена: $" << property.getPrice() << "\n"
        << "Адрес: г. " << property.getAddress().getCity() << ", ул. " << property.getAddress().getStreet()
        << ", д. " << property.getAddress().getHouseNumber() << ", кв. " << property.getAddress().getApartmentNumber() << "\n";
}
int Deal::getId() const { return dealId; }
string Deal::getDealType() const { return dealType; }
Property Deal::getProperty() const { return property; }
Person Deal::getClient() const { return client; }
Agent Deal::getAgent() const { return agent; }
void Deal::setDealType(const string& dt) { dealType = dt; }
void Deal::setPrice(double newPrice) {
    property.setPrice(newPrice);
}