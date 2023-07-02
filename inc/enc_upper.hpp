#include "../inc/precious_stone.hpp"

namespace ENC
{

class UpperCase : public Encryption 
{
public:
    Message* encrypt(Message const&) override;
};

}//namespace ENC