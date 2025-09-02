#include <string>
#include <vector>
#include <ctime>
#include "util.hpp"
using namespace std;


class VirtualClient {
    public:
    string name;
    char gender;
    time_t birth_date;
    int id;

    VirtualClient(string name_, char gender_, time_t birth_date_, int id_ = time(NULL)) {
        name = name_;
        birth_date = birth_date_;
        gender = gender_;
        id = id_;
    }


    VirtualClient(string name_, char gender_, int birth_day, int birth_month, int birth_year, int id_ = time(NULL)) {
        struct tm datetime = {};

        datetime.tm_year = birth_year - 1900;
        datetime.tm_mon = birth_month -1;
        datetime.tm_mday = birth_day;

        name = name_;
        birth_date = mktime(&datetime);
        gender = gender_;
        id = id_;
    }

    string getBirthDate() {
        struct tm bd = *localtime(&birth_date);
        char output[50];

        strftime(output, 50, "%d %B %Y", &bd);
        return string(output);
    }


    void showInfo() {
        cout << "Nome: " << name << endl
             << "Data de Nascimento: " << getBirthDate() << endl
             << "Gênero: " << gender << endl;
    }
};


class ClientManager {
    public:
    vector<VirtualClient> clients = {};
    VirtualClient* selected_clients;

    void createClient(string name_, char gender_, int birth_day, int birth_month, int birth_year) {
        clients.push_back(VirtualClient(name_, gender_, birth_day, birth_month, birth_year));
    }


    void showClients() {
        if (clients.empty()) {cout << "Não há clientes registrados"; return;}

        int max_name_size = 4;
        int max_id_size = 2;
        int max_birthdate_size = 10;
        for (VirtualClient c: clients) {
            if(to_string(c.id).size() > max_id_size) {max_id_size = to_string(c.id).size();}
            if(c.name.size() > max_name_size) {max_name_size = c.name.size();}
            if(c.getBirthDate().size() > max_birthdate_size) {max_birthdate_size = c.getBirthDate().size();}
        }
        
        int border_size = (2 + max_id_size + 3 + max_name_size + 3 + 6 + 3 + max_birthdate_size + 2);

        for (int d = 0; d < border_size; d++) {cout << "-";}

        cout << endl << "| ID";
        for(int i = 0; i < max_id_size - 2; i++) {cout << " ";}

        cout << " | " << "Nome";
        for(int i = 0; i < max_name_size - 4; i++) {cout << " ";}

        cout << " | " << "Genero";
        //for(int i = 0; i < 6; i++) {cout << " ";}

        cout << " | " << "Nascimento";
        for(int i = 0; i < max_birthdate_size - 10; i++) {cout << " ";}
        cout << " |" << endl;


        for (int d = 0; d < border_size; d++) {cout << "-";}
        cout << endl;
        for (VirtualClient c: clients) {
            cout  << "| " << c.id;
            for(int i = 0; i < max_id_size - to_string(c.id).size(); i++) {cout << " ";}

            cout << " | " << c.name;
            for(int i = 0; i < max_name_size - c.name.size(); i++) {cout << " ";}
            
            cout << " | " << c.gender << "      | " << c.getBirthDate();
            for(int i = 0; i < max_birthdate_size - c.getBirthDate().size(); i++) {cout << " ";}

            cout << " |" << endl;
        }
        for (int d = 0; d < border_size; d++) {cout << "-";}
        cout << endl;
    }

    int searchID() {
        while (true) 
        {
            int search_id = inputInt("Buscar um cliente por ID: ");
            for (int i = 0; i < clients.size(); i++) {
                if (clients[i].id == search_id) {
                    selected_clients = &clients[i];
                    return i;
                }
            }
            cout << "Cliente não encontrado ou o Valor se encontra fora do Alcance" << "\n";
        }
    }

    void editClient() {
        searchID();
        string opc = inputOption({"Nome", "Gênero", "Data de Nascimento"});
        if (opc == "Nome") {selected_clients->name = inputStr("Novo Nome:");}
        if (opc == "Gênero") {selected_clients->gender = inputGender();}
        if (opc == "Data de Nascimento") {tm datetime = inputBirthDate(); selected_clients->birth_date = mktime(&datetime);}
    }

    void deleteClient(int index) {
        if (clients.empty()) {return;}
        clients.erase(clients.begin() + index);
    }
    

    tm inputBirthDate() {
        struct tm datetime = {};

        while (1) {
            datetime.tm_year = inputInt("Ano de Nascimento do Cliente: ") - 1900;
            datetime.tm_mon = inputInt("Mês de Nascimento do Cliente: ") -1;
            datetime.tm_mday = inputInt("Dia do Nascimento do Cliente: ");
            if(validDate(datetime.tm_mday, datetime.tm_mon)) {break;}
        };
        return datetime;
    }


    bool validDate(int day, int month) {
        if (!12 > month | !month > 0) {cout << "Mês Inválido"; return false;}
        if (!32 > day | !day > 0) {cout << "Dia Inválido"; return false;}
        return true;
    }

};