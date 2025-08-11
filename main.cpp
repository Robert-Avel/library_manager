#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
//#include "book_n_library.hpp"
#include "essential/book_serielization.hpp"
//#include "util.cpp"
using namespace std;


int main() {
    Library main_db;
    main_db.inventory = restoreData("mylibrary.lbl");

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
                None,
                inputInt("Ano de lançamento: ")
            );

        } else if (choose == "Sair") {
            saveBooks(main_db.inventory, "mylibrary.lbl");
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
