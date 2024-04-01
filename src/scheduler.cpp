#include "scheduler.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <climits>

Scheduler::Scheduler(int cylinderCount, int sectorCount, float bytesPerSecond, float rpm, float avgSeekTime, int initialHeadPosition, std::vector<Request> requests, SchedulingType schedulingType){

		this->cylinderCount = cylinderCount;
		this->sectorCount = sectorCount;
		this->bytesPerSecond = bytesPerSecond;
		this->rpm = rpm;
		this->avgSeekTime = avgSeekTime;
		this->initialHeadPosition = initialHeadPosition;
		this->requests = requests;
		this->schedulingType = schedulingType;
		this->avgRotationalDelay = 0;
		this->totalSeekTime = 0;
}

void Scheduler::setAvgRotationalDelay(float avgRotationalDelay){
	this->avgRotationalDelay = avgRotationalDelay;
}

void Scheduler::setTotalSeekTime(float totalSeekTime){
	this->totalSeekTime = totalSeekTime;
}

float Scheduler::getTotalSeekTime(){
	return this->totalSeekTime;
}

float Scheduler::getAvgRotationalDelay(){
	return this->avgRotationalDelay;
}

void Scheduler::fcfsScheduling(){
	int currTrack = initialHeadPosition;
	seekSequence.push_back(initialHeadPosition);
	float total = 0;
	for(auto request: requests){
		total +=  std::abs(currTrack - request.getTrackNumber());
		seekSequence.push_back(request.getTrackNumber());
		currTrack = request.getTrackNumber();
	}

	float delay = (1.0f / (2.0f * rpm)) * 60.0f;

	setAvgRotationalDelay(delay);
	setTotalSeekTime(total);
}

void Scheduler::lookScheduling(){
	int currTrack = initialHeadPosition;
	seekSequence.push_back(initialHeadPosition);
	float total = 0;

	std::string direction = "right";

	std::vector<int> left, right;

	float delay = (1.0f / (2.0f * rpm)) * 60.0f;

	for(auto request: requests){
		int trackNumber = request.getTrackNumber();
		if(trackNumber < initialHeadPosition)
			left.push_back(trackNumber);

		if(trackNumber > initialHeadPosition)
			right.push_back(trackNumber);

	}

	std::sort(left.begin(), left.end());
	std::sort(right.begin(), right.end());

	int runs = 2;
	while(runs > 0){
		if(direction == "left"){
			for(int i = left.size()-1; i>-1; i--){
				total += std::abs(left[i] - currTrack);
				seekSequence.push_back(left[i]);
				currTrack = left[i];
			}

			direction = "right";
		}
		else if(direction == "right"){
			for(int i = 0; i<right.size(); i++){
				total += std::abs(right[i] - currTrack);
				seekSequence.push_back(right[i]);
				currTrack = right[i];
			}

			direction = "left";
		}
		runs--;
	}

	setAvgRotationalDelay(delay);
	setTotalSeekTime(total);
}

void Scheduler::cLookScheduling(){
	int currTrack = initialHeadPosition;
	seekSequence.push_back(initialHeadPosition);
	float total = 0;

	std::string direction = "right";

	std::vector<int> left, right;

	float delay = (1.0f / (2.0f * rpm)) * 60.0f;

	for(auto request: requests){
		int trackNumber = request.getTrackNumber();
		if(trackNumber < initialHeadPosition)
			left.push_back(trackNumber);

		if(trackNumber > initialHeadPosition)
			right.push_back(trackNumber);

	}

	std::sort(left.begin(), left.end());
	std::sort(right.begin(), right.end());

	int runs = 2;
	while(runs > 0){
		if(direction == "left"){
			for(int i = 0; i<left.size(); i++){
				total += std::abs(left[i] - currTrack);
				seekSequence.push_back(left[i]);
				currTrack = left[i];
			}

			direction = "right";
		}
		else if(direction == "right"){
			for(int i = 0; i<right.size(); i++){
				total += std::abs(right[i] - currTrack);
				seekSequence.push_back(right[i]);
				currTrack = right[i];
			}

			direction = "left";
		}
		runs--;
	}

	setAvgRotationalDelay(delay);
	setTotalSeekTime(total);
}

void Scheduler::scanScheduling(){
	int currTrack = initialHeadPosition;
	seekSequence.push_back(initialHeadPosition);
	float total = 0;

	std::string direction = "right";

	std::vector<int> left, right;

	float delay = (1.0f / (2.0f * rpm)) * 60.0f;

	for(auto request: requests){
		int trackNumber = request.getTrackNumber();
		if(trackNumber < initialHeadPosition)
			left.push_back(trackNumber);

		if(trackNumber > initialHeadPosition)
			right.push_back(trackNumber);

	}

	std::sort(left.begin(), left.end());
	std::sort(right.begin(), right.end());

	int runs = 2;
	while(runs > 0){
		if(direction == "left"){
			for(int i = 0; i<left.size(); i++){
				total += std::abs(left[i] - currTrack);
				seekSequence.push_back(left[i]);
				currTrack = left[i];
			}

			direction = "right";
		}
		else if(direction == "right"){
			for(int i = 0; i<right.size(); i++){
				total += std::abs(right[i] - currTrack);
				seekSequence.push_back(right[i]);
				currTrack = right[i];
			}
			total += std::abs(currTrack - cylinderCount);
			seekSequence.push_back(cylinderCount-1);
			currTrack = cylinderCount - 1;
			direction = "left";
		}
		runs--;
	}

	setAvgRotationalDelay(delay);
	setTotalSeekTime(total);
}

