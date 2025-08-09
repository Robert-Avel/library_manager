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

    bool saveBooks(string file_name) {
        int quantity = inventory.size(); // núnero de elementos

        ofstream fout;
        fout.open(file_name, std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
        if (fout.is_open()) {
            //Cabeçalho
            //int == número de elemento
            fout.write((char*) &quantity, sizeof(int));


            //Conteúdo
            for (int c = 0; c < quantity; c++) {
                int title_len = inventory[c].title.size();
                //Fazer dps um teste com strings maiores que 255 caracteres
                fout.write((char*) &title_len, sizeof(int));
                fout.write((char*) inventory[c].title.c_str(), title_len);

                int author_len = inventory[c].author.size();
                fout.write((char*) &author_len, sizeof(int));
                fout.write((char*) inventory[c].author.c_str(), author_len);

                fout.write((char*) &inventory[c].created_in, sizeof(int));
            }
            fout.close();
            std::cout << "Informação salva com sucesso!!\n";
            return true;

        } else {
            std::cout << "Algo deu errado ao tentar abrir o arquivo\n";
            return false;
        }  
    }
    void restoreData(string file_name) {
        ifstream fin;
        fin.open(file_name, std::ios_base::in | std::ios_base::binary );
        if (fin.is_open()) {
            int quantity;
            fin.read((char*) &quantity, sizeof(int));

            for (int c = 0; c < quantity; c++) {
                int title_len;
                fin.read((char*) &title_len, sizeof(int));
                string title(title_len, '\0');
                fin.read((char*) &title[0], title_len);

                int author_len;
                fin.read((char*) &author_len, sizeof(int));
                string author(author_len, '\0');
                fin.read((char*) &author[0], author_len);

                int created;
                fin.read((char*) &created, sizeof(int));

                Book loaded_book = {title, author, created};
                inventory.push_back(loaded_book);
                
                cout << "Título: " << loaded_book.title << "\nAuthor: " << loaded_book.author << "\nAno de lançamento: " << loaded_book.created_in << endl;
            }
        }
    }
};


int main() {
    Library main_db;
    main_db.restoreData("mylibrary.lbl");

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
            main_db.saveBooks("mylibrary.lbl");
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
