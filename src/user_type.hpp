#include <string>
#include <iostream>
#include <ctime>
using namespace std;

class Client {
    protected:
    string name;
    time_t birth_date;
    char gender;

    public:
    Client(string name_, char gender_, int birth_day, int birth_month, int birth_year) {
        struct tm datetime = {};

        datetime.tm_year = birth_year - 1900;
        datetime.tm_mon = birth_month -1;
        datetime.tm_mday = birth_day;

        name = name_;
        birth_date = mktime(&datetime);
        gender = gender_;
    }

    string showBirthDate() {
        struct tm bd = *localtime(&birth_date);
        char output[50];

        strftime(output, 50, "%d %B %Y", &bd);
        return string(output);
    }

    void showInfo() {
        cout << "Nome: " << name << endl
             << "Data de Nascimento: " << showBirthDate() << endl
             << "Gênero: " << gender << endl;
    }
};