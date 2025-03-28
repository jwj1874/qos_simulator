#include "Gateway.h"
#include <iostream>
using namespace std;
Gateway::Gateway() : received_count(0), dropped_count(0){}

void Gateway::processTimeSlot(int time, const Channel& channel){
    const auto& nodes = channel.getTransmissionsAt(time);

    if (nodes.size() == 1){
        ++received_count;
        cout << "[Gateway] Time " << time << ":Received data from Node " << nodes[0] << "\n";
    }
    else if (nodes.size() > 1){
        ++dropped_count;
        cout << "[Gateway] Time " << time << ": Collision detected between " << nodes.size() << " nodes.\n";
    }
}

void Gateway::printStatistics() const{
    cout << "\n=== Gateway Statistics ===\n";
    cout << "Received packets : " << received_count << "\n";
    cout << "Dropped packets <collisions) : " << dropped_count << "\n";
    cout << "===============================\n";
}

int Gateway::getReceivedCount() const{
    return received_count;
}

int Gateway::getDroppedCount() const{
    return dropped_count;
}
