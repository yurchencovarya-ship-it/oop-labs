#include "Airline.h"
#include <windows.h>

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    Flight flight;
    int choice = 0;
    string filename = "flight.txt";
    int empId = 0;
    string keyword;
    do {
        cout << "==============================\n";
        cout << "       МЕНЮ УПРАВЛЕНИЯ РЕЙСОМ       \n";
        cout << "==============================\n";
        cout << "1. Создать/заполнить новый рейс\n";
        cout << "2. Показать информацию о рейсе (в памяти)\n";
        cout << "3. Сохранить данные в файл (перезапись)\n";
        cout << "4. Загрузить данные из файла\n";
        cout << "5. Добавить сотрудника в файл\n";
        cout << "6. Удалить сотрудника из файла по ID\n";
        cout << "7. Редактировать сотрудника в файле по ID\n";
        cout << "8. Просмотр «сырых» данных файла\n";
        cout << "9. Поиск данных в файле\n";
        cout << "10. Выход\n";
        cout << "------------------------------\n";
        cout << "Выберите пункт меню (1-10): ";
        if (!(cin >> choice)) {
            cout << "Ошибка ввода! Пожалуйста, введите число от 1 до 10\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        switch (choice) {
        case 1:
            flight.createFlight();
            break;
        case 2:
            flight.showFlightInfo();
            break;
        case 3:
            cout << "Введите имя файла для сохранения (например, flight.txt): ";
            cin >> filename;
            flight.saveToFile(filename);
            break;
        case 4:
            cout << "Введите имя файла для загрузки (например, flight.txt): ";
            cin >> filename;
            flight.readFromFile(filename);
            break;
        case 5:
            cout << "Введите имя файла для добавления: ";
            cin >> filename;
            flight.appendToFile(filename);
            break;
        case 6:
            cout << "Введите имя файла: ";
            cin >> filename;
            cout << "Введите табельный номер (ID) сотрудника для удаления: ";
            cin >> empId;
            flight.deleteFromFile(filename, empId);
            break;
        case 7:
            cout << "Введите имя файла: ";
            cin >> filename;
            cout << "Введите табельный номер (ID) сотрудника для редактирования: ";
            cin >> empId;
            flight.editInFile(filename, empId);
            break;
        case 8:
            cout << "Введите имя файла для просмотра: ";
            cin >> filename;
            flight.viewFileRaw(filename);
            break;
        case 9:
            cout << "Введите имя файла для поиска: ";
            cin >> filename;
            cout << "Введите ключевое слово (например, фамилию или ID): ";
            cin >> keyword;
            flight.searchInFile(filename, keyword);
            break;
        case 10:
            cout << "Выход из программы. До свидания!\n";
            break;
        default:
            cout << "Неверный выбор! Пожалуйста, выберите пункт от 1 до 10.\n";
        }
    } while (choice != 10);
    return 0;
}
