#include "scheduler.h"
#include <iostream>
#include <cmath>
#include <algorithm>

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

}

void Scheduler::scanScheduling(){
	
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
		
	}
	std::cout<<"Seek Sequence : ";
	for(auto seek: seekSequence){
		std::cout<<seek<<" ";
	}
	std::cout<<"\n";
	std::cout<<"Average Rotational Delay : "<<this->getAvgRotationalDelay()<<" seconds"<<std::endl;
	std::cout<<"Total Seek Time : "<<this->getTotalSeekTime()<<" seconds"<<std::endl;
}
