#pragma once
#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "agent.h"
using namespace std;
#include"ListMenu.h"
void saveListToFile(const string& filename, const list<Agent>& agents) {
    ofstream ouf(filename, ios::out | ios::trunc);
    if (!ouf.is_open() || ouf.bad()) return;
    ouf << agents.size() << "\n";
    for (const auto& ag : agents) {
        ouf << ag.getId() << ";" << ag.getName() << ";" << ag.getPhone() << ";" << ag.getExperienceYears() << endl;
    }
    ouf.close();
}
void loadListFromFile(const string& filename, list<Agent>& agents) {
    ifstream inf(filename, ios::in);
    if (!inf.is_open()) return;
    if (inf.peek() == EOF) { inf.close(); return; }
    agents.clear();
    size_t size = 0;
    inf >> size;
    inf.ignore(1000, '\n');
    for (int i = 0; i < size; i++) {
        if (inf.eof() || inf.fail()) break;
        string line;
        getline(inf, line);
        if (line.empty()) continue;

        stringstream ss(line);
        string idStr, name, phone, expStr;
        getline(ss, idStr, ';');
        getline(ss, name, ';');
        getline(ss, phone, ';');
        getline(ss, expStr, ';');
        agents.push_back(Agent(name, phone, stoi(idStr), stod(expStr)));
    }
    inf.close();
}
void menuList() {
    list<Agent> agents;
    string filename = "agents.txt";
    loadListFromFile(filename, agents);
    int choice;
    do {
        cout << "\n--- Меню list (Штат агентов) ---" << endl;
        cout << "1. Просмотр всех агентов (на экран и в файл)" << endl;
        cout << "2. Добавить агента" << endl;
        cout << "3. Редактировать агента по ID" << endl;
        cout << "4. Удалить агента" << endl;
        cout << "5. Найти агента по ID" << endl;
        cout << "6. Сортировать агентов по стажу" << endl;
        cout << "0. Назад в главное меню" << endl;
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "\nШтат агентов (всего: " << agents.size() << "): " << endl;
            for (const auto& ag : agents) {
                cout << " - " << ag << endl;
            }
            saveListToFile(filename, agents);
            break;
        case 2: {
            string name, phone; int id, pos; double exp;
            cout << "Куда добавить? (1 - в начало, 2 - в конец): "; cin >> pos;
            cout << "ФИО агента: "; cin.ignore(); getline(cin, name);
            cout << "Телефон: "; cin >> phone;
            cout << "ID: "; cin >> id;
            cout << "Стаж (лет): "; cin >> exp;

            Agent newAg(name, phone, id, exp);
            if (pos == 1) agents.push_front(newAg);
            else agents.push_back(newAg);
            saveListToFile(filename, agents);
            cout << "Агент добавлен!" << endl;
            break;
        }
        case 3: {
            int id; cout << "Введите ID для редактирования: "; cin >> id;
            bool found = false;
            for (auto& ag : agents) {
                if (ag.getId() == id) {
                    string n, p; double e;
                    cout << "Новое ФИО: "; cin.ignore(); getline(cin, n);
                    cout << "Новый телефон: "; cin >> p;
                    cout << "Новый стаж: "; cin >> e;
                    ag = Agent(n, p, id, e);
                    found = true;
                    break;
                }
            }
            if (found) {
                saveListToFile(filename, agents);
                cout << "Данные обновлены!" << endl;
            }
            else cout << "Агент не найден" << endl;
            break;
        }
        case 4: {
            int sub; cout << "Удалить\n 1 - первого\n 2 - последнего\n 3 - по ID: \n";
            cin >> sub;
            if (agents.empty()) { cout << "Список пуст!" << endl; break; }
            if (sub == 1) agents.pop_front();
            else if (sub == 2) agents.pop_back();
            else if (sub == 3) {
                int id; cout << "Введите ID для удаления: "; cin >> id;
                agents.remove_if([id](const Agent& a) { return a.getId() == id; });
            }
            saveListToFile(filename, agents);
            cout << "Удаление выполнено" << endl;
            break;
        }
        case 5: {
            int id; cout << "Введите ID для поиска: "; cin >> id;
            bool found = false;
            for (const auto& ag : agents) {
                if (ag.getId() == id) {
                    cout << "Найден: " << ag << endl;
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Агент не найден" << endl;
            break;
        }
        case 6:
            agents.sort([](const Agent& a, const Agent& b) {
                return a.getExperienceYears() < b.getExperienceYears();
                });
            saveListToFile(filename, agents);
            cout << "Агенты отсортированы!" << endl;
            break;
        case 0:
            break;
        default:
            cout << "Неверный выбор" << endl;
        }
    } while (choice != 0);
}