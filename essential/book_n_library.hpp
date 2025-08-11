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


struct Book {
    string title;
    string author;
    string genre;
    int created_in;
};


// Library class to manage a collection of books

struct Library {
    vector<Book> inventory = {};

    bool isEmpty() {
        if (inventory.empty()) {
            return true;
            cout << "Biblioteca Vazia";
        } else {return false;}
    }

    void createBook(string titleI, string authorI,BookGenre genre_id, int ageI) {
        string genreI = "N/A";
        switch(genre_id)
        {
        case Romance:
            genreI = "Romance";
            break;
        case Mystery:
            genreI = "Mystery";
            break;
        case Ficction:
            genreI = "Ficction";
            break;
        case Historical:
            genreI = "Historical";
            break;
        case Poem:
            genreI = "Poem";
            break;
        case Science:
            genreI = "Science";
            break;
        default:
            break;
        }
        inventory.push_back(Book{titleI, authorI, genreI, ageI});
    }
    
    void showBooks() {
        int max_title_size = 0;
        int max_author_size = 0;
        int max_genre_size = 0;
        const int book_age_size = 5;

        for (Book& b: inventory) {
            if (b.title.size() > max_title_size) {max_title_size = b.title.size();}
            if (b.author.size() > max_author_size) {max_author_size = b.author.size();}
            if (b.genre.size() > max_genre_size) {max_genre_size = b.genre.size();}
        }
        for (Book& b: inventory) {
            cout << b.title;
            for (int c = 0; c < max_title_size-b.title.size(); c++) {cout << " ";}
            
            cout << " | " << b.author;
            for (int c = 0; c < max_author_size-b.author.size(); c++) {cout << " ";}
            
            cout << " | " << b.genre;
            for (int c = 0; c < max_genre_size-b.genre.size(); c++) {cout << " ";}
            
            cout << " | " << b.created_in;
            for (int c = 0; c < book_age_size - to_string(b.created_in).size(); c++) {cout << " ";}
            cout << " | " << endl;
        }
    }
    void printBook(Book selected_book) {
        cout << "Título: " << selected_book.title << "\nAuthor: " << selected_book.author << "\nAno de lançamento: " << selected_book.created_in << endl;
    }
    int searchBook() {
        while (true) 
        {
            string search_seq = inputStr("Buscar um Livro: ");
            for (int i = 0; i < inventory.size(); i++) {
                if (inventory[i].title.find(search_seq) != string::npos) {
                    return i;
                }
            }
            cout << "Livro não encontrado!" << "\n";
        }
    }
    void editBook(int index) {
        string edit_opc = inputOption({"Editar Título", "Editar Autor", "Editar Ano de lançamento"});
            if (edit_opc == "Editar Título") {
                inventory[index].title = inputStr("Novo Título do Livro: ");
            } else if (edit_opc == "Editar Autor") {
                inventory[index].author = inputStr("Novo Author do Livro: ");
            } else if (edit_opc == "Editar Ano de lançamento") {
                inventory[index].created_in = inputInt("Novo Ano de Lançamento: ");
            }
    };
    void deleteBook(int index) {
        inventory.erase(inventory.begin() + index);
    }
};

