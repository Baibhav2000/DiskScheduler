#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "request.h"
#include "scheduler.h"

int main(){
    
    std::string inputFileName = "../data/input.txt";

    std::ifstream inputFile(inputFileName);

    if (!inputFile.is_open()) {
        std::cout << "Error opening file!" << std::endl;
        return 1;
    }

    int cylinderCount;
    int sectorCount;
    float bytesPerSecond;
    float rpm;
    float avgSeekTime;
    int initialHeadPosition;

    std::string trackRequests;

    inputFile >> cylinderCount >> sectorCount >> bytesPerSecond >> rpm >> avgSeekTime >> initialHeadPosition >> trackRequests;

    getline(inputFile, trackRequests);
    
    inputFile.close();

    std::vector<Request> requests;

    std::stringstream ss(trackRequests);
    std::string token;
    int count = 0;

    while (getline(ss, token, ',')) {
        Request req;
        req.setRequestId(count);
        req.setTrackNumber(stoi(token));
        requests.push_back(req);
        count++;
    }

    Scheduler fcfsScheduler = Scheduler(cylinderCount, sectorCount, bytesPerSecond, rpm, avgSeekTime, initialHeadPosition, requests, FCFS);
    fcfsScheduler.schedule();
    fcfsScheduler.results();

    

    return 0;
}
