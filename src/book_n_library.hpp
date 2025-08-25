#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include "util.hpp"
using namespace std;


enum BookGenre {
    Romance,
    Mystery,
    Ficction,
    Historical,
    Poem,
    Science,
    None
};


struct HiredBook {
    int book_id;
    //Client tenant;
    time_t date;
    time_t expire_date;

    void getDates() {
        struct tm dt;
        dt = *localtime(&date);
        cout << "Data do aluguel: " << dt.tm_mday << " " << dt.tm_mon << " " << dt.tm_year << " " << dt.tm_hour << ":" << dt.tm_min << endl;
        dt = *localtime(&expire_date);
        cout << "Data de Expiração: " << dt.tm_mday << " " << dt.tm_mon << " " << dt.tm_year << " " << dt.tm_hour << ":" << dt.tm_min << endl;
    }
};


struct VirtualBook {
    VirtualBook(string titleI, string authorI,int ageI, BookGenre genre_id = None, int quantityI = 0, int ID_ = time(NULL)) {
        title = titleI;
        author = authorI;
        created_in = ageI;
        _base_genre = genre_id;
        quantity = quantityI;
        ID = ID_;
    }
    string genreToString(BookGenre genre) {
        switch(genre)
        {
        case Romance:
            return "Romance";
        case Mystery:
            return "Mystery";
        case Ficction:
            return "Ficction";
        case Historical:
            return "Historical";
        case Poem:
            return "Poem";
        case Science:
            return "Science";
        default:
            return "N/A";
        }
    }

    string getGenre() {
        return genreToString(_base_genre);
    }

    //Dados Base
    BookGenre _base_genre;

    //Dados Publicos
    string title;
    string author;
    int created_in;
    int ID;
    int quantity = 0;
};


// Library class to manage a collection of books

struct Library {
    protected:

    int total_books = 0;

    int max_title_size = 0;
    int max_author_size = 0;
    int max_genre_size = 0;
    int book_age_size = 5;

    VirtualBook* selected_book;

    void updateStatus() {
        total_books = 0;
        for (VirtualBook& b: inventory) {
            if (b.title.size() > max_title_size) {max_title_size = b.title.size();}
            if (b.author.size() > max_author_size) {max_author_size = b.author.size();}
            if (b.getGenre().size() > max_genre_size) {max_genre_size = b.getGenre().size();}
            if (to_string(b.created_in).size() > book_age_size) {book_age_size = to_string(b.created_in).size();}
            total_books += b.quantity;
        }
    }

    public:

    vector<HiredBook> hired_service = {};
    vector<VirtualBook> inventory = {};


    bool isEmpty() {
        if (inventory.empty()) {
            return true;
            cout << "Biblioteca Vazia";
        } else {return false;}
    }

    void createBook(string titleI, string authorI,int ageI, BookGenre genre_id) {
        inventory.push_back(VirtualBook(titleI, authorI, ageI, genre_id));
        updateStatus();
    }
    
    void showBooks() {
        if (isEmpty()) {
            cout << "--- O Registro está vazio ---\n";
        }

        updateStatus();
        for (int i = 0; i < inventory.size(); i++) { 

            cout << i;
            for (int c = 0; c < 3 - to_string(i).size(); c++) {cout << " ";}

            cout << " | " << inventory[i].title;
            for (int c = 0; c < max_title_size - inventory[i].title.size(); c++) {cout << " ";}
            
            cout << " | " << inventory[i].author;
            for (int c = 0; c < max_author_size - inventory[i].author.size(); c++) {cout << " ";}
            
            cout << " | " << inventory[i].getGenre();
            for (int c = 0; c < max_genre_size - inventory[i].getGenre().size(); c++) {cout << " ";}
            
            cout << " | " << inventory[i].created_in;
            for (int c = 0; c < book_age_size - to_string(inventory[i].created_in).size(); c++) {cout << " ";}

            cout << " | " << inventory[i].quantity;
            for (int c = 0; c < 3 - to_string(inventory[i].quantity).size(); c++) {cout << " ";}

            cout << " | " << inventory[i].ID;
            cout << " |" << endl;
        }
    }
    void printBook(VirtualBook &selected_book) {
        cout << "Título: " << selected_book.title << "\nAuthor: " << selected_book.author << "\nAno de lançamento: " << selected_book.created_in << endl;
    }
    int searchID() {
        while (true) 
        {
            int search_id = inputInt("Buscar um Livro por ID: ");
            for (int i = 0; i < inventory.size(); i++) {
                if (inventory[i].ID == search_id) {
                    selected_book = &inventory[i];
                    return i;
                }
            }
            cout << "Livro não encontrado ou o Valor se encontra fora do Alcance" << "\n";
        }
    }

    void editBook() {
        if (isEmpty()) {return;}
        string edit_opc = inputOption({"Editar Título", "Editar Autor", "Editar Ano de lançamento", "Editar Gênero"});

            if (edit_opc == "Editar Título") {
                selected_book->title = inputStr("Novo Título do Livro: ");
        
            } else if (edit_opc == "Editar Autor") {
                selected_book->author = inputStr("Novo Author do Livro: ");
        
            } else if (edit_opc == "Editar Ano de lançamento") {
                selected_book->created_in = inputInt("Novo Ano de Lançamento: ");
        
            } else if (edit_opc == "Editar Gênero") {
                selected_book->_base_genre = (BookGenre) inputRange({"Romance", "Mystery", "Ficction", "Historical", "Poem", "Science", "None"});
            }
        updateStatus();
    };
    void deleteBook(int index) {
        if (isEmpty()) {return;}
        inventory.erase(inventory.begin() + index);
        updateStatus();
    }

    void addBook(int value = 1) {
        if (isEmpty()) {return;}
        selected_book->quantity += value;
        cout << "Adicionado " << value << " unidade(s) do livro " << selected_book->title << "\n";
        cout << "Undidades Atual: " << selected_book->quantity << "\n";
    }
    void removeBook(int value = 1) {
        if (isEmpty()) {return;}
        if (selected_book->quantity - value >= 0) {
            selected_book->quantity -= value;
            cout << "Removido " << value << " unidade(s) do livro " << selected_book->title << "\n";
            cout << "Undidades Atual: " << selected_book->quantity << "\n";
        } else {cout << "O Valor é maior que a quantidade disponível\n";}
    }

};


class Client {
    protected:
    
    time_t birth_date;

    public:
    string name;
    char gender;
    int id;


    Client(string name_, char gender_, int birth_day, int birth_month, int birth_year) {
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
    vector<Client> clients = {};
    Client* selected_clients;

    void createClient(string name_, char gender_, int birth_day, int birth_month, int birth_year) {
        clients.push_back(Client(name_, gender_, birth_day, birth_month, birth_year));
    }


    void showClients() {
        if (clients.empty()) {cout << "Não há clientes registrados";}

        int max_name_size = 0;
        int max_id_size = 0;
        for (Client c: clients) {

            if(to_string(c.id).size() > max_id_size) {max_id_size = to_string(c.id).size();}
            if(c.name.size() > max_name_size) {max_name_size = c.name.size();}
        }
        for (Client c: clients) {
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