#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <vector>
#include <complex>
#include "SensorNode.h"
#include "Channel.h"
#include "Gateway.h"
#include "Logger.h"
#include "Config.h"


class Simulator{
private:
    std::vector<SensorNode> sensors;
    Channel channel;
    Gateway gateway;
    Logger logger;
    int current_time;

    std::vector<std::complex<double>> channel_response;

public:
    Simulator();
    void run();
};

#endif