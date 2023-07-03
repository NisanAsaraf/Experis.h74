#include "../inc/precious_stone.hpp"

namespace ENC
{
class Caesar: public Encryption 
{
public:
    ~Caesar() = default;
    Message* encrypt(Message const&) override;
};


}//namespace ENC