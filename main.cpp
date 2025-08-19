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
    main_db.inventory = restoreData("mylibrary2.lbl");

    while (true) {
        cout << endl << "---[ Bibliotecária Eletrônica ]---" << endl << endl;

        string choose = inputOption({"Livros Registrados","Registrar", "Alterar Registro", "Apagar Registro", "Sair"});
        if (choose == "Livros Registrados") {
            main_db.showBooks();
        }

        else if (choose == "Registrar") {
            cout << "=== Criar Novo Livro ===";
            main_db.createBook(
                inputStr("Título do Livro: "),
                inputStr("Author do Livro: "),
                inputInt("Ano de lançamento: "),
                (BookGenre)inputRange({"Romance", 'Mystery', "Ficction", "Historical", "Poem", "Science", "None"})
            );


        } else if (choose == "Sair") {
            saveBooks(main_db.inventory, "mylibrary2.lbl");
            break;
        }

        else if (choose == "Alterar Registro") {
            if (main_db.isEmpty()) {continue;}

            main_db.editBook(main_db.selectBook());
        }

        else if (choose == "Apagar Registro") {
            if (main_db.isEmpty()) {continue;}

            main_db.deleteBook(main_db.selectBook());
        }
    }
    return 0;
}
