#ifndef SENSOR_NODE_H
#define SENSOR_NODE_H

#include <vector>

class SensorNode{
private:
    int id;
    int tx_interval;
    int next_tx_time;
    std::vector<float> data; //센서가 보유한 시계열 데이터
    float last_value;
public:
    SensorNode(int id, int interval, int offset = 0);
    int getId() const;
    int getNextTxTime() const;
    bool isTimeToTransmit(int current_time) const;
    void updateNextTxTime();
    float generateData();
    float getDataAt(int index) const;
};



#endif