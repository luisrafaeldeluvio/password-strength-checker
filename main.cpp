#include <iostream>
#include <cctype>
#include <string>
#include <limits>
#include <vector>

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

Password checkPassword(std::string inputPassword);
std::string parsePasswordPower(int power);
void addToHistory(Password password);
void showLineBreak();
void showStartMenu();
void showPasswordMenu();
void showPasswordScoreBreakdown(Password password);
void showHistoryMenu();

int HISTORY_CAPACITY = 100;
int historySize = 0;
Password history[100] = {};
Password *ptrHistory = history;

// ----- LOGIC CODE -----
Password checkPassword(std::string inputPassword) {
    Password password {};
    password.id = historySize;
    password.password = inputPassword;
    password.length = inputPassword.length();

    // Check if the password contains symbols, capital letters, and numbers
    for (char c : inputPassword) {
        if (std::ispunct(c)) {
            password.symbolCount++;
            if (!password.hasSymbol) {
                password.hasSymbol = true;
                password.power++;
            }
        }
        else if (std::isupper(c)) {
            password.upperCount++;
            if (!password.hasUpper) {
                password.hasUpper = true;
                password.power++;
            }
        }
        else if (std::isdigit(c)) {
            password.numCount++;
            if (!password.hasNum) {
                password.hasNum = true;
                password.power++;
            }
        }
    }

    // Gives 1 point for every 4 characters of the password.
    int length = password.length;
    while (length > 4) {
        password.power++;
        length -= 4;
    }

    return password;
}

std::string parsePasswordPower(int power) {
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

void addToHistory(Password password) {
    *(ptrHistory + historySize) = password;
    historySize++;
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
                showPasswordMenu();
                break;
            case 'H':
            case 'h':
                isShown = false;
                showHistoryMenu();
                break;
            case 'E':
            case 'e':
                isShown = false;
                return;
                break;
            default:
                break;
        }
    } while (isShown);
}

void showPasswordMenu() {
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
            continue;
        }

        Password password = checkPassword(input);
        addToHistory(password);

        showPasswordScoreBreakdown(password);
        std::cin.get();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (isShown);
}

void showPasswordScoreBreakdown(Password password) {
    showLineBreak();

    std::cout << "This is a " << parsePasswordPower(password.power) << " password.\n";
    std::cout << "\n\t\t\t\tSCORE BREAKDOWN\n";

    if (password.hasSymbol) {
        std::cout << "\t\t" << password.symbolCount << " symbol/s \t\t\t\t\t+1\n";
    } else {
        std::cout << "\t\tNo symbols \t\t\t\t\t+0\n";
    }

    if (password.hasUpper) {
        std::cout << "\t\t" << password.upperCount << " uppercase letter/s \t\t+1\n";
    } else {
        std::cout << "\t\tNo uppercase letters \t\t+0\n";
    }

    if (password.hasNum) {
        std::cout << "\t\t" << password.numCount << " number/s \t\t\t\t\t+1\n";
    } else {
        std::cout << "\t\tNo numbers, \t\t\t\t+0\n";
    }

    int length = password.length;
    int powerFromLength {};
    while (length > 4) {
        powerFromLength++;
        length -= 4;
    }

    std::cout << "\t\t" << password.length << " character/s long \t\t+" << powerFromLength << "\n";
    std::cout << "-----------------------------------------------\n";
    std::cout << "\t\t\t\t\t" << password.power << " points\n";
}

// Displays the password on pages.
void showHistoryMenu() {
    bool isShown = true;
    int MAX_PASSWORD_TO_SHOW = 5;
    int startingIndex = 0;
    int page = 1;

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

        std::cout << "\n[P]revious [N]ext [E]xit | " << page << " of " << (historySize + MAX_PASSWORD_TO_SHOW - 1) / MAX_PASSWORD_TO_SHOW;
        showLineBreak();

        for (int i = startingIndex; i < std::min((startingIndex + MAX_PASSWORD_TO_SHOW), historySize); i++) {
            std::cout << (ptrHistory + i)->password << "\n";
        }

        std::cout << "\n\n───🡆 ";
        char input {};
        std::cin >> input;
        switch (input) {
            case 'P':
            case 'p':
                if (startingIndex - MAX_PASSWORD_TO_SHOW < 0) break;
                startingIndex -= MAX_PASSWORD_TO_SHOW;
                page--;
                break;
            case 'N':
            case 'n':
                if (startingIndex + MAX_PASSWORD_TO_SHOW >= historySize) break;
                startingIndex += MAX_PASSWORD_TO_SHOW;
                page++;
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