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

