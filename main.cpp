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
void toggleBookmark(Password *array, int arraySize, int arrayIndex);
void showLineBreak();
void showStartMenu();
void showPasswordMenu();
void showPasswordScoreBreakdown(Password password);
void showHistoryMenu();
void showBookmarkMenu(Password *passwordArray, int arraySize, void (*exitFunction)());

int HISTORY_CAPACITY = 100;
int BOOKMARKS_CAPACITY = 100;
int historySize = 0;
int bookmarksSize = 0;
Password history[100] = {};
Password *ptrHistory = history;
Password *bookmarks[100] = {};

// ----- LOGIC CODE -----

// Password parameter requirements are taken from CISA
// www.cisa.gov/audiences/small-and-medium-businesses/secure-your-business/require-strong-passwords
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

// add a password to the history array.
void addToHistory(Password password) {
    *(ptrHistory + historySize) = password;
    historySize++;
}

// *array - Points to the array of Password objects to inspect.
// arrayIndex - The specific index inside the array to evaluate.
// Dynamically add and remove a reference from the bookmarks array.
void toggleBookmark(Password *array,  int arraySize, int arrayIndex) {
    // prevent index from going under and over the array's size.
    if (arrayIndex >= arraySize || arrayIndex < 0) return;

    // checks if the selected password is already bookmarked.
    bool isBookmarked = false;
    int bookmarkedIndex {};
    for (int i = 0; i < bookmarksSize; i++) {
        if (array[arrayIndex].id == bookmarks[i]->id) {
            isBookmarked = true;
            bookmarkedIndex = i;
            break;
        }
    }

    // the bookmark is removed by replacing its value with the value of the next.
    if (isBookmarked) {
        for (int i = bookmarkedIndex; i < bookmarksSize - 1; i++) {
            bookmarks[i] = bookmarks[i + 1];
        }
        bookmarksSize--;
        return;
    }

    // if it's not bookmarked, bookmark it instead.
    bookmarks[bookmarksSize] = &array[arrayIndex];
    bookmarksSize++;
}

// ----- DISPLAY CODE ------

void showLineBreak() {
    std::cout << "\n═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════\n\n";
}

