#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <chrono>

using namespace std;

#include <openssl/sha.h>
string sha256(const string str)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);
    stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}

int main() {
    while(1){
    	int numL = 1, numR = 500000;
        int numAns = 1;
        while(numL <= numR){
            int numMid = (numL + numR)>>1;

            auto startTime = std::chrono::high_resolution_clock::now();
            for(int i = 1; i <= numMid; ++i)
                string ans = sha256("1234567890_1234567890");
            auto endTime = std::chrono::high_resolution_clock::now();

            unsigned int TotalTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
            if(TotalTime <= 1000){
                numAns = numMid;
                numL = numMid + 1;
            } else {
                numR = numMid - 1;
            }
        }
        cout << numAns << endl;
    }
    return 0;
}