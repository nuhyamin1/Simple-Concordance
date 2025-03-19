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
    void showConcordance(const std::string& word, int context);
    void showFrequencies(int limit = 0);
    void showWordFrequency(const std::string& word); // New function
    void showNGrams(int n);
    
private:
    std::vector<std::string> tokens;
    std::map<std::string, int> wordFrequencies;
    
    void tokenize(const std::string& text);
    void calculateFrequencies();
    std::string toLowerCase(const std::string& str);
    bool isAlphanumeric(char c);
};

#endif // CONCORDANCE_H