#include "Channel.h"

void Channel::recordTransmission(int time, int node_id){
    transmissions[time].push_back(node_id);
}

bool Channel::isCollision(int time) const{
    auto it = transmissions.find(time);
    if (it != transmissions.end()){
        return it->second.size() > 1;
    }
    return false;
}

std::vector<int> Channel::getTransmissionsAt(int time) const{
    auto it = transmissions.find(time);
    if (it != transmissions.end()){
        return it->second;
    }
    return {};
}

void Channel::clearTimeSlot(int time){
    transmissions.erase(time);
}