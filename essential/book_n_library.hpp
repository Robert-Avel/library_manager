#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
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


struct VirtualBook {
    VirtualBook(string titleI, string authorI,int ageI, BookGenre genre_id = None, int quantityI = 0) {
        title = titleI;
        author = authorI;
        created_in = ageI;
        _base_genre = genre_id;
        //genre = genreToString(genre_id);
        quantity = quantityI;

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
    //string genre;
    int created_in;
    int quantity = 0;
};


// Library class to manage a collection of books

struct Library {
    protected:

    int max_title_size = 0;
    int max_author_size = 0;
    int max_genre_size = 0;
    int book_age_size = 5;

    void updateStatus() {
    for (VirtualBook& b: inventory) {
        if (b.title.size() > max_title_size) {max_title_size = b.title.size();}
        if (b.author.size() > max_author_size) {max_author_size = b.author.size();}
        if (b.getGenre().size() > max_genre_size) {max_genre_size = b.getGenre().size();}
        if (to_string(b.created_in).size() > book_age_size) {book_age_size = to_string(b.created_in).size();}
        }
    }
    public:

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

            cout << " |" << endl;
        }
    }
    void printBook(VirtualBook &selected_book) {
        cout << "Título: " << selected_book.title << "\nAuthor: " << selected_book.author << "\nAno de lançamento: " << selected_book.created_in << endl;
    }
    int searchID() {
        while (true) 
        {
            int search_seq = inputInt("Buscar um Livro por ID: ");
            if (0 <= search_seq | search_seq < inventory.size()) {
                return search_seq;
            }
            cout << "Livro não encontrado ou o Valor se encontra fora do Alcance" << "\n";
        }
    }
    void editBook(int index) {
        string edit_opc = inputOption({"Editar Título", "Editar Autor", "Editar Ano de lançamento", "Editar Gênero"});

            if (edit_opc == "Editar Título") {
                inventory[index].title = inputStr("Novo Título do Livro: ");
        
            } else if (edit_opc == "Editar Autor") {
                inventory[index].author = inputStr("Novo Author do Livro: ");
        
            } else if (edit_opc == "Editar Ano de lançamento") {
                inventory[index].created_in = inputInt("Novo Ano de Lançamento: ");
        
            } else if (edit_opc == "Editar Gênero") {
                inventory[index]._base_genre = (BookGenre) inputRange({"Romance", "Mystery", "Ficction", "Historical", "Poem", "Science", "None"});
            }
        updateStatus();
    };
    void deleteBook(int index) {
        inventory.erase(inventory.begin() + index);
        updateStatus();
    }

    void addBook(int index, int value = 1) {
        inventory[index].quantity += value;
        cout << "Adicionado " << value << " unidade(s) do livro " << inventory[index].title << "\n";
        cout << "Undidades Atual: " << inventory[index].quantity << "\n";
    }
    void removeBook(int index, int value = 1) {
        if (inventory[index].quantity - value >= 0) {
            inventory[index].quantity -= value;
            cout << "Removido " << value << " unidade(s) do livro " << inventory[index].title << "\n";
            cout << "Undidades Atual: " << inventory[index].quantity << "\n";
        } else {cout << "O Valor é maior que a quantidade disponível\n";}
    }
};


