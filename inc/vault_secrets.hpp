#ifndef VAULT_OF_SECRETS_
#define VAULT_OF_SECRETS_
#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>
#include <optional>

namespace vos
{
template <typename Secret>
class Vault 
{
public:
    Vault(Vault const&) = delete;
    Vault& operator=(Vault const&) = delete;
    std::string const& get(std::string const& key) const;
    void add(std::string const& key, Secret const& value);
    
    template<typename T>
    friend std::ostream& operator<<(std::ostream& os, const Vault<T>& vault);

    void save();
private:
    Vault() = default;
    ~Vault() = default;
    void load();
public:
    static Vault& open(std::string const&);
private:
    std::string m_master_key = "psi";
    std::unordered_map<std::string, Secret> m_map;
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