#include "../inc/enc_trans_cipher.hpp"
#include <map>
#include <algorithm>
#include <vector>
#include <numeric>

namespace enc
{

Trans_Cipher::Trans_Cipher(std::string const& key)
:m_key{key}
{

}
Trans_Cipher::Trans_Cipher(char* const& key)
:m_key{key}
{
    
}
static std::vector<int> getAlphabetIndexes(std::string const& str) 
{
    std::vector<int> indexes;
    
    for (char ch : str) {
        char upperCh = std::toupper(ch);
        int index = upperCh - 'A' + 1;
        indexes.push_back(index);
    }
    
    return indexes;
}

std::vector<int> getSmallestIndices(const std::vector<int>& arr) 
{
    std::vector<int> indices(arr.size());
    std::iota(indices.begin(), indices.end(), 0);

    std::sort(indices.begin(), indices.end(), [&arr](int i, int j) 
    {
        return arr[i] < arr[j];
    });

    return indices;
}

static std::string cipher_enc(std::string str, std::string key)
{
    std::string str_cut; 
    for (char c : str) 
    {
        if (!std::isspace(static_cast<unsigned char>(c))) 
        {
            str_cut += c;
        }
    }
    

    int len = str_cut.length();
    size_t n = key.length();
    size_t m = std::ceil(len / n);
    std::string transformedText;

    std::vector<std::vector<char>> matrix(n, std::vector<char>(m));
    std::vector<int> order = getAlphabetIndexes(key);
    std::vector<int> positions = getSmallestIndices(order);

    int index = 0;
    for (size_t col = 0; col < m; col++) 
    {
        for (size_t row = 0; row < n; row++)
        {
            if(index >= len)
            {
                matrix[row][col] = 'X';
                index++;
            }
            else
            {
                matrix[row][col] = str_cut[index++];
            }
        }
    }

    for (int row : positions) 
    {
        for (size_t col = 0; col < m; col++) 
        {
            transformedText += matrix[row][col];
        }
    }

    return transformedText;
}

void Trans_Cipher::encrypt(Message const& m_original, Message& m_encrypted)
{
    const std::string& text = m_original.getText();
    
    std::string transformedText = text;
    transformedText = cipher_enc(transformedText, m_key);

    m_encrypted.setText(transformedText);
}

}//namespace enc