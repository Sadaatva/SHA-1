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
	    
	unsigned int a = H0;
        unsigned int b = H1;
        unsigned int c = H2;
        unsigned int d = H3;
        unsigned int e = H4;

        for (t = 0; t < 80; t++){
            if (t == 0 || t < 20){
                K = 0x5a827999;
                f = (b & c) | ((~b) & d);
            } else if (t < 40){
                K = 0x6ed9eba1;
                f = b ^ c ^ d;
            } else if (t < 60){
                K = 0x8f1bbcdc;
                f = (b & c) | (b & d) | (c & d);
            } else {
                K = 0xca62c1d6;
                f = b ^ c ^ d;
            }

            unsigned int temp = left_rol(a, 5) + f + e + W[t] + K;
            e = d;
            d = c;
            c = left_rol(b, 30);
            b = a;
            a = temp;
        }
        H0 += a;
        H1 += b;
        H2 += c;
        H3 += d;
        H4 += e;
    }

    char all[41];  
    std::sprintf(all, "%08x%08x%08x%08x%08x", H0, H1, H2, H3, H4);
	
    return std::string(all);
}

int main() {
    std::string message = "abcd";
    std::string Hash = SHA1(message);

    std::cout << "SHA-1 hash: " << Hash << "\n";

    return 0;
}
