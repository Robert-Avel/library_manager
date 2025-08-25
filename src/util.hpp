#include <string>
#include <iostream>
#include <vector>
using namespace std;


void listPrint(vector<string> &options) {
    for (int i = 0; i < options.size(); i++) {
        std::cout << "[ " << i << " ] - " << options[i] << std::endl;
    }
}


int inputInt(string input_text) {
    int user_input;
    cout << input_text;
    while (!(cin >> user_input)) {
        cout << "Digite um número válido: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    cin.ignore();
    return user_input;
}

int inputRange(vector<string> options) {
    //Função de validação de input, aceitando valores que estão dentro do range do array dado. retorna o index
    int user_in;
    listPrint(options);
    do {
        user_in = inputInt("Selecione a Opção: ");
    } while (0 > user_in or user_in >= options.size());

    return user_in;
}

string inputOption(std::vector<std::string> options) {
    int user_in;
    listPrint(options);
    do {
        user_in = inputInt("Selecione a Opção: ");
    } while (0 > user_in or user_in >= options.size());

    return options[user_in];
}


float moneyFormat(int int_value) {
    float float_value = int_value;
    return float_value / 100;
}


void lineDiv() {
    cout << "==========================\n";
}


string inputStr(string txt) {
    while (true) {
    string var;
    cout << txt;
    getline(cin, var);
    if (var.empty()) {
        cout << "Espaço em Branco, Tente Novamente!"<< "\n";
        //cin.ignore();
        } else {
        return var;
        } 
    }
    //cin.ignore(1000, '\n');
}


char genderInput() {
    int input = inputRange({"M - Male", "F - Female"});
    if (input == 0) {return 'M';}
    else {return 'F';}
}
