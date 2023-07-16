#ifndef VAULT_OF_SECRETS_
#define VAULT_OF_SECRETS_
#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>
#include <optional>
#include <algorithm>
#include <vector>

namespace vos
{
template <typename T>
class Singleton 
{
public:
    Singleton(Singleton const&) = delete;
    static T& get_instance();
    ~Singleton();

protected:
    Singleton() = default;

private:
    static T* self_pointer;
};

template <typename Secret>
class Vault : Singleton<Vault<Secret>>
{

public:
    Vault(Vault const&) = delete;
    Vault& operator=(Vault const&) = delete;

    Secret const& get(std::string const& key) const;
    void add(std::string const& key, Secret const& value);

    template<typename T>
    friend std::ostream& operator<<(std::ostream& os, const Vault<T>& vault);

    void save();
    friend class Singleton<Vault<Secret>>;

private:
    Vault() = default;
    ~Vault() = default;
    void load();

    void encrypt();
    void decrypt();

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