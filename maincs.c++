#include <iostream>
#include <filesystem>
#include <string>
#include <regex>
using namespace std;
namespace fs = std::filesystem;

void listAllFiles(const fs::path& path) {
    if (!fs::exists(path) || !fs::is_directory(path)) {
        ::cout << "Invalid directory.\n";
        return;
    }
    cout << "Files in directory: " << path << "\n";
    for (const auto& entry : fs::directory_iterator(path)) {
        if (fs::is_regular_file(entry.path()))
            cout << "  - " << entry.path().filename().string() << "\n";
    }
}

void listFilesByExtension(const fs::path& path) {
    string ext;
    cout << "Enter file extension (e.g., .txt): ";
    cin >> ext;

    for (const auto& entry : fs::directory_iterator(path)) {
        if (fs::is_regular_file(entry) && entry.path().extension() == ext) {
            cout << "  - " << entry.path().filename().string() << "\n";
        }
    }
}

void listFilesByPattern(const fs::path& path) {
    string pattern;
    cout << "Enter pattern (e.g., moha.*): ";
    cin >> pattern;

    string regexPattern = ::regex_replace(pattern, ::regex("\\*"), ".*");
    regexPattern = ::regex_replace(regexPattern, ::regex("\\?"), ".");

    regex fileRegex(regexPattern, ::regex_constants::icase);

    for (const auto& entry : fs::directory_iterator(path)) {
        if (fs::is_regular_file(entry) && ::regex_match(entry.path().filename().string(), fileRegex)) {
            cout << "  - " << entry.path().filename().string() << "\n";
        }
    }
}

void listFiles() {
    int choice;
    fs::path current = fs::current_path();

    cout << "\n[List Files Submenu]\n";
    cout << "[1] List All Files\n";
    cout << "[2] List Files by Extension\n";
    cout << "[3] List Files by Pattern\n";
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            listAllFiles(current);
            break;
        case 2:
            listFilesByExtension(current);
            break;
        case 3:
            listFilesByPattern(current);
            break;
        default:
            ::cout << "Invalid choice.\n";
    }
}

void createDirectory() {
    string dirName;
    cout << "Enter directory name to create: ";
    cin >> dirName;

    if (fs::exists(dirName)) {
        cout << "Error: Directory already exists.\n";
    } else {
        try {
            fs::create_directory(dirName);
            cout << "Directory created: " << dirName << "\n";
        } catch (const ::exception& e) {
            cout << "Error creating directory: " << e.what() << "\n";
        }
    }
}

void changeDirectory() {
    string newPath;
    cout << "Enter new directory path: ";
    cin >> newPath;

    if (fs::exists(newPath) && fs::is_directory(newPath)) {
        fs::current_path(newPath);
        cout << "Current directory changed to: " << fs::current_path() << "\n";
    } else {
        cout << "Error: Directory does not exist or is not accessible.\n";
    }
}

void mainMenu() {
    int choice;
    do {
        cout << "\n[Directory Management System]\n";
        cout << "Current Directory: " << fs::current_path() << "\n";
        cout << "[1] List Files\n";
        cout << "[2] Create Directory\n";
        cout << "[3] Change Directory\n";
        cout << "[4] Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                listFiles();
                break;
            case 2:
                createDirectory();
                break;
            case 3:
                changeDirectory();
                break;
            case 4:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 4);
}

int main() {
    mainMenu();
    return 0;
}
