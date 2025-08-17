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

struct MetaBook
{
    string title;
    string author;
    string genre;
    int created_in;
};


struct VirtualBook {
    string title;
    string author;
    string genre;
    int created_in;
    unsigned int id;
    unsigned int quantity = 0;
};


// Library class to manage a collection of books

struct Library {
    vector<VirtualBook> inventory = {};

    VirtualBook *selector;

    //STATUS
    unsigned int max_title_size = 0;
    unsigned int max_author_size = 0;
    unsigned int max_genre_size = 0;
    unsigned int book_age_size = 0;
    unsigned int last_id = 0;

    void updateStatus() {
        for (VirtualBook b: inventory) {
            if (b.id > last_id) {last_id = b.id;}
            if (b.title.size() > max_title_size) {max_title_size = b.title.size();}
            if (b.author.size() > max_author_size) {max_author_size = b.author.size();}
            if (b.genre.size() > max_genre_size) {max_genre_size = b.genre.size();}
            if (to_string(b.created_in).size() > book_age_size) {book_age_size = to_string(b.created_in).size();}
        }
    }

    bool isEmpty() {
        if (inventory.empty()) {
            return true;
            cout << "Biblioteca Vazia";
        } else {return false;}
    }

    
    void showBooks() {
        if (isEmpty()) {
            cout << "--- O Registro está vazio ---\n";
        }

        for (int i = 0; i < inventory.size(); i++) { 

            cout << i;
            for (int c = 0; c < 3 - to_string(i).size(); c++) {cout << " ";}

            cout << " | " << inventory[i].title;
            for (int c = 0; c < max_title_size - inventory[i].title.size(); c++) {cout << " ";}
            
            cout << " | " << inventory[i].author;
            for (int c = 0; c < max_author_size - inventory[i].author.size(); c++) {cout << " ";}
            
            cout << " | " << inventory[i].genre;
            for (int c = 0; c < max_genre_size - inventory[i].genre.size(); c++) {cout << " ";}
            
            cout << " | " << inventory[i].created_in;
            for (int c = 0; c < book_age_size - to_string(inventory[i].created_in).size(); c++) {cout << " ";}
            cout << " |" << endl;
        }
    }
    void printBook(VirtualBook selected_book) {
        cout << "Título: " << selected_book.title << "\nAuthor: " << selected_book.author << "\nAno de lançamento: " << selected_book.created_in << endl;
    }
    void getBook() {
        while (true) 
        {
            unsigned int search_seq = inputInt("Buscar um Livro por ID: ");
            for (VirtualBook b: inventory) {
                if (b.id == search_seq) {
                    selector = &b;
                }
            }
            cout << "Livro não encontrado!" << "\n";
        }
    }
    void editBook() {
        string edit_opc = inputOption({"Editar Título", "Editar Autor", "Editar Ano de lançamento"});
            if (edit_opc == "Editar Título") {
                selector->title = inputStr("Novo Título do Livro: ");
            } else if (edit_opc == "Editar Autor") {
                selector->author = inputStr("Novo Author do Livro: ");
            } else if (edit_opc == "Editar Ano de lançamento") {
                selector->created_in = inputInt("Novo Ano de Lançamento: ");
            } else if (edit_opc == "Editar Gênero") {
                //Fazer depois
            }
    }

    void addBook(MetaBook &new_book) {
        inventory.push_back({new_book.title, new_book.author, new_book.genre, new_book.created_in, last_id+1, 0});
        updateStatus();
    }


    void deleteBook() {
        inventory.erase(find(inventory.begin(), inventory.end(), *selector));
        updateStatus();
    }
};



struct Librarian
{
    MetaBook createBook(string title, string author, int created_in, string genre = "N/A") {
        MetaBook new_book = {title, author, genre, created_in};
        return new_book;
    }

};
