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
    file.close();
}

} // namespace vos
