#include <iostream>
#include <cstring>
#include <chrono>
#include <fstream>

size_t countPalindromesFromCenter(const char* str, size_t n, size_t left, size_t right) {
    size_t count = 0;

    while (left >= 0 && right < n && *(str + left) == *(str + right)) {
        count++;  
        if (left == 0) break; 
        left--;  
        right++; 
    }

    return count;
}

size_t countAllPalindromes(const char* str) {
    if (!str) return 0; 

    size_t n = std::strlen(str);
    size_t totalCount = 0;

    for (size_t i = 0; i < n; ++i) {
        totalCount += countPalindromesFromCenter(str, n, i, i);
        totalCount += countPalindromesFromCenter(str, n, i, i + 1);
    }
    return totalCount;
}

int main() {
    std::string filename = "war-and-peace";  // Ensure the correct file path

    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string input;
    std::string line;
    
    // Read the file content line by line and concatenate into a single string
    while (std::getline(inputFile, line)) {
        input += line; // Append each line (without newlines)
    }

    inputFile.close();

    const char* inputStr = input.c_str();
    auto startTime = std::chrono::high_resolution_clock::now();

    size_t palindromeCount = countAllPalindromes(inputStr);

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);

    std::cout << "Total number of palindromes: " << palindromeCount << std::endl;
    std::cout << "Execution time: " << duration.count() << " microseconds" << std::endl;

    return 0;
}
