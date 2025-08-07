#include <iostream>
#include <filesystem>
#include <string>
#include <regex>

namespace fs = std::filesystem;

void listAllFiles(const fs::path& path) {
    if (!fs::exists(path) || !fs::is_directory(path)) {
        std::cout << "Invalid directory.\n";
        return;
    }
    std::cout << "Files in directory: " << path << "\n";
    for (const auto& entry : fs::directory_iterator(path)) {
        if (fs::is_regular_file(entry.path()))
            std::cout << "  - " << entry.path().filename().string() << "\n";
    }
}

void listFilesByExtension(const fs::path& path) {
    std::string ext;
    std::cout << "Enter file extension (e.g., .txt): ";
    std::cin >> ext;

    for (const auto& entry : fs::directory_iterator(path)) {
        if (fs::is_regular_file(entry) && entry.path().extension() == ext) {
            std::cout << "  - " << entry.path().filename().string() << "\n";
        }
    }
}

void listFilesByPattern(const fs::path& path) {
    std::string pattern;
    std::cout << "Enter pattern (e.g., moha.*): ";
    std::cin >> pattern;

    std::string regexPattern = std::regex_replace(pattern, std::regex("\\*"), ".*");
    regexPattern = std::regex_replace(regexPattern, std::regex("\\?"), ".");

    std::regex fileRegex(regexPattern, std::regex_constants::icase);

    for (const auto& entry : fs::directory_iterator(path)) {
        if (fs::is_regular_file(entry) && std::regex_match(entry.path().filename().string(), fileRegex)) {
            std::cout << "  - " << entry.path().filename().string() << "\n";
        }
    }
}

void listFiles() {
    int choice;
    fs::path current = fs::current_path();

    std::cout << "\n[List Files Submenu]\n";
    std::cout << "[1] List All Files\n";
    std::cout << "[2] List Files by Extension\n";
    std::cout << "[3] List Files by Pattern\n";
    std::cout << "Enter choice: ";
    std::cin >> choice;

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
            std::cout << "Invalid choice.\n";
    }
}

void createDirectory() {
    std::string dirName;
    std::cout << "Enter directory name to create: ";
    std::cin >> dirName;

    if (fs::exists(dirName)) {
        std::cout << "Error: Directory already exists.\n";
    } else {
        try {
            fs::create_directory(dirName);
            std::cout << "Directory created: " << dirName << "\n";
        } catch (const std::exception& e) {
            std::cout << "Error creating directory: " << e.what() << "\n";
        }
    }
}

void changeDirectory() {
    std::string newPath;
    std::cout << "Enter new directory path: ";
    std::cin >> newPath;

    if (fs::exists(newPath) && fs::is_directory(newPath)) {
        fs::current_path(newPath);
        std::cout << "Current directory changed to: " << fs::current_path() << "\n";
    } else {
        std::cout << "Error: Directory does not exist or is not accessible.\n";
    }
}

void mainMenu() {
    int choice;
    do {
        std::cout << "\n[Directory Management System]\n";
        std::cout << "Current Directory: " << fs::current_path() << "\n";
        std::cout << "[1] List Files\n";
        std::cout << "[2] Create Directory\n";
        std::cout << "[3] Change Directory\n";
        std::cout << "[4] Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

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
                std::cout << "Exiting program...\n";
                break;
            default:
                std::cout << "Invalid choice.\n";
        }
    } while (choice != 4);
}

int main() {
    mainMenu();
    return 0;
}
