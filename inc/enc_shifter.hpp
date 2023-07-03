#ifndef _ENC_SHIFTER_
#define _ENC_SHIFTER_
#include "../inc/precious_stone.hpp"

namespace enc
{
class Shifter: public Encoder
{
public:
    Shifter(int n);
    ~Shifter() = default;
    void encrypt(Message const& m_original, Message& m_encrypted) override;
    char shift(char c);

protected:
    int shiftAmount;
};

} // namespace enc

#endif
