#include "client.hpp"


struct HiredBook {
    int book_id;
    int client_id;
    time_t hire_date;
    time_t expiration_date;

    bool was_returned = false;
    time_t return_day;


    HiredBook(int book_id_, int client_id_, int hire_period_days) {
        book_id = book_id_;
        client_id = client_id_;
        hire_date = time(NULL);
        
        struct tm datetime;
        datetime = *localtime(&hire_date);
        datetime.tm_mday += hire_period_days;
        expiration_date = mktime(&datetime);
        
    }


    string getHireDate() {
        char output[50];
        struct tm datetime;
        datetime = *localtime(&hire_date);
        strftime(output, 50, "%d %B %Y %H : %M : %S", &datetime);
        return string(output);
    }


    string getExpirationDate() {
        char output[50];
        struct tm datetime;
        datetime = *localtime(&expiration_date);
        strftime(output, 50, "%d %B %Y %H : %M : %S", &datetime);
        return string(output);
    }


    string getStatus() {
        if(!was_returned) {
            if(hire_date > expiration_date) {
                return "Pendente";
            } else {
                return "Atrasado";
            }
        } else {
            if(return_day > expiration_date) {
                return "Entregue com Atraso";
            } else {
                return "Entregue no Prazo";
            }
        }
        return "N/A";
    }
};



class BookNClient: public ClientManager, public Library {
    public:
    
    vector<HiredBook> hired_books;

    HiredBook* selected_hire;

    void hireBook(int book_id, int client_id, int hire_period_days) {
        hired_books.push_back(HiredBook(book_id, client_id, hire_period_days));
    }


    void printHire(int index) {
        selectBookID(hired_books[index].book_id);
        selectClientID(hired_books[index].client_id);
        

        cout << "\n\n";
        if(!selected_book) {
            cout << "Livro não encontrado! id<" << hired_books[index].book_id << ">\n";
        } else {
            cout << "Livro: " << selected_book->title 
                << "\nAuthor: " << selected_book->author 
                << "\nID do Livro: " << selected_book->ID << "\n\n";
        }

        if(!selected_clients) {
            cout << "Cliente não encontrado! id<" << hired_books[index].client_id << ">\n";
        } else {
            cout << "Solicitado por: " << selected_clients->name 
                 << "\nSexo: " << ((selected_clients->gender == 'F') ? "Feminino" : "Masculino") 
                 << "\nID do Cliente: " << selected_clients->id << "\n\n";
        }

        cout<< "ID do Serviço: " << hired_books[index].hire_date
            << "\nData do Serviço: " << hired_books[index].getHireDate()
            << "\nData de Expiração: " << hired_books[index].getExpirationDate()
            << "\nStatus: "<< hired_books[index].getStatus() << "\n\n";
    }


    void selectHire(long ID) {
        for (HiredBook &h: hired_books) {
            if(h.hire_date == ID) {
                selected_hire = &h;
            }
        }
        cout << "Aluguel não encontrado ou o Valor se encontra fora do Alcance" << "\n";
    }

    int searchHireId() {
        while (1)
        {
            long search_id = inputInt("Buscar por ID");
            for (int i = 0; i < hired_books.size(); i++) {
                if(search_id == hired_books[i].hire_date) {
                    selected_hire = &hired_books[i];
                    return i;
                }
            }
            cout << "Aluguel não encontrado ou o Valor se encontra fora do Alcance" << "\n";
        }
    }
};