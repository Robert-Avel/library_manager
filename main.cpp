#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "src/serielization.hpp"
using namespace std;


static Library main_db;
static ClientManager client_db;


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
}


void client_area_loop() {
    while (1)
    {
        string choose = inputOption({"Cadastrar Cliente", "Mostrar Clientes","Remover Cliente", "Editar Cliente", "Sair"});


        if(choose == "Sair") {
            Client::saveData(client_db.clients, "client.lbl");
            break;
        } 
        
        
        else if (choose == "Cadastrar Cliente") {
            client_db.createClient(
                inputStr("Nome do Cliente: "),
                inputGender(),
                inputRange("Dia do Nascimento: ", 31, 1),
                inputRange("Mês do Nascimento: ", 12, 1),
                inputInt("Ano de nascimento: ")
            );
        }
        
        else if(choose == "Mostrar Clientes") {
            client_db.showClients();
        }

        else if (choose == "Remover Cliente") {
            if (client_db.clients.empty()) {break;}
            client_db.deleteClient(client_db.searchID());
        }

        else if (choose == "Editar Cliente") {
            client_db.searchID();
            string opc = inputOption({"Nome", "Gênero", "Data de Nascimento"});
            if (opc == "Nome") {client_db.selected_clients->name = inputStr("Novo Nome:");}
            if (opc == "Gênero") {client_db.selected_clients->gender = inputGender();}
            if (opc == "Data de Nascimento") {tm datetime = client_db.inputBirthDate(); client_db.selected_clients->birth_date = mktime(&datetime);}
        }
    }
}




int main() {
    main_db.inventory = Book::restoreData("mylibrary2.lbl");
    client_db.clients = Client::restoreData("client.lbl");

    while (true) { // PRINCIPAL
        cout << endl << "---[ Bibliotecária Eletrônica ]---" << endl << endl;

        string area_choose = inputOption({"Àrea de Livros", "Área de Clientes", "Aluguel de Livros", "Fechar"});


        if (area_choose == "Fechar") {
            break;
        } else if(area_choose == "Àrea de Livros") {
            library_area_loop();
        } else if (area_choose == "Área de Clientes") {
            client_area_loop();
        } else if (area_choose == "Aluguel de Livros [EM BREVE]") {
            cout << "EM CONSTRUÇÃO" << endl;
        }
    }
    return 0;
}
