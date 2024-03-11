#include "request.h"

void Request::setRequestId(int requestId){
    this->requestId = requestId;
}

void Request::setTrackNumber(int trackNumber){
    this->trackNumber = trackNumber;
}

int Request::getRequestId(){
    return this->requestId;
}

int Request::getTrackNumber(){
    return this->trackNumber;
}
