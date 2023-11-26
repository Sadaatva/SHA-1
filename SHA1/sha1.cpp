#include <iostream>

unsigned int left_rol(unsigned int value, size_t bits){
    return (value << bits) | (value >> (32 - bits));
}

std::string SHA1(const std::string& message){
	
    unsigned int H0 = 0x67452301;
    unsigned int H1 = 0xEFCDAB89;
    unsigned int H2 = 0x98BADCFE;
    unsigned int H3 = 0x10325476;
    unsigned int H4 = 0xC3D2E1F0;

    unsigned int K;
    unsigned int t;
    unsigned int f;
    unsigned int W[80];

    unsigned int message_length = message.length() * 8;
    
    std::string imessage = message + static_cast<char>(0x80);
    
    while((imessage.length() * 8) % 512 != 448){
        imessage += static_cast<char>(0x00);
    }
    
    imessage += std::string(reinterpret_cast<char*>(&message_length), sizeof(message_length));
