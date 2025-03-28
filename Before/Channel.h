#ifndef CHANNEL_H
#define CHANNEL_H

#include <unordered_map>
#include <vector>

class Channel{
private:
    std::unordered_map<int, std::vector<int>> transmissions;

public:
    void recordTransmission(int time, int node_id);
    bool isCollision(int time) const;
    std::vector<int> getTransmissionsAt(int time) const;
    void clearTimeSlot(int time);
};


#endif