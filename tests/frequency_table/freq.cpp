#include <iostream>
#include "../../inc/frequency_table.hpp"

int main(int argc, char** argv) 
{
    if (argc < 2)
    {
        std::cout << "invalid input\n";
        return 1;
    }

    std::string text;
    std::string line;
    int n = std::stoi(argv[1]);

    while (std::getline(std::cin, line)) 
    {
        text += line + '\n';
    }

    ds::WordCounter wordCounter;
    std::vector<std::pair<std::string, int>> wordCount = wordCounter.word_frequency_vector(text);
    wordCounter.print_frequency_list(wordCount, n);

    return 0;
}
