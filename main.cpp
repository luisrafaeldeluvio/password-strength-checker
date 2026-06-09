#include <iostream>
#include <cctype>
#include <string>

// features idea:
// - password history
// - score breakdown
// - maybe bookmarking password (having names)
//     - When testing passwords, it will check if it
//         already exist on the bookmark

// struct password {
//     bool hasSymbol = false;
//     bool hasUpper = false;
//     bool hasNum = false;
//     int length {};
//     std::string password {};
// };
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

// maybe create a git

int main()
{
    do {
        std::string input;
        int power = 0;
        std::cout << "pass: ";
        std::cin >> input;

        for (char c : input) {
            if (std::ispunct(c)) {
                power++;
                break;
            }
        }
        for (char c : input) {
            if (std::isupper(c) ) {
                power++;
                break;
            }
        }
        for (char c : input) {
            if (std::isdigit(c)) {
                power++;
                break;
            }
        }
        int pLength = input.length();

        while (pLength > 4) {
            power++;
            pLength -= 4;
        }

        // great password is >7 points;
        // good password is 4-6  points;
        // okay password is 2-3 points
        // bad password is 1 points

        std::cout << "score: " << power << "\n";

        switch (power) {
            case 0:
            case 1:
                std::cout << "bad";
                break;
            case 2:
            case 3:
                std::cout << "okay";
                break;
            case 4:
            case 5:
            case 6:
                std::cout << "good";
                break;
            default:
                std::cout << "great";
                break;
        }
        std::cout << "\n\n";
    } while (true);

    // features idea:
    // - password history
    // - score breakdown
    // - maybe bookmarking password (having names)
    //     - When testing passwords, it will check if it
    //         already exist on the bookmark

}