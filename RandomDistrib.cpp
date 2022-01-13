
#include <vector>
#include <cmath>
#include <boost/tuple/tuple.hpp>
#include <chrono>
#include <random>
#include <vector>
#include <string>
#include <array>
#include <unordered_set>

#include "gnuplot-iostream.h"

int generateTimeout(){
    std::random_device rd; 
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<int> dist(150, 300);

    return std::chrono::milliseconds(dist(gen)).count();
}

#templace to calculate every possible size of array
int numberOfDuplicates(std::array<int, 5> arr){
    int cnt = 0;
    for(int i=0; i < 4; ++i){
        for(int j = 0; j < i; ++j){
            if (arr[i] == arr[j] && i != j){
                cnt++;
            }
        }
    }
    return cnt;
}

int main() {
	int cnt = 0;
    int timeout;
    std::vector<std::array<int, 5>> timeouts;
    // std::map<int, std::vector<std::pair<int, int>> duplicates;
    
    int machines = 10;
    while(cnt < 1000){
        std::array<int, machines+1> singleRun;
        for(auto machineNo = 0; machineNo < machines; ++machineNo){
            timeout = generateTimeout();
            singleRun[machineNo] = timeout;
        }
        singleRun[machines] = numberOfDuplicates(singleRun);
        timeouts.emplace_back(singleRun);

        cnt++;
    }

    int runNo = 1;
    int machineNo = 1;
    int totalDups = 0;
    for(auto& arr:timeouts){
        std::cout << "RUN NO: " << std::to_string(runNo++) << std::endl;
        for(auto time:arr){
            if(machineNo == 5){
                std::cout << " DUPLICATES: " << std::to_string(time);
                totalDups += time;
                continue;
            }
            std::cout << "MACHINE NO: " << std::to_string(machineNo++) << " TIMEOUT: " << std::to_string(time) << " ";
        }
        std::cout << std::endl;
        machineNo = 1;
    }

    std::cout << "Total Duplicates in " << std::to_string(runNo) << " runs: " << std::to_string(totalDups) << std::endl;
	
}