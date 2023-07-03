#include "../inc/precious_stone.hpp"

namespace ENC
{

class UpperCase : public Encryption 
{
public:
    ~UpperCase() = default;
    Message* encrypt(Message const&) override;
};

}//namespace ENC