void showStartMenu() {
    bool isShown = true;
    do {
        showLineBreak();
        std::string titleAscii[8] = {
            " ________  ________  ________   ________  ___      ___ ________  ___  ___  ___   _________   ",
            "|\\   __  \\|\\   __  \\|\\   ____\\ |\\   ____\\|\\  \\    /  /|\\   __  \\|\\  \\|\\  \\|\\  \\ |\\___   ___\\ ",
            "\\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\___|_\\ \\  \\___|\\ \\  \\  /  / | \\  \\|\\  \\ \\  \\\\\\  \\ \\  \\\\|___ \\  \\_| ",
            " \\ \\   ____\\ \\   __  \\ \\_____  \\\\ \\_____  \\ \\  \\/  / / \\ \\   __  \\ \\  \\\\\\  \\ \\  \\    \\ \\  \\  ",
            "  \\ \\  \\___|\\ \\  \\ \\  \\|____|\\  \\\\|____|\\  \\ \\    / /   \\ \\  \\ \\  \\ \\  \\\\\\  \\ \\  \\____\\ \\  \\ ",
            "   \\ \\__\\    \\ \\__\\ \\__\\____\\_\\  \\ ____\\_\\  \\ \\__/ /     \\ \\__\\ \\__\\ \\_______\\ \\_______\\ \\__\\",
                "    \\|__|     \\|__|\\|__|\\_________\\\\_________\\|__|/       \\|__|\\|__|\\|_______|\\|_______|\\|__|",
            "                       \\|_________\\|_________|                                               ",
        };
        for (std::string line : titleAscii) {
            std::cout << line << "\n";
        }
        std::cout << "\t\t\t\t\tA Password Strength Checker with History and Bookmarking\n";
        std::cout << "By LRRD & LGTR";
        showLineBreak();
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
                showPasswordMenu();
                break;
            case 'H':
            case 'h':
                isShown = false;
                showHistoryMenu();
                break;
            case 'B':
            case 'b': {
                isShown = false;
                Password bm[100] {};
                for (int i = 0; i < bookmarksSize; i++) {
                    bm[i] = *bookmarks[i];
                }

                showBookmarkMenu(bm, bookmarksSize, showStartMenu);
                break;
            }
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

        // Allow the user to view the score breakdown without immediately asking for a new password.
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

void showHistoryMenu() {
    bool isShown = true;
    // Tells how many password is shown on screen.
    int MAX_PASSWORD_TO_SHOW = 5;
    // Tells which index to start on when showing the passwords.
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

        std::cout << "\n[P]revious [N]ext [B]ookmark [E]xit | " << page << " of "
        << (historySize + MAX_PASSWORD_TO_SHOW - 1) / MAX_PASSWORD_TO_SHOW; // A trick to round up historySize / MAX_PASSWORD_TO_SHOW.
        showLineBreak();

        // Displays the passwords.
        // std::min to make sure startingIndex + MAX_PASSWORD_TO_SHOW won't go over the size of history.
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
            case 'B':
            case 'b':
                isShown = false;
                showBookmarkMenu(history, historySize, showHistoryMenu);
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

// Made dynamic by accepting paremeters to avoid code duplication.
void showBookmarkMenu(Password *passwordArray, int arraySize, void (*exitFunction)()) {
    bool isShown = true;
    int MAX_PASSWORD_TO_SHOW = 5;
    int startingIndex = 0;
    int page = 1;

    do {
        showLineBreak();
        std::string bookmarkAscii[8] = {
            "$$$$$$$\\\\                      $$\\                                         $$\\       ",
            "$$  __$$\\                     $$ |                                        $$ |      ",
            "$$ |  $$ | $$$$$$\\   $$$$$$\\  $$ |  $$\\ $$$$$$\\$$\\$$\\   $$$$$$\\   $$$$$$\\  $$ |  $$\\ ",
            "$$$$$$$\\ |$$  __$$\\ $$  __$$\\ $$ | $$  |$$  _$$  _$$\\  \\____$$\\ $$  __$$\ $$ | $$  |",
            "$$  __$$\\ $$ /  $$ |$$ /  $$ |$$$$$$  / $$ / $$ / $$ | $$$$$$$ |$$ |  \\__|$$$$$$  / ",
            "$$ |  $$ |$$ |  $$ |$$ |  $$ |$$  _$$<  $$ | $$ | $$ |$$  __$$ |$$ |      $$  _$$<  ",
            "$$$$$$$  |\\$$$$$$  | \\$$$$$$  |$$ | \\$$\\ $$ | $$ | $$ |\\$$$$$$$ |$$ |      $$ | \\$$\\ ",
            "\\_______/  \\______/   \\______/ \\__|  \\__|\\__| \\__| \\__| \\_______|\\__|      \\__|  \\__|"
        };

        for (std::string line : bookmarkAscii) {
            std::cout << line << "\n";
        }

        std::cout << "\n[N]ext [P]revious [E]xit | " << page << " of " << (arraySize + MAX_PASSWORD_TO_SHOW - 1) / MAX_PASSWORD_TO_SHOW << " | Select the password to bookmark (1~" << arraySize << ")";
        showLineBreak();

        for (int i = startingIndex; i < std::min((startingIndex + MAX_PASSWORD_TO_SHOW), arraySize); i++) {
            std::cout << "[" << i + 1 << "]";

            for (int j = 0; j < bookmarksSize; j++) {
                if (bookmarks[j]->id == passwordArray[i].id) {
                    std::cout << "*";
                    break;
                }
            }
            std::cout << " " << passwordArray[i].password << "\n";
        }

        std::cout << "\n\n───🡆 ";
        std::string input;
        std::cin >> input;

        // Check input is a number.
        bool isInputNum = false;
        for (char c : input) {
            if (std::isdigit(c)) isInputNum = true;
        }

        // If it is, toggle bookmark and convert the input to a number.
        if (isInputNum) {
            toggleBookmark(passwordArray, arraySize, std::stoi(input) - 1);
            continue;
        }

        switch (input[0]) {
            case 'P':
            case 'p':
                if (startingIndex - MAX_PASSWORD_TO_SHOW < 0) break;
                startingIndex -= MAX_PASSWORD_TO_SHOW;
                page--;
                break;
            case 'N':
            case 'n':
                if (startingIndex + MAX_PASSWORD_TO_SHOW >= arraySize) break;
                startingIndex += MAX_PASSWORD_TO_SHOW;
                page++;
                break;
            case 'E':
            case 'e':
                isShown = false;
                exitFunction();
                break;
            default:
                break;
        }
    } while (isShown);
}

int main() {
    showStartMenu();
}