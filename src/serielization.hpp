#include "book_n_library.hpp"
#include <vector>
#include <string>
#include <fstream>
using namespace std;


namespace Book {
    void saveData(vector<VirtualBook> &inventory, string file_name) {
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
                fout.write((char*) &title_len, sizeof(int));
                fout.write((char*) inventory[c].title.c_str(), title_len);

                int author_len = inventory[c].author.size();
                fout.write((char*) &author_len, sizeof(int));
                fout.write((char*) inventory[c].author.c_str(), author_len);

                int genre = inventory[c]._base_genre;
                fout.write((char*) &genre, sizeof(int));

                fout.write((char*) &inventory[c].created_in, sizeof(int));

                fout.write((char*) &inventory[c].quantity, sizeof(unsigned int));

                fout.write((char*) &inventory[c].ID, sizeof(int));
            }
            fout.close();
            std::cout << "Informação salva com sucesso!!\n";

        } else {
            std::cout << "Algo deu errado ao tentar abrir o arquivo\n";
        }  
    }

    vector<VirtualBook> restoreData(string file_name) {

        vector<VirtualBook> loaded_inventory = {};

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

                BookGenre genre;
                fin.read((char*) &genre, sizeof(int));
                //string genre(genre_len, '\n');
                //fin.read((char*) &genre[0], genre_len);


                int created;
                fin.read((char*) &created, sizeof(int));


                unsigned int quantity;
                fin.read((char*) &quantity, sizeof(unsigned int));

                int ID_;
                fin.read((char*) &ID_, sizeof(int));

                VirtualBook loaded_book = VirtualBook(title, author, created, genre, quantity, ID_);
                loaded_inventory.push_back(loaded_book);
                
                cout << "Título: " << loaded_book.title << "\nAuthor: " << loaded_book.author << "\nAno de lançamento: " << loaded_book.created_in << endl;
            }
            return loaded_inventory;
        } else {
            cout << "Algo deu errado ao tentar abrir o arquivo\n";
        }
        return loaded_inventory;
    }
}


namespace Client {
    void saveData(vector<VirtualClient> &data, string file_name) {
        int quantity = data.size();

        ofstream fout;

        fout.open(file_name, std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
        if (!fout.is_open()) {
            cout << "Algo deu errado ao tentar abrir o arquivo!\n";
        } else {
            fout.write((char*)&quantity, sizeof(int));

            for(int i = 0; i < quantity; i++) {
                int name_size = data[i].name.size();
                fout.write((char*) &name_size, sizeof(int));
                fout.write((char*) data[i].name.c_str(), name_size);

                fout.write((char*) &data[i].gender, sizeof(char));

                fout.write((char*) &data[i].birth_date, sizeof(time_t));

                fout.write((char*) &data[i].id, sizeof(int));
            }
            fout.close();
            std::cout << "Informação salva com sucesso!!\n";
        }
    }


    vector<VirtualClient> restoreData(string file_name) {
        vector<VirtualClient> loaded_data = {};

        ifstream fin;

        fin.open(file_name);
        if(!fin.is_open()) {
            cout << "Algo deu errado ao tentar abrir o arquivo!\n";
        } else {
            int quantity;
            fin.read((char*) &quantity, sizeof(int));
            
            for(int i = 0; i < quantity; i++) {
                int name_size;
                fin.read((char*) &name_size, sizeof(int));

                string name(name_size, '\0');
                fin.read((char*) &name[0], name_size);

                char gender;
                fin.read((char*) &gender, sizeof(char));

                time_t birthdate;
                fin.read((char*) &birthdate, sizeof(time_t));

                int id;
                fin.read((char*) &id, sizeof(int));
                
                loaded_data.push_back(VirtualClient(name, gender, birthdate, id));
            }
            fin.close();
        }
        return loaded_data;
    }
}