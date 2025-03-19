#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>
#include <sstream>
#include "concordance.h"

void printHelp() {
    std::cout << "Simple Concordance Tool\n";
    std::cout << "Commands:\n";
    std::cout << "  load <filename>       - Load a text file\n";
    std::cout << "  kwic <word> <context> - Find keyword in context\n";
    std::cout << "  freq [n]              - Show word frequencies (optional: top n words)\n";
    std::cout << "  ngram <n>             - Generate n-grams\n";
    std::cout << "  help                  - Show this help\n";
    std::cout << "  exit                  - Exit the program\n";
}

int main() {
    ConcordanceAnalyzer analyzer;
    std::string command, line;
    
    std::cout << "Simple Concordance Tool\n";
    std::cout << "Type 'help' for available commands\n";
    
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, line);
        std::istringstream iss(line);
        iss >> command;
        
        if (command == "exit") {
            break;
        } else if (command == "help") {
            printHelp();
        } else if (command == "load") {
            std::string filename;
            iss >> filename;
            if (analyzer.loadFile(filename)) {
                std::cout << "File loaded successfully.\n";
            } else {
                std::cout << "Failed to load file.\n";
            }
        } else if (command == "kwic") {
            std::string word;
            int context = 5;
            iss >> word;
            iss >> context;
            analyzer.showConcordance(word, context);
        } else if (command == "freq") {
            int limit = 0;
            iss >> limit;
            analyzer.showFrequencies(limit);
        } else if (command == "ngram") {
            int n = 2;
            iss >> n;
            analyzer.showNGrams(n);
        } else {
            std::cout << "Unknown command. Type 'help' for available commands.\n";
        }
    }
    
    return 0;
}