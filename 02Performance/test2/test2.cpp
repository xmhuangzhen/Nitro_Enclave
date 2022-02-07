#include <iostream>
#include <chrono>

using namespace std;

int main(){
    while(1){
        auto startTime = std::chrono::high_resolution_clock::now();
        int ans = 0;
        for(int k = 0; k < 100000; ++k)
            for(int j = 0; j < 100000; ++j)
                ans++;
        auto endTime = std::chrono::high_resolution_clock::now();
        unsigned int totalTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
        std::cout << totalTime<<endl;
    }
    return 0;
}
