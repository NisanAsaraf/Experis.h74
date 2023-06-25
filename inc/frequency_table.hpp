#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <cmath>
#include <cstring>
#include <unordered_map>
namespace ds
{
class WordCounter 
{
public:
    std::vector<std::string> split_words(const std::string& text) 
    {
        std::vector<std::string> words;
        std::string single;

        for (char c : text) 
        {
            if (std::isalpha(c)) 
            {
                single += std::tolower(c);
            } else if (c == ' ' && !single.empty()) 
            {
                words.push_back(single);
                single.clear();
            }
        }

        if (!single.empty()) 
        {
            words.push_back(single);
        }

        return words;
    }

    static bool compare_by_frequency(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) 
    {
        return a.second > b.second;
    }

    std::vector<std::pair<std::string, int>> word_frequency_vector(const std::string& text) 
    {
        std::vector<std::string> words = split_words(text);

        std::unordered_map<std::string, int> wordCount;
        for (const std::string& word : words) 
        {
            wordCount[word]++;
        }

        std::vector<std::pair<std::string, int>> sortedWords(wordCount.begin(), wordCount.end());
        std::sort(sortedWords.begin(), sortedWords.end(), compare_by_frequency);

        return sortedWords;
    }


    void print_frequency_list(std::vector<std::pair<std::string, int>> sortedWords, int n)
    {
        int count = 0;
        for (const std::pair<std::string, int>& pair : sortedWords) 
        {
            std::cout << pair.first << ": " << pair.second << '\n';
            count++;
            if (count == n) 
            {
                break;
            }
        }
    }
};

}//namespace ds