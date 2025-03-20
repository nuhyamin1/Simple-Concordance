#ifndef CONCORDANCE_H
#define CONCORDANCE_H

#include <string>
#include <vector>
#include <map>

class ConcordanceAnalyzer {
public:
    ConcordanceAnalyzer();
    ~ConcordanceAnalyzer();
    
    bool loadFile(const std::string& filename);
    void showConcordance(const std::string& word, int context = 5);
    void showFrequencies(int limit = 0);
    void showNGrams(int n);
    void showWordFrequency(const std::string& word);
    void showSentence(const std::string& word);  // New method
    
private:
    void tokenize(const std::string& text);
    void calculateFrequencies();
    std::string toLowerCase(const std::string& str);
    bool isAlphanumeric(char c);
    
    std::vector<std::string> tokens;
    std::vector<std::string> sentences;  // New member to store sentences
    std::map<std::string, int> wordFrequencies;
};

#endif // CONCORDANCE_H