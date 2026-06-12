#include <iostream>
#include <cctype>
#include <string>
#include <limits>
#include <vector>

// create branch for the score breakdown

// ----- INITIALIZATION CODE -----
void showStartMenu();
void showCheckPasswordMenu();
void showAddBookmarkMenu(int startLimit, int endLimit);

struct Password {
    int id {};
    bool hasSymbol = false;
    bool hasUpper = false;
    bool hasNum = false;
    int power = 0;
    int length {};
    std::string password {};
};

std::vector<Password> history = {};
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
std::vector<Password*> bookmarks = {};

// ----- LOGIC CODE -----

// adding the id here is not yet implemented.
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

// ----- DISPLAY CODE ------

void showLineBreak() {
    std::cout << "\n═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════\n\n";
}

void showHistoryMenu() {
    bool isShown = true;
    int limit = 5;
    int currentshown = 0;
    do {
        showLineBreak();
        std::string historyAscii[11] = {
            "$$\\   $$\\ $$\\                                     ",
            "$$ |  $$ |\\__|            $$ |                    ",
            "$$ |  $$ |$$\\  $$$$$$$\\ $$$$$$\\    $$$$$$\\   $$$$$$\\  $$\\   $$\\ ",
            "$$$$$$$$ |$$ |$$  _____|\\_$$  _|  $$  __$$\\ $$  __$$\\ $$ |  $$ |",
            "$$  __$$ |$$ |\\$$$$$$\\    $$ |    $$ /  $$ |$$ |  \\__|$$ |  $$ |",
            "$$ |  $$ |$$ | \\____$$\\   $$ |$$\\ $$ |  $$ |$$ |      $$ |  $$ |",
            "$$ |  $$ |$$ |$$$$$$$  |  \\$$$$  |\\$$$$$$  |$$ |      \\$$$$$$$ |",
            "\\__|  \\__|\\__|\\_______/    \\____/  \\______/ \\__|       \\____$$ |",
            "                                                      $$\\   $$ |",
            "                                                      \\$$$$$$  |",
            "                                                       \\______/ "
        };

        for (std::string line : historyAscii) {
            std::cout << line << "\n";
        }

        std::cout << "\n[N]ext [P]revious [B]ookmark [E]xit";
        showLineBreak();

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

        std::cout << "\n\n───🡆 ";
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
                break;
            case 'B':
            case 'b':
                showAddBookmarkMenu(currentshown, limit);
                break;
            case 'E':
            case 'e':
                isShown = false;
                showStartMenu();
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

void showStartMenu() {
    bool isShown = true;
    do {
        showLineBreak();
        std::string titleAscii[7] = {
            "  __                                           __                                           __                               ",
            " /  |                                  |      /    /                        /    /         /    /              /             ",
            "(___| ___  ___  ___       ___  ___  ___|     (___ (___  ___  ___  ___  ___ (___ (___      (    (___  ___  ___ (     ___  ___ ",
            "|    |   )|___ |___ |   )|   )|   )|   )         )|    |   )|___)|   )|   )|    |   )     |   )|   )|___)|    |___)|___)|   )",
            "|    |__/| __/  __/ |/\\/ |__/ |    |__/       __/ |__  |    |__  |  / |__/ |__  |  /      |__/ |  / |__  |__  | \\  |__  |    ",
            "                                                                      __/                                                    "
        };
        for (std::string line : titleAscii) {
            std::cout << line << "\n";
        }
        std::cout << "[C]heck Password\n";
        std::cout << "[H]istory\n";
        std::cout << "[B]ookmarks\n";
        std::cout << "[E]xit\n";

        char input {};
        std::cout << "\n\n───🡆 ";
        std::cin >> input;

        switch (input) {
            case 'C':
            case 'c':
                isShown = false;
                showCheckPasswordMenu();
                break;
            case 'H':
            case 'h':
                isShown = false;
                showHistoryMenu();
                break;
            case 'B':
            case 'b':
                break;
            case 'E':
            case 'e':
                isShown = false;
                break;
            default:
                break;
        }
    } while (isShown);
}

void showCheckPasswordMenu() {
    bool isShown = true;
    do {
        std::cout << "\n═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════\n\n";

        std::string passwordAscii[8] = {
            "$$$$$$$\\                                                                       $$\\ ",
            "$$  __$$\\                                                                      $$ |",
            "$$ |  $$ |$$$$$$\\   $$$$$$$\\  $$$$$$$\\ $$\\  $$\\  $$\\  $$$$$$\\   $$$$$$\\   $$$$$$$ |",
            "$$$$$$$  |\\____$$\\ $$  _____|$$  _____|$$ | $$ | $$ |$$  __$$\\ $$  __$$\\ $$  __$$ |",
            "$$  ____/ $$$$$$$ |\\$$$$$$\\  \\$$$$$$\\  $$ | $$ | $$ |$$ /  $$ |$$ |  \\__|$$ /  $$ |",
            "$$ |     $$  __$$ | \\____$$\\  \\____$$\\ $$ | $$ | $$ |$$ |  $$ |$$ |      $$ |  $$ |",
            "$$ |     \\$$$$$$$ |$$$$$$$  |$$$$$$$  |\\$$$$$\\$$$$  |\\$$$$$$  |$$ |      \\$$$$$$$ |",
            "\\__|      \\_______|\\_______/ \\_______/  \\_____\\____/  \\______/ \\__|       \\_______|",
        };

        for (std::string line : passwordAscii) {
            std::cout << line << "\n";
        }
        std::cout << "\n/exit to return to main menu";
        std::cout << "\n═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════\n\n";
        std::string input;
        std::cout << "Password:: ";

        std::cin >> input;

        if (input == "/exit") {
            isShown = false;
            showStartMenu();
        }

        Password pass = checkPass(input);

        std::cout << "score: " << pass.power << "\n";
        std::cout << parsePassPower(pass.power);
        std::cout << "\n\n";
        // insert breakdown of password
        std::cin.get();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (isShown);
}

int main() {
    showStartMenu();
}
