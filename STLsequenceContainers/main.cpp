#include <iostream>
#include "ListMenu.h"   
#include "VectorMenu.h"
#include "ArrayMenu.h"
#include <windows.h>
using namespace std;

int main() {
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);
    int choice = 0;
    do {
        cout << "-------------------------------------------------"<<endl;
        cout << "  Учет сделок по продаже и покупке недвижимости "<<endl;
        cout << "-------------------------------------------------"<<endl;
        cout << "1. Работа со списком (list<Agent>)"<<endl;
        cout << "2. Работа с вектором (vector<Deal>)"<<endl;
        cout << "3. Работа с массивом (array)"<<endl;
        cout << "0. Выход из программы"<<endl;
        cout << "-----------------------------------------"<<endl;
        cout << "Выберите пункт меню: ";
        cin >> choice;
        switch (choice) {
        case 1:
            menuList();
            break;
        case 2:
            menuVector();
            break;
        case 3:
            menuArray();
            break;
        case 0:
            cout << "\nПрограмма завершена :)"<<endl;
            break;
        default:
            cout << "\nОшибка: некорректный ввод! Выберите пункт от 0 до 3"<<endl;
            break;
        }
    } while (choice != 0);
    return 0;
}