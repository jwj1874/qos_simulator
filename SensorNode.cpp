#include "SensorNode.h"
#include <cmath>

SensorNode::SensorNode(int id, int interval, int offset) 
: id(id), tx_interval(interval), next_tx_time(offset), last_value(20.0f){
    data.reserve(1000);
}

int SensorNode::getId() const{
    return id;
}

int SensorNode::getNextTxTime() const{
    return next_tx_time;
}

bool SensorNode::isTimeToTransmit(int current_time)const{
    return current_time >= next_tx_time;
}

void SensorNode::updateNextTxTime(){
    next_tx_time += tx_interval;
}

float SensorNode::generateData(){
    float delta = ((rand() % 60) - 30) / 100.0f;
    last_value += delta;
    data.push_back(last_value);
    return last_value;
}

float SensorNode::getDataAt(int index) const{
    return (static_cast<size_t>(index) < data.size()) ? data[index] : 0.0f;
}

