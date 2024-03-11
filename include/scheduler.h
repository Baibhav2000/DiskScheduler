#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "request.h"
#include <vector>

typedef enum SchedulingType{
	FCFS,
	LOOK,
	C_LOOK,
	SCAN
}SchedulingType;

class Scheduler{
	private:

		int cylinderCount;						//  Number of available cylinders in the disk
		int sectorCount;						//  Number of sectors per track
		float bytesPerSecond;					//  Rate at which data is read/written from/to a disk (in Bytes)
		float rpm;								// 	Number  of revolutions per minute that the head moves across a disk
		float avgSeekTime;						//  Average time taken to move the head to a track
		int initialHeadPosition;				//  Initial position of the disk's head at the start
		std::vector<Request> requests;			//  Queue containing all requests made by users
		SchedulingType schedulingType;			//  Type of Disk scheduling algorithm used
		float avgRotationalDelay;				//  Average rotational delay of the algorithm
		float totalSeekTime;					//	Total seek time spent so far

		/****************************************************************************************
		 * @brief Performs FCFS Disk Scheduling
		*****************************************************************************************/
		void fcfsScheduling();

		/****************************************************************************************
		 * @brief Performs Look Disk Scheduling
		*****************************************************************************************/
		void lookScheduling();

		/****************************************************************************************
		 * @brief Performs C-Look Disk Scheduling
		*****************************************************************************************/
		void cLookScheduling();

		/****************************************************************************************
		 * @brief Performs Scan DiskScheduling
		*****************************************************************************************/
		void scanScheduling();
	
	public:

		/*****************************************************************************************
		 * @brief Construct a new Scheduler object
		 * 
		 * @param[in]   cylinderCount The number of cylinders in a disk
		 * @param[in]   sectorCount The number of sectors in a disk
		 * @param[in]   bytesPerSecond The speed at which the disk can read/write
		 * @param[in]   rpm The number of revolutions of a disk per minute
		 * @param[in]	avgSeekTime The time taken to seek a track
		 * @param[in]	initialHeadPosition The starting position of the disk head
		 * @param[inout] requests Queue of disk requests	
		 * @param[in]	schedulingType Type of Disk scheduling algorithm used
		******************************************************************************************/
		Scheduler(int cylinderCount, int sectorCount, float bytesPerSecond, float rpm, float avgSeekTime, int initialHeadPosition, std::vector<Request> &requests, SchedulingType schedulingType);

		
		/***********************************************************
		 * @brief Schedules Disk Requests
		************************************************************/
		void schedule();

		/***************************************************************
		 * @brief Displays results
		 ***************************************************************/
		void results();

		/***********************************************************************
		 * @brief Sets Avg. rotational delay of the algorithm
		 * 
		 * @param[in] avgRotationalDelay Avg. rotational delay of the algorithm
		************************************************************************/
		void setAvgRotationalDelay(float avgRotationalDelay);

		/***********************************************************************
		 * @brief Sets total seek time of the algorithm
		 * 
		 * @param[in] totalSeekTime total seek time of the algorithm
		************************************************************************/
		void setTotalSeekTime(float totalSeekTime);

		/***********************************************************************
		 * @brief Fetches Avg. rotational delay  of the algorithm
		 * 
		 * @return Avg. Rotational Delay of the algorithm
		************************************************************************/
		float getAvgRotationalDelay();

		/***********************************************************************
		 * @brief Fetches total seek time of the algorithm
		 * 
		 * @return total seek time of the algorithm
		************************************************************************/
		float getTotalSeekTime();


};

#endif
