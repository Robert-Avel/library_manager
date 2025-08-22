#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "src/serielization.hpp"
using namespace std;


int main() {
    Library main_db;
    main_db.inventory = Book::restoreData("mylibrary2.lbl");

    while (true) {
        cout << endl << "---[ Bibliotecária Eletrônica ]---" << endl << endl;

        string choose = inputOption({"Livros Registrados","Registrar", "Alterar Registro", "Apagar Registro", "Adicionar Livro", "Remover Livro","Sair"});
        if (choose == "Livros Registrados") {
            main_db.showBooks();
        }

        else if (choose == "Registrar") {
            cout << "=== Criar Novo Livro ===";
            main_db.createBook(
                inputStr("Título do Livro: "),
                inputStr("Author do Livro: "),
                inputInt("Ano de lançamento: "),
                (BookGenre)inputRange({"Romance", "Mystery", "Ficction", "Historical", "Poem", "Science", "None"})
            );


        } else if (choose == "Sair") {
            Book::saveBooks(main_db.inventory, "mylibrary2.lbl");
            break;
        }

        else if (choose == "Alterar Registro") {
            if (main_db.isEmpty()) {break;}
            main_db.searchID();
            main_db.editBook();
        }

        else if (choose == "Apagar Registro") {
            if (main_db.isEmpty()) {break;}
            main_db.deleteBook(main_db.searchID());
        }

        else if(choose == "Adicionar Livro") {
            if (main_db.isEmpty()) {break;}
            main_db.searchID();
            main_db.addBook();
        }

        else if (choose == "Remover Livro") {
            if (main_db.isEmpty()) {break;}
            main_db.searchID();
            main_db.removeBook();
        }
    }
    return 0;
}
