#include <iostream>
#include <cctype>
#include <string>
#include <limits>
#include <vector>

// TODO:
// - [/] Implement ID system on checkPass(). I think I should base the ID on the history's vector length since some function rely on a linear ID.
// - [ ] Add history logic code.
// - [ ] BUG: Right now, on the history pagination, you can go back and go forward too much. Add a limit.
// - [ ] change pass to password
// - [ ] choose power or score or points

// ----- INITIALIZATION CODE -----
struct Password {
    int id {};
    bool hasSymbol = false;
    bool hasUpper = false;
    bool hasNum = false;
    int symbolCount = 0;
    int upperCount = 0;
    int numCount = 0;
    int power = 0;
    int length {};
    std::string password {};
};

Password checkPass(std::string inputPassword);
std::string parsePassPower(int power);
void showLineBreak();
void showStartMenu();
void showCheckPasswordMenu();
void showPasswordScoreBreakdown(Password pass);
void showHistoryMenu();

int HISTORY_CAPACITY = 100;
int historySize = 0;
Password history[100] = {
    // {1,  true,  true,  true,  2,    1,   4,    3,   12,  "P@ssw0rd!123"},
    // {2,  true,  true,  true,  1,    1,   2,    3,   9,   "Secure99#"},
    // {3,  true,  false, true,  1,    0,   1,    2,   7,   "d0llar$"},
    // {4,  false, true,  true,  0,    2,   2,    2,   12,  "HelloWorld42"},
    // {5,  true,  true,  true,  4,    2,   1,    3,   11,  "C++Rocks!2#"},
    // {6,  false, true,  false, 0,    2,   0,    1,   9,   "OnlyUpper"},
    // {7,  true,  false, false, 1,    0,   0,    1,   7,   "$ymbols"},
    // {8,  false, false, true,  0,    0,   6,    1,   6,   "123456"},
    // {9,  true,  true,  true,  2,    2,   1,    3,   11,  "Str0ng!P#ss"},
    // {10, true,  false, true,  1,    0,   1,    2,   8,   "an0ther$"}
};

// ----- LOGIC CODE -----
Password checkPass(std::string inputPassword) {
    Password pass {};
    pass.id = historySize;
    pass.password = inputPassword;
    pass.length = inputPassword.length();

    for (char c : inputPassword) {
        if (std::ispunct(c)) {
            pass.symbolCount++;
            if (!pass.hasSymbol) {
                pass.hasSymbol = true;
                pass.power++;
            }
        }
        else if (std::isupper(c)) {
            pass.upperCount++;
            if (!pass.hasUpper) {
                pass.hasUpper = true;
                pass.power++;
            }
        }
        else if (std::isdigit(c)) {
            pass.numCount++;
            if (!pass.hasNum) {
                pass.hasNum = true;
                pass.power++;
            }
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
           return "fair";
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
        std::cout << "By LRRD & LGTR";
        showLineBreak();
        std::cout << "[C]heck Password\n";
        std::cout << "[H]istory\n";
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
        showLineBreak();
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
        showLineBreak();

        std::string input;
        std::cout << "Password:: ";
        std::cin >> input;

        if (input == "/exit") {
            isShown = false;
            showStartMenu();
        }

        Password pass = checkPass(input);
        history[historySize] = pass;
        historySize++;

        showPasswordScoreBreakdown(pass);
        std::cin.get();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (isShown);
}

void showPasswordScoreBreakdown(Password pass) {
    showLineBreak();

    std::cout << "This is a " << parsePassPower(pass.power) << " password.\n";
    std::cout << "\n\t\t\t\tSCORE BREAKDOWN\n";

    if (pass.hasSymbol) {
        std::cout << "\t\t" << pass.symbolCount << " symbol/s \t\t\t\t\t+1\n";
    } else {
        std::cout << "\t\tNo symbols \t\t\t\t\t+0\n";
    }

    if (pass.hasUpper) {
        std::cout << "\t\t" << pass.upperCount << " uppercase letter/s \t\t+1\n";
    } else {
        std::cout << "\t\tNo uppercase letters \t\t+0\n";
    }

    if (pass.hasNum) {
        std::cout << "\t\t" << pass.numCount << " number/s \t\t\t\t\t+1\n";
    } else {
        std::cout << "\t\tNo numbers, \t\t\t\t+0\n";
    }

    int length = pass.length;
    int powerFromLength {};
    while (length > 4) {
        powerFromLength++;
        length -= 4;
    }

    std::cout << "\t\t" << pass.length << " character/s long \t\t+" << powerFromLength << "\n";
    std::cout << "-----------------------------------------------\n";
    std::cout << "\t\t\t\t\t" << pass.power << " points\n";
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

        std::cout << "\n[N]ext [P]revious [E]xit";
        showLineBreak();

        int shown = currentshown;
        for (int i = currentshown; i < historySize; i++) {
            if (shown > limit - 1) break;
            std::cout << history[i].password << "\n";
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

int main() {
    showStartMenu();
}
