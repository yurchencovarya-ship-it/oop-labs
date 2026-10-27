#include <iostream>
#include <map>
#include "deal.h"
#include "MapMenu.h"
#include "MultimapMenu.h"
#include "SetMenu.h"
#include <windows.h>

using namespace std;

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    map<int, Deal> mainDealsMap;
    loadMapFromFile("deals_map.txt", mainDealsMap);

    int choice = 0;
    do {
        cout << "=========================================================" << endl;
        cout << " Учет сделок по продаже и покупке недвижимости    " << endl;
        cout << "=========================================================" << endl;
        cout << "1. Работа с картой сделок (map)" << endl;
        cout << "2. Работа с мультикартой (multimap)" << endl;
        cout << "3. Работа с множеством (set)" << endl;
        cout << "0. Выход из программы" << endl;
        cout << "Выберите пункт меню: ";
        cin >> choice;
        switch (choice) {
        case 1:
            menuMap();
            break;
        case 2:
            menuMultimap(mainDealsMap);
            break;
        case 3:
            menuSet(mainDealsMap);
            break;
        case 0:
            cout << "\nПрограмма завершена :)" << endl;
            break;
        default:
            cout << "\nОшибка: некорректный ввод!" << endl;
            break;
        }
    } while (choice != 0);
    return 0;
}