#include "data.h"
#include "user.h"
#include <iostream>

int main() {
    while (true) {
        //std::cout << "Select Your Role:\n\t1) Provider\n\t2) Manager\n\t3) Operator\n\t4)quit\n(Input a number then press Enter)\n";
        std::cout << "Select Your Role:\n\t1) Provider\n\t2) Manager\n\t3) Operator\n\t4) Member\n\t5) Quit\n(Input a number then press Enter)\n";
        int option;
        std::cin >> option;
        std::cin.ignore(9999999, '\n');

        User* user;

        switch(option) {
        case(1):
            user = new Provider;
            break;
        case(2):
            user = new Manager;
            break;
        case(3):
            user = new Operator;
            break;
        case(4):
            user = new Member;
            break;
        case(5):
            //user = new Member;
            return 0;
        default:
            std::cout << "Invalid option, try again.\n";
            continue;
        }

        user->Flow();
    }

    return 0;
}
