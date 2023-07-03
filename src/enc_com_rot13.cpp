#include "../inc/enc_com_rot13.hpp"

namespace enc
{

Rot13_comp ::Rot13_comp ()
:caesar(new Caesar(13))
{
}

void Rot13_comp ::encrypt(Message const& m_original, Message& m_encrypted) 
{
    caesar->encrypt(m_original, m_encrypted);
}

}//namespace enc