void Scheduler::cScanScheduling(){
    int currTrack = initialHeadPosition;
	seekSequence.push_back(initialHeadPosition);
	float total = 0;

	std::string direction = "right";

	std::vector<int> left, right;

	float delay = (1.0f / (2.0f * rpm)) * 60.0f;

	for(auto request: requests){
		int trackNumber = request.getTrackNumber();
		if(trackNumber < initialHeadPosition)
			left.push_back(trackNumber);

		if(trackNumber > initialHeadPosition)
			right.push_back(trackNumber);

	}

	std::sort(left.begin(), left.end());
	std::sort(right.begin(), right.end());

	int runs = 2;
	while(runs > 0){
		if(direction == "left"){
			for(int i = 0; i<left.size(); i++){
				total += std::abs(left[i] - currTrack);
				seekSequence.push_back(left[i]);
				currTrack = left[i];
			}

			direction = "right";
		}
		else if(direction == "right"){
			for(int i = 0; i<right.size(); i++){
				total += std::abs(right[i] - currTrack);
				seekSequence.push_back(right[i]);
				currTrack = right[i];
			}
			total += std::abs(currTrack - cylinderCount);
			seekSequence.push_back(cylinderCount-1);
			currTrack = cylinderCount - 1;
            total += std::abs(currTrack - 0);
            seekSequence.push_back(0);
			currTrack = 0;
			direction = "left";
		}
		runs--;
	}

	setAvgRotationalDelay(delay);
	setTotalSeekTime(total);
}

int findNextTrack(int currTrack, std::vector<Request> &requests, std::vector<bool> &served){
    int minAbsoluteDiff = INT_MAX;
    
    int nextTrack, nextTrackId;

    for(auto request: requests){
        int requestedTrack = request.getTrackNumber();
        int requestedTrackId = request.getRequestId();

        int diff = std::abs(currTrack - requestedTrack);
        if(diff < minAbsoluteDiff && !served[requestedTrackId]){
            minAbsoluteDiff = diff;
            nextTrack = requestedTrack;
            nextTrackId = requestedTrackId;
        }
    }

    if(minAbsoluteDiff == INT_MAX)
        return -1;

    served[nextTrackId] = true;
    return nextTrack;
}

void Scheduler::sstfScheduling(){
    std::vector<bool> served(requests.size(), false);
    
    int currTrack = initialHeadPosition;
    int nextTrack = findNextTrack(currTrack, requests, served);

    seekSequence.push_back(currTrack);
    int total = 0;
    while(nextTrack != -1){
        total += std::abs(currTrack - nextTrack);
        seekSequence.push_back(nextTrack);
        currTrack = nextTrack;
         nextTrack = findNextTrack(currTrack, requests, served);
    }
    float delay = (1.0f / (2.0f * rpm)) * 60.0f;
    setTotalSeekTime(total);
    setAvgRotationalDelay(delay);
}

void Scheduler::schedule(){

	switch (this->schedulingType){

		case FCFS:
			this->fcfsScheduling();
			break;

		case LOOK:
			this->lookScheduling();
			break;

		case C_LOOK:
			this->cLookScheduling();
			break;

		case SCAN:
			this->scanScheduling();
			break;
		
        case C_SCAN:
			this->cScanScheduling();
			break;

        case SSTF:
            this->sstfScheduling();
            break;
		
	}

}

void Scheduler::results(){
	switch (this->schedulingType){

		case FCFS:
			std::cout<<"\n\nFCFS Scheduling Results: \n\n";
			break;

		case LOOK:
			std::cout<<"\n\nLOOK Scheduling Results: \n\n";
			break;

		case C_LOOK:
			std::cout<<"\n\nC-LOOK Scheduling Results: \n\n";
			break;

		case SCAN:
			std::cout<<"\n\nSCAN Scheduling Results: \n\n";
			break;
		
        case C_SCAN:
			std::cout<<"\n\nC-SCAN Scheduling Results: \n\n";
			break;
        
        case SSTF:
			std::cout<<"\n\nSSTF Scheduling Results: \n\n";
			break;
		
	}
	std::cout<<"Seek Sequence : ";
	for(auto seek: seekSequence){
		std::cout<<seek<<" ";
	}
	std::cout<<"\n";
	std::cout<<"Average Rotational Delay : "<<this->getAvgRotationalDelay()<<" seconds"<<std::endl;
	std::cout<<"Total Seek Time : "<<this->getTotalSeekTime()<<" seconds"<<std::endl;
}
