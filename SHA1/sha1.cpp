#include <iostream>
#include <cstdint>
#include <vector>

unsigned int left_rol(unsigned int value, size_t bits){
    return (value << bits) | (value >> (32 - bits));
}

std::string SHA1(const std::string& vec){
    std::vector<uint8_t> message(vec.begin(), vec.end());
    
    uint64_t imessage = message.size() * 8;

    message.push_back(0x80);

    while ((message.size() * 8) % 512 != 448){
        message.push_back(0x00);
    }
    
    for (int i = 7; i >= 0; --i){
        message.push_back((imessage >> (i * 8)) & 0xFF);
    }

    std::vector<uint32_t> H = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0};
    std::vector<uint32_t> W(80);
    std::vector<uint32_t> M(16); 
    
    unsigned int K;
    unsigned int t;
    unsigned int f;
    
    for (uint64_t n = 0; n*64 < message.size(); n++){ 
		
    for (int i = 0; i < 16; i++) {
        M[i] = (message[n * 64 + 4 * i] << 24) | (message[n * 64 + 4 * i + 1] << 16) | (message[n * 64 + 4 * i + 2] << 8) | message[n * 64 + 4 * i + 3];
    }
 
    for (int i = 0; i < 16; i++){  
        W[i] = M[i];  
    } 
    for (t = 16; t < 80; t++){
	    W[t] = left_rol(W[t - 3] ^ W[t - 8] ^ W[t - 14] ^ W[t - 16], 1);
    }

        unsigned int a = H[0];
        unsigned int b = H[1];
        unsigned int c = H[2];
        unsigned int d = H[3];
        unsigned int e = H[4];

        for (t = 0; t < 80; t++){
            if (t < 20) {
                K = 0x5a827999;
                f = (b & c) | ((~b) & d); 
            } else if (t < 40){
                K = 0x6ed9eba1;
                f = b ^ c ^ d;   
            } else if (t < 60){
                K = 0x8f1bbcdc;
                f = (b & c) | (b & d) | (c & d); 
            } else{
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
        H[0] += a;
        H[1] += b;
        H[2] += c;
        H[3] += d;
        H[4] += e;
    }

    char all[41];  
    std::sprintf(all, "%08x%08x%08x%08x%08x", H[0], H[1], H[2], H[3], H[4]);
	
    return std::string(all);
}

int main(){
    std::string message = "'' '";
    std::string Hash = SHA1(message);

    std::cout << "SHA-1 hash: " << Hash << "\n";

    return 0;
}
