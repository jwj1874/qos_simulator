#ifndef GATEWAY_H
#define GATEWAY_H

#include "Channel.h"

class Gateway{
private:
    int received_count;
    int dropped_count;

public:
    Gateway();

    void processTimeSlot(int time, const Channel& channel);
    void printStatistics() const;

    int getReceivedCount() const;
    int getDroppedCount() const;
};

#endif
