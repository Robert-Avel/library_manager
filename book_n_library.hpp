#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "util.cpp"
using namespace std;



struct Book {
    string title;
    string author;
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

    void createBook(string titleI, string authorI, int ageI) {
        Book new_book = {titleI, authorI, ageI};
        inventory.push_back(new_book);
    }
    
    void showBooks() {
        for (Book b: inventory) {
            cout << b.title << " " << b.author << " " << b.created_in << endl;
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

