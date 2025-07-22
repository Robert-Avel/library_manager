#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "util.cpp"
using namespace std;


struct Book {
    string title;
    string author;
    int created_in;
    void initBook(string titleI, string authorI, int ageI) {
        title = titleI;
        author = authorI;
        created_in = ageI;
    }
    void printBook() {
        cout << "Título: " << title << "\nAuthor: " << author << "\nAno de lançamento: " << created_in << endl;
    }
    void editName(string new_value) {
        title = new_value;
    }
    void editAuthor(string new_value) {
        author = new_value;
    }
    void editAge(int new_value) {
        created_in = new_value;
    }
};


struct Library {
    vector<Book> inventory = {};
    bool isEmpty() {
        if (inventory.empty()) {
            return true;
            cout << "Biblioteca Vazia";
        } else {return false;}
    }
    void createBook(string titleI, string authorI, int ageI) {
        Book new_book;
        new_book.initBook(titleI, authorI, ageI);
        inventory.push_back(new_book);
    }
    void showBooks() {
        for (Book b: inventory) {
            cout << b.title << " " << b.author << " " << b.created_in << endl;
        }
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
                inventory[index].editName(inputStr("Novo Título do Livro: "));
            } else if (edit_opc == "Editar Autor") {
                inventory[index].editAuthor(inputStr("Novo Author do Livro: "));
            } else if (edit_opc == "Editar Ano de lançamento") {
                inventory[index].editAge(inputInt("Novo Ano de Lançamento: "));
            }
    };
    void deleteBook(int index) {
        inventory.erase(inventory.begin() + index);
    }
};


int main() {
    Library main_db;


    while (true) {
        cout << "---[ Bibliotecária Eletrônica ]---" << endl << endl;

        string choose = inputOption({"Livros Registrados","Registrar", "Alterar Registro", "Apagar Registro", "Sair"});
        if (choose == "Livros Registrados") {
            if (main_db.isEmpty()) {continue;}
            main_db.showBooks();
        }

        else if (choose == "Registrar") {
            main_db.createBook(
                inputStr("Título do Livro: "),
                inputStr("Author do Livro: "),
                inputInt("Ano de lançamento: ")
            );

        } else if (choose == "Sair") {
            break;
        }

        else if (choose == "Alterar Registro") {
            if (main_db.isEmpty()) {continue;}

            int book_address = main_db.searchBook();
            main_db.editBook(book_address);
        }

        else if (choose == "Apagar Registro") {
            if (main_db.isEmpty()) {continue;}

            int book_address = main_db.searchBook();
            main_db.deleteBook(book_address);
        }
    }
    return 0;
}
