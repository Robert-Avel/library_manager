#include <string>
#include <vector>
#include <ctime>
#include "util.hpp"
using namespace std;


class VirtualClient {
    protected:


    public:
    string name;
    char gender;
    time_t birth_date;
    int id;

    VirtualClient(string name_, char gender_, time_t birth_date_, int id_ = time(NULL)) {
        name = name_;
        birth_date = birth_date_;
        gender = gender_;
        id = time(NULL);
    }


    VirtualClient(string name_, char gender_, int birth_day, int birth_month, int birth_year, int id_ = time(NULL)) {
        struct tm datetime = {};

        datetime.tm_year = birth_year - 1900;
        datetime.tm_mon = birth_month -1;
        datetime.tm_mday = birth_day;

        name = name_;
        birth_date = mktime(&datetime);
        gender = gender_;
        id = time(NULL);
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
        if (clients.empty()) {cout << "Não há clientes registrados";}

        int max_name_size = 0;
        int max_id_size = 0;
        for (VirtualClient c: clients) {

            if(to_string(c.id).size() > max_id_size) {max_id_size = to_string(c.id).size();}
            if(c.name.size() > max_name_size) {max_name_size = c.name.size();}
        }
        for (VirtualClient c: clients) {
            cout << " | " << c.id;
            for(int i = 0; i < max_id_size - to_string(c.id).size(); i++) {cout << " ";}

            cout << " | " << c.name;
            for(int i = 0; i < max_name_size - c.name.size(); i++) {cout << " ";}
            
            cout << " | " << c.gender << " | " << c.getBirthDate() << endl;
        }
    }

    int searchID() {
        while (true) 
        {
            int search_id = inputInt("Buscar um Livro por ID: ");
            for (int i = 0; i < clients.size(); i++) {
                if (clients[i].id == search_id) {
                    selected_clients = &clients[i];
                    return i;
                }
            }
            cout << "Cliente não encontrado ou o Valor se encontra fora do Alcance" << "\n";
        }
    }
    void deleteClient(int index) {
        if (clients.empty()) {return;}
        clients.erase(clients.begin() + index);
    }
};