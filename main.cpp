#include <iostream>
#include <cctype>
#include <limits>
#include <string>
#include <vector>

void showStartMenu();
void showCheckPasswordMenu();

struct Password {
    int id {};
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

void showPassword(Password pass) {
    std::cout << pass.password << " - " << parsePassPower(pass.power);
}

std::vector<Password> history = {
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
    {11, false, true,  true,  5,  8, "Mix42B"},
    {12, true,  true,  false, 6, 13, "AlphaBeta#9"},
    {13, false, false, false, 0,  5, "weak"},
    {14, true,  false, true,  4,  9, "test!2"},
    {15, false, true,  false, 2,  7, "UPPERNO"},
    {16, true,  true,  true,  7, 12, "F!ght0n#"},
    {17, false, true,  true,  5, 10, "Win2024"},
    {18, true,  false, false, 1,  6, "!@#$%^"},
    {19, false, false, true,  3,  8, "88888888"},
    {20, true,  true,  true,  7, 14, "C0mpl3x!ty"}
};

void showStartMenu() {
    bool isShown = true;
    do {
        std::cout << "\n═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════\n\n";
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
        std::cout << "[1]. Check Password\n";
        std::cout << "[2]. History\n";
        std::cout << "[3]. Bookmarks\n";
        std::cout << "[0]. Exit\n";

        int input {};
        std::cout << "\n\n───🡆 ";
        std::cin >> input;

        switch (input) {
            case 1:
                isShown = false;
                showCheckPasswordMenu();
                break;
            case 0:
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
