#include "../inc/vault_secrets.hpp"

namespace vos
{

Vault& Vault::open(std::string const& master_key)
{
    static Vault instance(master_key);
    if(instance.m_map.empty())
    {
        instance.load();
    }
    return instance;
}

Vault::Vault(std::string const& master_key)
:m_master_key{master_key}
{
}


std::string Vault::get(std::string const& key)
{
    return m_map.at(key);
}

void Vault::add(std::string const& key, std::string const& value)
{
    m_map.insert({ key, value });
}  

std::ostream& operator<<(std::ostream& os, const Vault& vault)
{
    for (const auto& kvp : vault.m_map)
    {
        os << kvp.first << ": " << kvp.second << '\n';
    }
    return os;
}

void Vault::save()
{
    std::string filename = "vault_contents.txt";
    std::ofstream file(filename);

    for (const auto& kvp : m_map)
    {
        file << kvp.first << ":" << kvp.second << '\n';
    }
    file.close();
}

void Vault::load()
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
