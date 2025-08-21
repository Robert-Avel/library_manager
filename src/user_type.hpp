#include <string>
#include <iostream>
using namespace std;

class User {
    protected:
    string username;
    string password;
    Role user_role;

    public:
    User(string username_, string password_, Role role) {
        username = username_;
        password = password_;
        user_role = role;
    }

    string getUserName() {return username;}
    bool validadePassWord(string password_input) {return password_input == password;}
    string passwordInput(string input_text) {
        string password_;
        cout << input_text;
        char ch;
        //ch = getche(); ADICIONAR INPUT SECRETO
    }
};


class Role {
    protected:

    bool canRead = false;
    bool canCRUD = false;
    bool admPermition = false;
};


class Reader: public Role {
    public:
    Reader(string username_, string password_) {
        canRead = true;
    }
};


class Librarian: public Role {
    public:
    Librarian(string username_, string password_) {
        canRead = true;
        canCRUD = true;
    }
};