#include "../inc/precious_stone.hpp"

namespace ENC
{

class Vowels: public Encryption 
{
public:
    ~Vowels() = default;
    Message* encrypt(Message const&) override;
};


}//namespace ENC