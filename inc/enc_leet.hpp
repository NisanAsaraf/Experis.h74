#include "../inc/precious_stone.hpp"

namespace ENC
{
class Leet: public Encryption 
{
public:
    ~Leet() = default;
    Message* encrypt(Message const&) override;
};


}//namespace ENC