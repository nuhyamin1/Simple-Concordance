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
    std::cout << "  kwic <phrase> [context] - Find keyword in context\n";
    std::cout << "  freq [n]              - Show word frequencies (optional: top n words)\n";
    std::cout << "  freq <phrase>         - Show frequency of a specific word or phrase\n";
    std::cout << "  ngram <n>             - Generate n-grams\n";
    std::cout << "  sen <phrase>          - Show full sentences containing a word or phrase\n";
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
            
            // Read the entire phrase until we encounter a number or end of line
            std::string phrase;
            std::string token;
            while (iss >> token) {
                // Check if token is a number (context size)
                if (std::all_of(token.begin(), token.end(), ::isdigit)) {
                    context = std::stoi(token);
                    break;
                }
                if (!phrase.empty()) phrase += " ";
                phrase += token;
            }
            
            if (!phrase.empty()) {
                analyzer.showConcordance(phrase, context);
            } else {
                std::cout << "Usage: kwic <phrase> [context]\n";
            }
        } else if (command == "freq") {
            int limit = 0;
            std::string word;
            
            // Read the entire input after "freq"
            std::string restOfLine;
            std::getline(iss, restOfLine);
            
            // Trim leading whitespace
            restOfLine.erase(0, restOfLine.find_first_not_of(" \t"));
            
            if (restOfLine.empty()) {
                // No parameter, show all frequencies
                analyzer.showFrequencies();
            } else if (std::all_of(restOfLine.begin(), restOfLine.end(), ::isdigit)) {
                // It's a number, show top N frequencies
                limit = std::stoi(restOfLine);
                analyzer.showFrequencies(limit);
            } else {
                // It's a phrase, show its frequency
                analyzer.showWordFrequency(restOfLine);
            }
        } else if (command == "ngram") {
            int n = 2;
            iss >> n;
            analyzer.showNGrams(n);
        } else if (command == "sen" || command == "sentence") {
            // Read the entire phrase
            std::string phrase;
            std::getline(iss, phrase);
            
            // Trim leading whitespace
            phrase.erase(0, phrase.find_first_not_of(" \t"));
            
            if (!phrase.empty()) {
                analyzer.showSentence(phrase);
            } else {
                std::cout << "Usage: sen <word or phrase>\n";
            }
        } else {
            std::cout << "Unknown command. Type 'help' for available commands.\n";
        }
    }
    
    return 0;
}