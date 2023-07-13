#include "../vault_secrets.hpp"

namespace vos
{

template<typename Secret>
Vault<Secret>& Vault<Secret>::open(std::string const& master_key)
{
    static Vault* instance = nullptr;

    if (!instance) 
    {
        instance = new Vault();
    }

    if (instance->m_master_key != master_key) 
    {
        throw InvalidPasswordException();
    }

    if(instance->m_map.empty())
    {
        instance->load();
    }
    
    return *instance;
}

template<typename Secret>
std::string const& Vault<Secret>::get(std::string const& key) const
{
    try 
    {
        return m_map.at(key);    
    }
    catch (const std::out_of_range& err) 
    {
        std::cerr << "Out of Range error: " << err.what() << '\n';
        throw; 
    }
}

template<typename Secret>
void Vault<Secret>::add(std::string const& key, Secret const& value)
{
    m_map.insert({ key, value });
}  

template<typename Secret>
std::ostream& operator<<(std::ostream& os, const Vault<Secret>& vault)
{
    for (const auto& kvp : vault.m_map)
    {
        os << kvp.first << ": " << kvp.second << '\n';
    }
    return os;
}

template<typename Secret>
void Vault<Secret>::save()
{
    std::string filename = "vault_contents.txt";
    std::ofstream file(filename);
    encrypt();
    for (const auto& kvp : m_map)
    {
        file << kvp.first << ":" << kvp.second << '\n';
    }
    file.close();
}

template<typename Secret>
void Vault<Secret>::load()
{
    std::string filename = "vault_contents.txt";
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line))
    {
        size_t delimiterPos = line.find(":");
        if (delimiterPos != std::string::npos)
        {
            std::string key = line.substr(0, delimiterPos);
            std::string value = line.substr(delimiterPos + 1);
            m_map[key] = value;
        }
    }

    decrypt();
    
    file.close();
}

char leet_enc(char c)
{   
     switch(c) 
     {
        case 'A': return '4';
        case 'a': return '@';
        case 'B': return '8';
        case 'c': return '(';
        case 'D': return ')';
        case 'e': return '3';
        case 'g': return '6';
        case 'G': return '&';
        case 'h': return '#';
        case 'i': return '1';
        case 'v': return '>';
        case 'V': return '<';
        case 'l': return '!';
        case 'o': return '0';
        case 's': return '5';
        case 'S': return '$';
        case 'T': return '7';
        case 'z': return '2';
        default: return c;
    }
}

char leet_dec(char c) 
{
    switch (c) 
    {
        case 4: return 'A';
        case '@': return 'a';
        case 8: return 'B';
        case '(': return 'c';
        case ')': return 'D';
        case 3: return 'e';
        case 6: return 'g';
        case '&': return 'G';
        case '#': return 'h';
        case 1: return 'i';
        case '>': return 'v';
        case '<': return 'V';
        case '!': return 'l';
        case 0: return 'o';
        case 5: return 's';
        case '$': return 'S';
        case 7: return 'T';
        case 2: return 'z';
        default: return c;
    }
}

template<typename Secret>
void encrypt_leet(Secret& a_secret)
{
    std::transform(a_secret.begin(), a_secret.end(), a_secret.begin(), &leet_enc);
}

template<typename Secret>
void decrypt_leet(Secret& a_secret)
{
    std::transform(a_secret.begin(), a_secret.end(), a_secret.begin(), &leet_dec);
}

template<typename Secret>
void Vault<Secret>::encrypt()
{
    for(auto& kvp : m_map)
    {
        encrypt_leet(kvp.second);
    }
}

template<typename Secret>
void Vault<Secret>::decrypt()
{
    for(auto& kvp : m_map)
    {
        decrypt_leet(kvp.second);
    }
}
    
} // namespace vos
