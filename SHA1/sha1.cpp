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

    for (size_t i = 0; i < imessage.length(); i += 64){
        const unsigned int* part = reinterpret_cast<const unsigned int*>(&imessage[i]);

        for (t = 0; t < 16; t++){
            W[t] = part[t];
        }
        for (t = 16; t < 80; t++){
            W[t] = left_rol(W[t - 3] ^ W[t - 8] ^ W[t - 14] ^ W[t - 16], 1);
        }
    }
