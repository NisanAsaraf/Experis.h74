#include "../inc/precious_stone.hpp"

namespace ENC
{
class Caesar: public Encryption 
{
public:
    Message* encrypt(Message const&) override;
};


}//namespace ENC