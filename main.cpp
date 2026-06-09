#include <iostream>
#include <cctype>
#include <string>

// features idea:
// - password history
// - score breakdown
// - maybe bookmarking password (having names)
//     - When testing passwords, it will check if it
//         already exist on the bookmark

// - [x] at least one loop
// - [x] at least one conditional
// - [x] at least one switch
// - [x] Include two or more user-defined functions
// - [ ] Store and manipulate data using arrays and array pointers
// - [x] Use strings for input and output operations
// - [x] Incorporate the cctype library to validate or manipulate characters

struct Password {
    bool hasSymbol = false;
    bool hasUpper = false;
    bool hasNum = false;
    int power = 0;
    int length {};
    std::string password {};
};

Password checkPass(std::string inputPassword) {
    Password pass {};
    pass.password = inputPassword;
    pass.length = inputPassword.length();

    for (char c : inputPassword) {
        if (!pass.hasSymbol && std::ispunct(c)) {
            pass.hasSymbol = true;
            pass.power++;
            continue;
        }
        if (!pass.hasUpper && std::isupper(c) ) {
            pass.hasUpper = true;
            pass.power++;
            continue;
        }
        if (!pass.hasNum && std::isdigit(c)) {
            pass.hasNum = true;
            pass.power++;
        }
    }

    int length = pass.length;
    while (length > 4) {
        pass.power++;
        length -= 4;
    }

    return pass;
}

std::string parsePassPower(int power) {
    switch (power) {
        case 0:
        case 1:
            return "bad";
        case 2:
        case 3:
           return "okay";
        case 4:
        case 5:
        case 6:
            return "good";
        default:
            return "great";
    }
}

int main() {
    do {
        std::string input;
        std::cout << "password: ";
        std::cin >> input;

        Password pass = checkPass(input);

        // great password is >7 points;
        // good password is 4-6  points;
        // okay password is 2-3 points
        // bad password is 1 points
        std::cout << "score: " << pass.power << "\n";
        std::cout << parsePassPower(pass.power);
        std::cout << "\n\n";
    } while (true);
}