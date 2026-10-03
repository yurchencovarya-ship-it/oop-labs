#include "Airline.h"

// Перегрузка операторов вывода и ввода для Employee
ostream& operator<<(ostream& os, const Employee& emp) {
    emp.putData();
    return os;
}
istream& operator>>(istream& is, Employee& emp) {
    emp.getData();
    return is;
}
// РАБОТНИК
Employee::Employee() {
    name = "Неизвестно";
    id = 0;
}
Employee::Employee(const string& name, int id) {
    this->name = name;
    this->id = id;
}
Employee::Employee(const Employee& other) {
    name = other.name;
    id = other.id;
}
Employee::~Employee() {}
void Employee::getData() {
    cin.ignore(1000, '\n');
    cout << "Введите ФИО сотрудника: ";
    getline(cin, name);
    cout << "Введите табельный номер: " << endl;
    cin >> id;
}
void Employee::putData() const {
    cout << "ФИО: " << name << endl;
    cout << "Табельный номер: " << id << endl;
}
void Employee::saveData(ofstream& ouf) const {
    ouf << name << endl << id << endl;
}
void Employee::loadData(ifstream& inf) {
    inf.ignore(1000, '\n');
    getline(inf, name);
    inf >> id;
}
// ПИЛОТ 
Pilot::Pilot() : Employee() {
    flightHours = 0;
}
Pilot::Pilot(const string& name, int id, int flightHours) : Employee(name, id) {
    this->flightHours = flightHours;
}
Pilot::Pilot(const Pilot& other) : Employee(other) {
    flightHours = other.flightHours;
}
Pilot::~Pilot() {}
void Pilot::getData() {
    Employee::getData();
    cout << "Введите общий налет часов: " << endl;
    cin >> flightHours;
}
void Pilot::putData() const {
    Employee::putData();
    cout << "Должность: Пилот" << endl;
    cout << "Налет часов: " << flightHours << endl;
}
void Pilot::saveData(ofstream& ouf) const {
    Employee::saveData(ouf);
    ouf << flightHours << endl;
}
void Pilot::loadData(ifstream& inf) {
    Employee::loadData(inf);
    inf >> flightHours;
}
// СТЮАРДЕССА
FlightAttendant::FlightAttendant() : Employee() {
    speaksEnglish = true;
}
FlightAttendant::FlightAttendant(const string& name, int id, bool speaksEnglish) : Employee(name, id) {
    this->speaksEnglish = speaksEnglish;
}
FlightAttendant::FlightAttendant(const FlightAttendant& other) : Employee(other) {
    speaksEnglish = other.speaksEnglish;
}
FlightAttendant::~FlightAttendant() {}
void FlightAttendant::getData() {
    Employee::getData();
    cout << "Владеет английским языком (1 - да, 0 - нет): " << endl;
    cin >> speaksEnglish;
}
void FlightAttendant::putData() const {
    Employee::putData();
    cout << "Должность: Бортпроводник" << endl;
    cout << "Знание английского: " << (speaksEnglish ? "Да" : "Нет") << endl;
}
void FlightAttendant::saveData(ofstream& ouf) const {
    Employee::saveData(ouf);
    ouf << speaksEnglish << endl;
}
void FlightAttendant::loadData(ifstream& inf) {
    Employee::loadData(inf);
    inf >> speaksEnglish;
}
// ИНЖЕНЕР 
Engineer::Engineer() : Employee() {
    specialization = "Общая";
}
Engineer::Engineer(const string& name, int id, const string& spec) : Employee(name, id) {
    specialization = spec;
}
Engineer::Engineer(const Engineer& other) : Employee(other) {
    specialization = other.specialization;
}
Engineer::~Engineer() {}
void Engineer::getData() {
    Employee::getData();
    cin.ignore(1000, '\n');
    cout << "Введите специализацию (например, Авионика): ";
    getline(cin, specialization);
}
void Engineer::putData() const {
    Employee::putData();
    cout << "\nДолжность: Инженер" << endl;
    cout << "Специализация: " << specialization << endl;
}
void Engineer::saveData(ofstream& ouf) const {
    Employee::saveData(ouf);
    ouf << specialization << endl;
}
void Engineer::loadData(ifstream& inf) {
    Employee::loadData(inf);
    inf.ignore(1000, '\n');
    getline(inf, specialization);
}
// ПОЛЕТ (ЭКИПАЖ)
Flight::Flight() {
    flightNumber = "AB-000";
    destination = "Не указан";
    crewSize = 0;
    for (int i = 0; i < MAX_CREW; ++i) {
        crew[i] = nullptr;
    }
}
Flight::Flight(const string& flightNum, const string& dest) {
    flightNumber = flightNum;
    destination = dest;
    crewSize = 0;
    for (int i = 0; i < MAX_CREW; ++i) {
        crew[i] = nullptr;
    }
}
Flight::Flight(const Flight& other) {
    flightNumber = other.flightNumber;
    destination = other.destination;
    crewSize = other.crewSize;
    for (int i = 0; i < MAX_CREW; ++i) {
        if (i >= crewSize || other.crew[i] == nullptr) {
            crew[i] = nullptr;
            continue;
        }
        if (typeid(*other.crew[i]) == typeid(Pilot)) {
            crew[i] = new Pilot(*dynamic_cast<Pilot*>(other.crew[i]));
        }
        else if (typeid(*other.crew[i]) == typeid(FlightAttendant)) {
            crew[i] = new FlightAttendant(*dynamic_cast<FlightAttendant*>(other.crew[i]));
        }
        else if (typeid(*other.crew[i]) == typeid(Engineer)) {
            crew[i] = new Engineer(*dynamic_cast<Engineer*>(other.crew[i]));
        }
        else {
            crew[i] = nullptr;
        }
    }
}
Flight::~Flight() {
    for (int i = 0; i < crewSize; ++i) {
        delete crew[i];
    }
}
void Flight::createFlight() {
    for (int i = 0; i < crewSize; ++i) {
        delete crew[i];
        crew[i] = nullptr;
    }
    crewSize = 0;
    cin.ignore(1000, '\n');
    cout << "Введите номер рейса: ";
    getline(cin, flightNumber);
    cout << "Введите пункт назначения: ";
    getline(cin, destination);
    char choice = 'y';
    do {
        if (crewSize >= MAX_CREW) {
            cout << "Достигнут лимит экипажа!" << endl;
            break;
        }
        cout << "-- Добавление сотрудника в экипаж --" << endl;
        cout << "1 - Пилот" << endl;
        cout << "2 - Бортпроводник" << endl;
        cout << "3 - Инженер" << endl;
        cout << "Выберите тип сотрудника (1-3): " << endl;
        int typeChoice;
        if (!(cin >> typeChoice)) {
            cout << "Ошибка ввода!" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        Employee* emp = nullptr;
        if (typeChoice == 1) emp = new Pilot();
        else if (typeChoice == 2) emp = new FlightAttendant();
        else if (typeChoice == 3) emp = new Engineer();
        else {
            cout << "Неверный выбор!" << endl;
            continue;
        }
        cin >> *emp;
        crew[crewSize++] = emp;
        cout << "Добавить еще сотрудника? (y/n): " << endl;
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');
}
void Flight::showFlightInfo() const {
    cout << "------------------------------------------------" << endl;
    cout << "Рейс номер: " << flightNumber << " | Назначение: " << destination << endl;
    cout << "Состав экипажа (" << crewSize << " чел.):" << endl;
    for (int i = 0; i < crewSize; ++i) {
        cout << "----------------------------------------" << endl;
        if (crew[i] != nullptr) {
            cout << *crew[i];
        }
        cout << endl;
    }
    cout << "--------------------------------------------------" << endl;
}
void Flight::saveToFile(const string& filename) const {
    ofstream ouf;
    ouf.open(filename, ios::out);
    if (!ouf.is_open() || ouf.fail()) {
        cerr << "Ошибка открытия файла для записи!" << endl;
        return;
    }
    if (ouf.good()) {
        ouf << flightNumber << endl;
        ouf << destination << endl;
        ouf << crewSize << endl;
        for (int i = 0; i < crewSize; ++i) {
            if (crew[i] != nullptr) {
                ouf << crew[i]->getTypeName() << endl;
                crew[i]->saveData(ouf);
            }
        }
        cout << "Данные успешно сохранены в файл: " << filename << endl;
    }
    if (ouf.bad()) {
        cerr << "Критическая ошибка записи в файл (bad)!" << endl;
    }
    ouf.close();
}
void Flight::readFromFile(const string& filename) {
    ifstream inf;
    inf.open(filename, ios::in);
    if (!inf.is_open()) {
        cerr << "Ошибка открытия файла для чтения!" << endl;
        return;
    }
    if (inf.peek() == EOF) {
        cout << "Файл пуст!" << endl;
        inf.close();
        return;
    }
    for (int i = 0; i < crewSize; ++i) {
        delete crew[i];
        crew[i] = nullptr;
    }
    crewSize = 0;
    inf.ignore(1000, '\n');
    getline(inf, flightNumber);
    getline(inf, destination);
    int loadedSize = 0;
    inf >> loadedSize;
    for (int i = 0; i < loadedSize; ++i) {
        if (inf.eof()) {
            cout << "Предупреждение: достигнут конец файла раньше времени!" << endl;
            break;
        }
        string typeStr;
        inf >> typeStr;
        Employee* emp = nullptr;
        if (typeStr == "Pilot") {
            emp = new Pilot();
        }
        else if (typeStr == "FlightAttendant") {
            emp = new FlightAttendant();
        }
        else if (typeStr == "Engineer") {
            emp = new Engineer();
        }
        else {
            cerr << "Неизвестный тип сотрудника в файле: " << typeStr << endl;
            continue;
        }
        if (emp != nullptr) {
            emp->loadData(inf);
            crew[crewSize++] = emp;
        }
    }
    cout << "Данные успешно загружены из файла: " << filename << endl;
    inf.close();
}
void Flight::appendToFile(const string& filename) const {
    ofstream ouf;
    ouf.open(filename, ios::app);
    if (!ouf.is_open()) {
        cerr << "Ошибка открытия файла для добавления!" << endl;
        return;
    }
    cout << "Добавление дополнительного сотрудника в файл:" << endl;
    cout << "1 - Пилот\n2 - Бортпроводник\n3 - Инженер\nВыбор: ";
    int tChoice;
    cin >> tChoice;
    Employee* emp = nullptr;
    if (tChoice == 1) emp = new Pilot();
    else if (tChoice == 2) emp = new FlightAttendant();
    else if (tChoice == 3) emp = new Engineer();
    else {
        cout << "Неверный выбор!" << endl;
        ouf.close();
        return;
    }
    cin >> *emp;
    ouf << emp->getTypeName() << endl;
    emp->saveData(ouf);
    delete emp;
    cout << "Данные успешно добавлены в файл!" << endl;
    ouf.close();
}

void Flight::viewFileRaw(const string& filename) const {
    ifstream inf;
    inf.open(filename);
    if (!inf.is_open()) {
        cerr << "Не удалось открыть файл для просмотра!" << endl;
        return;
    }
    cout << "--- СОДЕРЖИМОЕ ФАЙЛА (" << filename << ") ---" << endl;
    string line;
    while (getline(inf, line)) {
        cout << line << endl;
        streampos pos = inf.tellg();
        (void)pos;
    }
    cout << "-----------------------------------------\n" << endl;
    inf.close();
}

void Flight::searchInFile(const string& filename, const string& keyword) const {
    ifstream inf;
    inf.open(filename);
    if (!inf.is_open()) {
        cerr << "Ошибка открытия файла для поиска!" << endl;
        return;
    }
    cout << "--- РЕЗУЛЬТАТЫ ПОИСКА КЛЮЧЕВОГО СЛОВА: " << keyword << endl;
    string line;
    bool found = false;
    while (getline(inf, line)) {
        if (line.find(keyword) != string::npos) {
            cout << "Найдено совпадение в строке: " << line << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "По вашему запросу ничего не найдено." << endl;
    }
    cout << "---------------------------------------------" << endl;
    inf.close();
}

void Flight::deleteFromFile(const string& filename, int empId) {
    readFromFile(filename);
    bool deleted = false;
    for (int i = 0; i < crewSize; ++i) {
        if (crew[i]->getId() == empId) {
            delete crew[i];
            for (int j = i; j < crewSize - 1; ++j) {
                crew[j] = crew[j + 1];
            }
            crew[--crewSize] = nullptr;
            deleted = true;
            break;
        }
    }
    if (deleted) {
        ofstream ouf;
        ouf.open(filename, ios::trunc);
        if (ouf.is_open()) {
            ouf.seekp(0);
            ouf.close();
        }
        saveToFile(filename);
        cout << "Сотрудник с ID " << empId << " удален из файла." << endl;
    }
    else {
        cout << "Сотрудник с ID " << empId << " не найден в экипаже." << endl;
    }
}

void Flight::editInFile(const string& filename, int empId) {
    readFromFile(filename);
    bool edited = false;
    for (int i = 0; i < crewSize; ++i) {
        if (crew[i]->getId() == empId) {
            cout << "Найден сотрудник. Введите новые данные:" << endl;
            cin >> *crew[i];
            edited = true;
            break;
        }
    }
    if (edited) {
        saveToFile(filename);
        cout << "Данные сотрудника в файле успешно отредактированы!" << endl;
    }
    else {
        cout << "Сотрудник для редактирования не найден." << endl;
    }
}
