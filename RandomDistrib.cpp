
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

int numberOfDuplicates(std::vector<int> vec){
    int cnt = 0;
    for(int i=0; i < vec.size(); ++i){
        for(int j = 0; j < i; ++j){
            if (vec[i] == vec[j] && i != j){
                cnt++;
            }
        }
    }
    return cnt;
}

int main() {
	int cnt = 0;
    int timeout;
    std::vector<std::vector<int>> timeouts;
    // std::map<int, std::vector<std::pair<int, int>> duplicates;
    
    int machines = 10;
    while(cnt < 1000){
        std::vector<int> singleRun;
        for(auto machineNo = 0; machineNo < machines; ++machineNo){
            timeout = generateTimeout();
            singleRun.emplace_back(timeout);
        }
        singleRun.emplace_back(numberOfDuplicates(singleRun));
        timeouts.emplace_back(singleRun);

        cnt++;
    }

    int runNo = 1;
    int machineNo = 1;
    int totalDups = 0;
    for(auto& run:timeouts){
        std::cout << "=======" << std::endl;
        std::cout << "RUN NO: " << std::to_string(runNo++) << std::endl;
        for(auto val:run){
            if(machineNo == machines+1){
                std::cout << " DUPLICATES: " << std::to_string(val);
                totalDups += val;
                continue;
            }
            std::cout << "    MACHINE NO: " << std::to_string(machineNo++) << " TIMEOUT: " << std::to_string(val) << std::endl;
        }
        std::cout << std::endl;
        machineNo = 1;
    }

    std::cout << "Total Duplicates in " << std::to_string(runNo) << " runs: " << std::to_string(totalDups) << std::endl;
	
}