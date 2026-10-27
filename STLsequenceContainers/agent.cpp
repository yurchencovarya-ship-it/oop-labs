#include "agent.h"
using namespace std;
Agent::Agent() : Person(), agentId(0), experienceYears(0) {}
Agent::Agent(const string& name, const string& ph, int id, int experience)
    : Person(name, ph), agentId(id), experienceYears(experience) {
}
void Agent::display() const {
    Person::display();
    cout << ", ID агента: " << agentId
        << ", Стаж работы: " << experienceYears << " лет";
}
int Agent::getId() const {
    return agentId;
}
int Agent::getExperienceYears() const {
    return experienceYears;
}
void Agent::setId(int id) {
    agentId = id;
}
void Agent::setExperienceYears(int experience) {
    experienceYears = experience;
}
ostream& operator<<(ostream& os, const Agent& ag) {
    os << "ID: " << ag.getId()
        << ", ФИО: " << ag.getName()
        << ", Телефон: " << ag.getPhone()
        << ", Стаж: " << ag.getExperienceYears() << " лет";
    return os;
}