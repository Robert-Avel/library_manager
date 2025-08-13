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

    void createBook(string titleI, string authorI,int ageI, BookGenre genre_id = None) {
        string genreI = "N/A";

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
            } else if (edit_opc == "Editar Gênero") {
                //Fazer depois
            }
    };
    void deleteBook(int index) {
        inventory.erase(inventory.begin() + index);
    }
};



struct Librarian
{
    Book createBook(string title, string author, int created_in, BookGenre Genre) {
        Book new_book = {title, author, genreToString(Genre),created_in};
        return new_book;
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
    BookGenre genreToString(string &genre) {
        if (genre == "Romance") {return Romance;}
        else if (genre == "Mystery") {return Mystery;}
        else if (genre == "Ficction") {return Ficction;}
        else if (genre == "Historical") {return Historical;}
        else if (genre == "Poem") {return Poem;}
        else if (genre == "Science") {return Science;}
        else {return None;}
    }
};
