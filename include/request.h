#ifndef REQUEST_H
#define REQUEST_H

class Request{
	private:
		int requestId;
		int trackNumber;

	public:
		/************************************************************
		 * @brief Sets Request Id of the disk request
		 * 
		 * @param requestId The id of the request
		*************************************************************/
		void setRequestId(int requestId);

		/************************************************************
		 * @brief Sets Track Number of the disk request
		 * 
		 * @param trackNumber The track number of the request
		*************************************************************/
		void setTrackNumber(int trackNumber);

		/************************************************************
		 * @brief Fetches Request Id of the disk request
		 * 
		 * @return ID of the request
		 ************************************************************/
		int getRequestId();

		/************************************************************
		 * @brief Fetches Track Number of the disk request
		 * 
		 * @return The track number of the request
		*************************************************************/
		int getTrackNumber();
};

#endif
