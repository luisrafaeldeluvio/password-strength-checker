#include <iostream>
#include <cctype>
#include <string>
#include <vector>

// - maybe bookmarking password (having names)
//     - When testing passwords, it will check if it
//         already exist on the bookmark
struct Password {
    int id {};
    bool hasSymbol = false;
    bool hasUpper = false;
    bool hasNum = false;
    int power = 0;
    int length {};
    std::string password {};
};

void showAddBookmarkMenu(int startLimit, int endLimit);

std::vector<Password> history = {};
std::vector<Password*> bookmarks = {};

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

std::vector<Password> mockHistory = {
    {1,  true,  true,  true,  7, 12, "P@ssw0rd!123"},
    {2,  true,  true,  false, 5, 10, "Secure99#"},
    {3,  true,  false, true,  4,  8, "d0llar$"},
    {4,  false, true,  true,  6, 11, "HelloWorld42"},
    {5,  true,  true,  true,  7, 14, "C++Rocks!2#"},
    {6,  false, true,  false, 2,  9, "OnlyUpper"},
    {7,  true,  false, false, 1,  7, "$ymbols"},
    {8,  false, false, true,  3,  6, "123456"},
    {9,  true,  true,  true,  7, 15, "Str0ng!P#ss"},
    {10, true,  false, true,  4, 10, "an0ther$"},
};

void showHistoryMenu() {

    bool isShown = true;
    int limit = 5;
    int currentshown = 0;
    do {
        std::cout << "[N]ext [P]revious [B]ookmark [E]xit\n";
        int shown = currentshown;
        for (int i = currentshown; i < mockHistory.size(); i++) {
            if (shown > limit - 1) break;
            std::cout << "[" << i + 1 << "]";
            for (Password *j : bookmarks) {
                if (j->id == mockHistory[i].id) {
                    std::cout << "*";
                    break;
                }
            }
            std::cout << " " << mockHistory[i].password << "\n";
            shown++;
        }

        std::cout << "--> ";
        char input {};
        std::cin >> input;
        switch (input) {
            case 'N':
            case 'n':
                limit += 5;
                currentshown = shown;
                break;
            case 'P':
            case 'p':
                limit -= 5;
                currentshown -= 5;
            case 'B':
                showAddBookmarkMenu(currentshown, limit);
                break;
            case 'E':
                isShown = false;
                break;
            default:

                break;
        }
    } while (isShown);

}

void showAddBookmarkMenu(int startLimit, int endLimit) {
    bool isShown = true;
    do {
        std::cout << "Select the password to bookmark (1~10): ";
        std::cout << "Enter 0 to cancel";
        int choice;
        std::cin >> choice;

        if (choice == 0) isShown = false;
        if (choice > endLimit || choice < startLimit) {
         std::cout << "try again" << startLimit << "   " << endLimit;
            continue;
        }

        bookmarks.push_back(&mockHistory[choice-1]);
        std::cout << "\nBookmarks\n";
        for (Password *b : bookmarks) {
            std::cout << b->password << "\n";
        }
    } while (isShown);


}

int main() {
    // do {
    //     std::string input;
    //     std::cout << "password: ";
    //     std::cin >> input;
    //
    //     Password pass = checkPass(input);
    //
    //     // great password is >7 points;
    //     // good password is 4-6  points;
    //     // okay password is 2-3 points
    //     // bad password is 1 points
    //     std::cout << "score: " << pass.power << "\n";
    //     std::cout << parsePassPower(pass.power);
    //     std::cout << "\n\n";
    //
    // } while (true);

    // lets work on the bookmark picture,
    // the history will just be a vector of Password and the bookmark will just be vector or reference(&) from the history


    showHistoryMenu();


    // add a bookmark
    // bookmarks.push_back(&mockHistory[0]);
    //




}