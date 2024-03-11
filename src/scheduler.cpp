#include "scheduler.h"

Scheduler::Scheduler(int cylinderCount, int sectorCount, float bytesPerSecond, float rpm, float avgSeekTime, int initialHeadPosition, std::vector<Request> &requests, SchedulingType schedulingType){

		this->cylinderCount = cylinderCount;
		this->sectorCount = sectorCount;
		this->bytesPerSecond = bytesPerSecond;
		this->rpm = rpm;
		this->avgSeekTime = avgSeekTime;
		this->initialHeadPosition = initialHeadPosition;
		this->requests = requests;
		this->schedulingType = schedulingType;

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
	return this->avgSeekTime;
}

void Scheduler::fcfsScheduling(){

}

void Scheduler::lookScheduling(){

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
