#include "concordance.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iomanip>

ConcordanceAnalyzer::ConcordanceAnalyzer() {
}

ConcordanceAnalyzer::~ConcordanceAnalyzer() {
}

bool ConcordanceAnalyzer::loadFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    std::string content, line;
    while (std::getline(file, line)) {
        content += line + " ";
    }
    
    tokenize(content);
    calculateFrequencies();
    return true;
}

// Update the tokenize method to track sentences
void ConcordanceAnalyzer::tokenize(const std::string& text) {
    tokens.clear();
    sentences.clear();  // Clear sentences container
    std::string token;
    std::string currentSentence;
    
    for (size_t i = 0; i < text.length(); i++) {
        currentSentence += text[i];
        
        if (isAlphanumeric(text[i])) {
            token += text[i];
        } else {
            if (!token.empty()) {
                tokens.push_back(toLowerCase(token));
                token.clear();
            }
            
            // Check for sentence endings
            if (text[i] == '.' || text[i] == '!' || text[i] == '?') {
                if (i + 1 < text.length() && (text[i+1] == ' ' || text[i+1] == '\n')) {
                    sentences.push_back(currentSentence);
                    currentSentence.clear();
                }
            }
        }
    }
    
    if (!token.empty()) {
        tokens.push_back(toLowerCase(token));
    }
    
    if (!currentSentence.empty()) {
        sentences.push_back(currentSentence);
    }
}

// Add the showSentence method implementation
void ConcordanceAnalyzer::showSentence(const std::string& word) {
    std::string searchWord = toLowerCase(word);
    
    if (sentences.empty()) {
        std::cout << "No text loaded. Use 'load' command first.\n";
        return;
    }
    
    bool found = false;
    for (const auto& sentence : sentences) {
        std::string lowerSentence = toLowerCase(sentence);
        
        // Check if the word appears as a whole word in the sentence
        size_t pos = 0;
        while ((pos = lowerSentence.find(searchWord, pos)) != std::string::npos) {
            // Check if it's a whole word (surrounded by non-alphanumeric chars or at boundaries)
            bool isWordStart = (pos == 0 || !isAlphanumeric(lowerSentence[pos-1]));
            bool isWordEnd = (pos + searchWord.length() == lowerSentence.length() || 
                             !isAlphanumeric(lowerSentence[pos + searchWord.length()]));
            
            if (isWordStart && isWordEnd) {
                found = true;
                std::cout << sentence << std::endl;
                break;  // Only show each matching sentence once
            }
            pos += searchWord.length();
        }
    }
    
    if (!found) {
        std::cout << "Word '" << word << "' not found in any sentence.\n";
    }
}

void ConcordanceAnalyzer::calculateFrequencies() {
    wordFrequencies.clear();
    for (const auto& token : tokens) {
        wordFrequencies[token]++;
    }
}

void ConcordanceAnalyzer::showConcordance(const std::string& word, int context) {
    std::string searchWord = toLowerCase(word);
    
    if (tokens.empty()) {
        std::cout << "No text loaded. Use 'load' command first.\n";
        return;
    }
    
    bool found = false;
    for (size_t i = 0; i < tokens.size(); i++) {
        if (tokens[i] == searchWord) {
            found = true;
            
            // Print left context
            std::cout << "... ";
            for (int j = std::max(0, static_cast<int>(i) - context); j < i; j++) {
                std::cout << tokens[j] << " ";
            }
            
            // Print the keyword in uppercase
            std::cout << "[" << searchWord << "] ";
            
            // Print right context
            for (size_t j = i + 1; j < std::min(tokens.size(), i + context + 1); j++) {
                std::cout << tokens[j] << " ";
            }
            std::cout << "...\n";
        }
    }
    
    if (!found) {
        std::cout << "Word '" << word << "' not found in the text.\n";
    }
}

void ConcordanceAnalyzer::showFrequencies(int limit) {
    if (wordFrequencies.empty()) {
        std::cout << "No text loaded. Use 'load' command first.\n";
        return;
    }
    
    // Convert map to vector for sorting
    std::vector<std::pair<std::string, int>> freqVec(
        wordFrequencies.begin(), wordFrequencies.end());
    
    // Sort by frequency (descending)
    std::sort(freqVec.begin(), freqVec.end(), 
        [](const auto& a, const auto& b) { return a.second > b.second; });
    
    // Determine how many items to show
    size_t count = limit > 0 ? std::min(static_cast<size_t>(limit), freqVec.size()) : freqVec.size();
    
    // Print header
    std::cout << std::left << std::setw(20) << "WORD" << "FREQUENCY\n";
    std::cout << std::string(30, '-') << "\n";
    
    // Print frequencies
    for (size_t i = 0; i < count; i++) {
        std::cout << std::left << std::setw(20) << freqVec[i].first 
                  << freqVec[i].second << "\n";
    }
}

void ConcordanceAnalyzer::showNGrams(int n) {
    if (tokens.empty() || n <= 0) {
        std::cout << "No text loaded or invalid n-gram size.\n";
        return;
    }
    
    std::map<std::string, int> ngrams;
    
    for (size_t i = 0; i <= tokens.size() - n; i++) {
        std::string ngram;
        for (int j = 0; j < n; j++) {
            ngram += tokens[i + j];
            if (j < n - 1) ngram += " ";
        }
        ngrams[ngram]++;
    }
    
    // Convert map to vector for sorting
    std::vector<std::pair<std::string, int>> ngramVec(
        ngrams.begin(), ngrams.end());
    
    // Sort by frequency (descending)
    std::sort(ngramVec.begin(), ngramVec.end(), 
        [](const auto& a, const auto& b) { return a.second > b.second; });
    
    // Print header
    std::cout << std::left << std::setw(30) << n << "-GRAM" << "FREQUENCY\n";
    std::cout << std::string(40, '-') << "\n";
    
    // Print top 20 n-grams
    size_t count = std::min(static_cast<size_t>(20), ngramVec.size());
    for (size_t i = 0; i < count; i++) {
        std::cout << std::left << std::setw(30) << ngramVec[i].first 
                  << ngramVec[i].second << "\n";
    }
}

std::string ConcordanceAnalyzer::toLowerCase(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), 
        [](unsigned char c) { return std::tolower(c); });
    return result;
}

bool ConcordanceAnalyzer::isAlphanumeric(char c) {
    // Cast to unsigned char to avoid negative values
    unsigned char uc = static_cast<unsigned char>(c);
    return std::isalnum(uc) || c == '\'' || c == '-';
}


void ConcordanceAnalyzer::showWordFrequency(const std::string& word) {
    if (wordFrequencies.empty()) {
        std::cout << "No text loaded. Use 'load' command first.\n";
        return;
    }
    
    std::string searchWord = toLowerCase(word);
    
    if (wordFrequencies.find(searchWord) != wordFrequencies.end()) {
        std::cout << searchWord << " " << wordFrequencies[searchWord] << "\n";
    } else {
        std::cout << searchWord << " 0\n";
    }
}  // Add this closing brace for showWordFrequency method