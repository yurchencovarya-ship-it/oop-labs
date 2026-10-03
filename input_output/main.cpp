#include <iostream>
#include <string>
#include "smarthome.h"
#include <windows.h>
using namespace std;
int main() {

    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    SmartHome myHome("Загородный дом");
    while (true) {
        cout << "\nМеню Умного дома" << endl;
        cout << "1. Показать все устройства" << endl;
        cout << "2. Добавить умную лампу" << endl;
        cout << "3. Добавить умный термостат" << endl;
        cout << "4. Найти устройство по названию" << endl;
        cout << "5. Изменить энергопотребление устройства" << endl;
        cout << "6. Удалить устройство по ID" << endl;
        cout << "7. Сортировать устройства по ID" << endl;
        cout << "0. Выход" << endl;

        int choice = readInt("Выберите действие: ");
        switch (choice) {
        case 1: {
            myHome.displayTable(cout);
            break;
        }
        case 2: {
            cout << "Добавление умной лампы" << endl;
            int id = readInt("Введите ID устройства: ");
            string name;
            cout << "Введите название устройства (например, 'Лампа в гостиной'): ";
            getline(cin, name);
            int statusInt = readInt("Состояние (1 - вкл, 0 - выкл): ");
            bool status = (statusInt != 0);
            double power = readInt("Введите энергопотребление (Вт): ");
            int brightness = readInt("Введите яркость (0-100%): ");

            myHome.addDevice(new SmartLight(name, status, id, power, brightness));
            cout << "Умная лампа успешно добавлена!" << endl;
            break;
        }
        case 3: {
            cout << "Добавление умного термостата" << endl;
            int id = readInt("Введите ID устройства: ");
            string name;
            cout << "Введите название устройства (например, 'Термостат спальни'): ";
            getline(cin, name);
            int statusInt = readInt("Состояние (1 - вкл, 0 - выкл): ");
            bool status = (statusInt != 0);
            double power = readInt("Введите энергопотребление (Вт): ");
            cout << "Введите целевую температуру (°C): ";
            double temp;
            cin >> temp;
            cin.ignore(1000, '\n');
            myHome.addDevice(new SmartThermostat(name, status, id, power, temp));
            cout << "Умный термостат успешно добавлен!" << endl;
            break;
        }
        case 4: {
            cout << "Поиск устройства" << endl;
            string searchName;
            cout << "Введите название для поиска: ";
            getline(cin, searchName);
            myHome.searchDevice(searchName);
            break;
        }
        case 5: {
            cout << "Изменение энергопотребления" << endl;
            int id = readInt("Введите ID устройства: ");
            double newPower = readInt("Введите новое энергопотребление (Вт): ");
            myHome.editDevice(id, newPower);
            break;
        }
        case 6: {
            cout << "Удаление устройства" << endl;
            int id = readInt("Введите ID для удаления: ");
            myHome.removeDevice(id);
            break;
        }
        case 7: {
            cout << "Устройства отсортированы по ID" << endl;
            myHome.sortDevices();
            break;
        }
        case 0: {
            cout << "Завершение работы программы..." << endl;
            return 0;
        }
        default: {
            cout << "Неверный пункт меню! Попробуйте снова" << endl;
            break;
        }
        }
    }
}
