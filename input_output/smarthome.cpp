#include"smarthome.h"
#include <string>
#include <iostream>
using namespace std;
int readInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (!cin.fail()) {
            cin.ignore(1000, '\n');//очищаем буфер ввода от оставшегося символа перевода строки
            return value;
        }
        cin.clear();//сбрасываем флаг ошибки у потока cin
        cin.ignore(1000, '\n');//выбрасываем из буфера ввода некорректно введённый мусор (буквы или знаки)
        cout << "Ошибка! Введите целое число" << endl;
    }
}
SmartDevice::SmartDevice(string n, bool status) {
    name = n;
    isOn = status;
}
SmartDevice::~SmartDevice() {}
string SmartDevice::getName() const {
    return name;
}
bool SmartDevice::getStatus() const {
    return isOn;
}
ElectricalDevice::ElectricalDevice(string n, bool status, int i, double power) : SmartDevice(n, status) {
    id = i;
    powerConsumption = power;
}
int ElectricalDevice::getId() const {
    return id;
}
double ElectricalDevice::getPowerConsumption() const {
    return powerConsumption;
}
void ElectricalDevice::setPowerConsumption(double power) {
    powerConsumption = power;
}
SmartLight::SmartLight(string n, bool status, int i, double power, int bright) : ElectricalDevice(n, status, i, power) {
    brightness = bright;
}
string SmartLight::getDeviceType() const {
    return "Лампа";
}
void SmartLight::printRow(ostream& os) const { // os - поток вывода
    os.setf(ios::left); // флаг выравнивает по левому краю
    os << setw(6) << id // задает ширину
        << setw(20) << name
        << setw(12) << getDeviceType()
        << setw(10) << (isOn ? "Вкл" : "Выкл");
    os.setf(ios::fixed); // фиксированный формат чисел
    os.precision(2); // точность вывода числа (2 знака после запятой)
    os << setw(14) << powerConsumption
        << "Яркость: " << brightness << "%" << endl;
}
SmartThermostat::SmartThermostat(string n, bool status, int i, double power, double temp) : ElectricalDevice(n, status, i, power) {
    targetTemperature = temp;
}
string SmartThermostat::getDeviceType() const {
    return "Термостат";
}
void SmartThermostat::printRow(ostream& os) const {
    os.setf(ios::left);
    os << setw(6) << id
        << setw(20) << name
        << setw(12) << getDeviceType()
        << setw(10) << (isOn ? "Вкл" : "Выкл");
    os.setf(ios::fixed);
    os.precision(2);
    os << setw(14) << powerConsumption
        << "Цель: " << targetTemperature << " °C" << endl;
}
SmartHome::SmartHome(string hName) {
    homeName = hName;
    count = 0;
    capacity = 5;
    devices = new ElectricalDevice * [capacity];
}
SmartHome::~SmartHome() {
    for (int i = 0; i < count; i++) {
        delete devices[i];
    }
    delete[] devices;
}
void SmartHome::resize() {
    capacity = capacity * 2; // емкость увеличивается в 2 раза
    ElectricalDevice** newDevices = new ElectricalDevice * [capacity];
    for (int i = 0; i < count; i++) {
        newDevices[i] = devices[i];
    }
    delete[] devices;
    devices = newDevices;
}
void SmartHome::addDevice(ElectricalDevice* dev) {
    if (count >= capacity) {
        resize();
    }
    devices[count] = dev;
    count++;
}
void SmartHome::removeDevice(int id) {
    int index = -1;
    for (int i = 0; i < count; i++) {
        if (devices[i]->getId() == id) {
            index = i;
            break;
        }
    }
    if (index != -1) {
        delete devices[index];
        for (int i = index; i < count - 1; i++) {
            devices[i] = devices[i + 1];
        }
        count--;
        cout << "Устройство успешно удалено" << endl;
    }
    else {
        cout << "Устройство с таким ID не найдено" << endl;
    }
}
void SmartHome::editDevice(int id, double newPower) {
    bool found = false;
    for (int i = 0; i < count; i++) {
        if (devices[i]->getId() == id) {
            devices[i]->setPowerConsumption(newPower);
            cout << "Энергопотребление устройства с ID " << id << " успешно изменено на " << newPower << " Вт" << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Устройство с ID " << id << " не найдено" << endl;
    }
}
void SmartHome::sortDevices() {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (devices[j]->getId() > devices[j + 1]->getId()) {
                ElectricalDevice* temp = devices[j];
                devices[j] = devices[j + 1];
                devices[j + 1] = temp;
            }
        }
    }
    cout << "Устройства отсортированы по ID" << endl;
}
void SmartHome::searchDevice(const string& searchName) const {
    cout << "\nРезультаты поиска:" << endl;
    bool found = false;
    for (int i = 0; i < count; i++) {
        if (devices[i]->getName() == searchName) {
            devices[i]->printRow(cout);
            found = true;
        }
    }
    if (!found) {
        cout << "Совпадений не найдено" << endl;
    }
}
void SmartHome::displayTable(ostream& os) const {
    os << " СИСТЕМА УМНЫЙ ДОМ: " << homeName << endl;
    os << setfill('-'); // меняет символ-заполнитель для пустого пространства
    os << setw(72) << "-" << endl;
    os << setfill(' '); // возвращает символ-заполнитель обратно на пробел
    os.setf(ios::left);
    os.setf(ios::showpoint); // заставляет поток всегда выводить хвост с нулями
    os << setw(6) << "ID"
        << setw(30) << "Название"
        << setw(20) << "Тип"
        << setw(10) << "Статус"
        << setw(14) << "Мощность(Вт)"
        << "Доп. инфо" << endl;
    os << setfill('-');
    os << setw(72) << "-" << "\n";
    os << setfill(' ');
    for (int i = 0; i < count; i++) {
        devices[i]->printRow(os);
    }
    os << setfill('-');
    os << setw(72) << "-" << "\n\n";
    os << setfill(' ');
}
