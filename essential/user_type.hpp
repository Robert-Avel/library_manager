#include <string>
#include <iostream>
using namespace std;

class BaseUser {
    protected:
    string username;
    string password;

    bool canRead = false;
    bool canCRUD = false;
    bool admPermition = false;

    public:
    BaseUser(string username_, string password_) {
        username = username_;
        password = password_;
    }
};


class Reader: public BaseUser {
    public:
    Reader(string username_, string password_): BaseUser(username_, username_){
        canRead = true;
    }
};


class Librarian: public BaseUser {
    public:
    Librarian(string username_, string password_): BaseUser(username_, username_) {
        canRead = true;
        canCRUD = true;
    }
};