#include <iostream>
#include <cstring>
#include <fstream>
#include <omp.h>

size_t countPalindromesFromCenter(const char* str, size_t n, size_t left, size_t right) {
    size_t count = 0;
    // Expand outwards as long as we are within bounds and characters match
    while (left < n && right < n && str[left] == str[right]) {
        count++;
        if (left == 0) break;
        left--;
        right++;
    }
    return count;
}

size_t countAllPalindromes(const char* str, size_t n, int numThreads) {
    if (!str) return 0;
    size_t totalCount = 0;

    omp_set_num_threads(numThreads);

#pragma omp parallel for reduction(+:totalCount) schedule(dynamic, 100000)
for (size_t i = 0; i < n; ++i) {
    totalCount += countPalindromesFromCenter(str, n, i, i);  // Odd-length palindromes
    totalCount += countPalindromesFromCenter(str, n, i, i + 1);  // Even-length palindromes
}

return totalCount;
}

int main() {
    std::string filename = "war-and-peace";  

    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string input;
    std::string line;
    while (std::getline(inputFile, line)) {
        input += line;
    }
    inputFile.close();

    const char* inputStr = input.c_str();
    size_t inputLength = input.length();

    int numThreads;
    std::cout << "Number of used threads: ";
    std::cin >> numThreads;

    double startTime = omp_get_wtime();

    size_t palindromeCount = countAllPalindromes(inputStr, inputLength, numThreads);

    double endTime = omp_get_wtime();

    std::cout << "Total number of palindromes: " << palindromeCount << std::endl;
    std::cout << "Execution time: " << (endTime - startTime) * 1e6 << " microseconds" << std::endl;

    return 0;
}
