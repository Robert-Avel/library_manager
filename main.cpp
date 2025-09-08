#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "src/serielization.hpp"
using namespace std;


static BookNClient main_db;
//static ClientManager client_db;


void library_area_loop() {

    while (1) {
        string choose = inputOption({"Livros Registrados","Registrar", "Alterar Registro", "Apagar Registro", "Adicionar Livro", 
            "Remover Livro", "Sair"});
        

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
            Book::saveData(main_db.inventory, "mylibrary2.lbl");
            break;
        }

        else if (choose == "Alterar Registro") {
            if (main_db.isEmpty()) {break;}
            main_db.searchBookID();
            main_db.editBook();
        }

        else if (choose == "Apagar Registro") {
            if (main_db.isEmpty()) {break;}
            main_db.deleteBook(main_db.searchBookID());
        }

        else if(choose == "Adicionar Livro") {
            if (main_db.isEmpty()) {break;}
            main_db.searchBookID();
            main_db.addBook();
        }

        else if (choose == "Remover Livro") {
            if (main_db.isEmpty()) {break;}
            main_db.searchBookID();
            main_db.removeBook();
        }
    }
}


void client_area_loop() {
    while (1)
    {
        string choose = inputOption({"Cadastrar Cliente", "Mostrar Clientes","Remover Cliente", "Editar Cliente", "Sair"});


        if(choose == "Sair") {
            Client::saveData(main_db.clients, "client.lbl");
            break;
        } 
        
        
        else if (choose == "Cadastrar Cliente") {
            main_db.createClient(
                inputStr("Nome do Cliente: "),
                inputGender(),
                inputRange("Dia do Nascimento: ", 31, 1),
                inputRange("Mês do Nascimento: ", 12, 1),
                inputInt("Ano de nascimento: ")
            );
        }
        
        else if(choose == "Mostrar Clientes") {
            main_db.showClients();
        }

        else if (choose == "Remover Cliente") {
            if (main_db.clients.empty()) {break;}
            main_db.deleteClient(main_db.searchClientID());
        }

        else if (choose == "Editar Cliente") {
            main_db.searchClientID();
            string opc = inputOption({"Nome", "Gênero", "Data de Nascimento"});
            if (opc == "Nome") {main_db.selected_clients->name = inputStr("Novo Nome:");}
            if (opc == "Gênero") {main_db.selected_clients->gender = inputGender();}
            if (opc == "Data de Nascimento") {tm datetime = main_db.inputBirthDate(); main_db.selected_clients->birth_date = mktime(&datetime);}
        }
    }
}


void hire_book_service() {
    while (1) {
        string choose = inputOption({"Alugar Livro", "Informações", "Ver Registros", "Sair"});
        
        if (choose == "Alugar Livro") {
            main_db.searchBookID();
            main_db.searchClientID();

            main_db.hireBook(main_db.selected_book->ID, main_db.selected_clients->id, inputInt("Dias de Aluguel: "));
        }

        else if (choose == "Informações") {
            if(main_db.hired_books.empty()) {
                cout << "Nenhum Aluguel Registrado";
                continue;

            }
            main_db.printHire(main_db.searchHireId());
        }

        else if (choose == "Ver Registros") {
            if(main_db.hired_books.empty()) {
                cout << "Nenhum Aluguel Registrado";
                continue;
            }
            for(HiredBook h: main_db.hired_books) {
                cout << h.hire_date << " | " << h.getHireDate()<< " | " << h.getExpirationDate() << " | B" << h.book_id << " | C" << h.client_id;
            }
        }

        else if (choose == "Sair") {
            break;
        }
    }  
}


int main() {
    main_db.inventory = Book::restoreData("mylibrary2.lbl");
    main_db.clients = Client::restoreData("client.lbl");

    while (true) { // PRINCIPAL
        cout << endl << "---[ Bibliotecária Eletrônica ]---" << endl << endl;

        string area_choose = inputOption({"Àrea de Livros", "Área de Clientes", "Aluguel de Livros", "Fechar"});

        if (area_choose == "Fechar") {
            break;
        } else if(area_choose == "Àrea de Livros") {
            library_area_loop();
        } else if (area_choose == "Área de Clientes") {
            client_area_loop();
        } else if (area_choose == "Aluguel de Livros") {
            hire_book_service();
        }
    }
    return 0;
}
