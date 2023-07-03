#include "../inc/precious_stone.hpp"

namespace ENC
{
class Scytale: public Encryption 
{
public:
    ~Scytale() = default;
    Message* encrypt(Message const&) override;
};


}//namespace ENC