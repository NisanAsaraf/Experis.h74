#include "../inc/precious_stone.hpp"

namespace ENC
{
class Leet: public Encryption 
{
public:
    Message* encrypt(Message const&) override;
};


}//namespace ENC