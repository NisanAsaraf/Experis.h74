#ifndef VAULT_OF_SECRETS_
#define VAULT_OF_SECRETS_
#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>
#include <optional>

namespace vos
{
class Vault 
{
public:
    Vault(Vault const&) = delete;
    Vault(Vault&) = delete;
    Vault& operator=(Vault const&) = delete;

    std::string get(std::string const& key);
    void add(std::string const& key, std::string const& value);
    friend std::ostream& operator<<(std::ostream& os, const Vault& vault);
    void save();
private:
    Vault() = default;
    void load();
public:
    static Vault& open(std::string const&);
private:
    std::string m_master_key = "LIGMA";
    std::unordered_map<std::string, std::string> m_map;
};


class InvalidPasswordException : public std::exception
{
public:
    const char* what() const noexcept override
    {
        return "Invalid password";
    }
};


}//namespace vos
#endif