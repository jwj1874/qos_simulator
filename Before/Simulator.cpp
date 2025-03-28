// #include "Simulator.h"
// #include <iostream>

// Simulator::Simulator() : current_time(0){
//     for(int i = 0; i < SENSOR_COUNT; i++){
//         sensors.emplace_back(i, SENSOR_TX_INTERVAL);
//     }
// }

// void Simulator::run(){
//     std::cout << "[Simulator] Running for " << SIM_DURATION << "secnods...\n";
    
//     for(current_time = 0; current_time < SIM_DURATION; current_time++){
//         for(auto&sensor : sensors){
//             if (sensor.isTimeToTransmit(current_time)){
//                 float value = sensor.generateData();
//                 sensor.updateNextTxTime();

//                 channel.recordTransmission(current_time, sensor.getId());

//                 logger.log(current_time, sensor.getId(), true, false, value);

//                 std::cout << "[Sensor " << sensor.getId() << "] Time " << current_time << ": Transmitting value " << value << "\n";
//             }
//         }
//         const auto& nodes = channel.getTransmissionsAt(current_time);
//         bool collision = nodes.size() > 1;
//         if (collision){
//             for(int node_id : nodes){
//                 logger.log(current_time, node_id, true, true, 0.0f);
//             }
//         }

//         gateway.processTimeSlot(current_time, channel);
//         channel.clearTimeSlot(current_time);
//     }
//     gateway.printStatistics();

//     logger.saveCSV("result.csv");
// }

// #include "Simulator.h"
// #include "AR_channel.h"
// #include <vector>
// #include <complex>
// #include <iostream>
// #include <unordered_map>

// std::vector<std::complex<double>> channel_response;

// Simulator::Simulator() : current_time(0){
//     for(int i = 0; i < SENSOR_COUNT; i++){
//         sensors.emplace_back(i, SENSOR_TX_INTERVAL);
//     }
// }

// void Simulator::run(){
//     std::cout << "[Simulator] Running for " << SIM_DURATION << " seconds...\n";

//     for(current_time = 0; current_time < SIM_DURATION; current_time++){
//         std::unordered_map<int, float> value_map;  

//         // 1. 전송 시도만 먼저 수행
//         for(auto& sensor : sensors){
//             if (sensor.isTimeToTransmit(current_time)){
//                 float value = sensor.generateData();
//                 sensor.updateNextTxTime();  //

//                 channel.recordTransmission(current_time, sensor.getId());
//                 value_map[sensor.getId()] = value;

//                 std::cout << "[Sensor " << sensor.getId()
//                           << "] Time " << current_time
//                           << ": Transmitting value : " << value << "\n";
//             }
//         }

//         // 2. 충돌 판단 후 log 기록
//         const auto& nodes = channel.getTransmissionsAt(current_time);
//         bool collision = nodes.size() > 1;

//         for (int node_id : nodes) {
//             float value = value_map.count(node_id) ? value_map[node_id] : 0.0f;
//             logger.log(current_time, node_id, true, collision, value);
//         }

//         gateway.processTimeSlot(current_time, channel);
//         channel.clearTimeSlot(current_time);
//     }

//     gateway.printStatistics();
//     logger.saveCSV("result.csv");
// }

#include "Simulator.h"
#include "AR_channel.h"
#include <iostream>
#include <unordered_map>
#include <cmath>  // for std::abs

#define THRESHOLD 0.5  // 채널 임계값

Simulator::Simulator() : current_time(0) {
    for (int i = 0; i < SENSOR_COUNT; i++) {
        int offset = rand() % SENSOR_TX_INTERVAL;
        sensors.emplace_back(i, SENSOR_TX_INTERVAL, offset);
    }

    // AR 채널 생성
    AR_Channel ar_channel;
    this->channel_response = ar_channel.generateChannel();
}

void Simulator::run() {
    std::cout << "[Simulator] Running for " << SIM_DURATION << " seconds...\n";

    for (current_time = 0; current_time < SIM_DURATION; current_time++) {
        std::unordered_map<int, float> value_map;

        // 1. 센서 전송 시도
        for (auto& sensor : sensors) {
            if (sensor.isTimeToTransmit(current_time)) {
                float value = sensor.generateData();
                sensor.updateNextTxTime();

                // 채널 응답 가져오기
                double h = std::abs(this->channel_response[current_time % this->channel_response.size()]);
                double signal_strength = value * h;
                bool valid = signal_strength >= THRESHOLD;

                if (valid) {
                    channel.recordTransmission(current_time, sensor.getId());
                    value_map[sensor.getId()] = value;
                }

                std::cout << "[Sensor " << sensor.getId()
                          << "] Time " << current_time
                          << ": Value = " << value
                          << ", |h(t)| = " << h
                          << ", Valid = " << (valid ? "YES" : "NO") << "\n";

                // 로그: 전송 실패도 기록
                logger.log(current_time, sensor.getId(), true, false, valid ? value : 0.0f, h);
            }
        }

        // 2. 충돌 판단 및 로그 기록 (유효 전송만 대상)
        const auto& nodes = channel.getTransmissionsAt(current_time);
        bool collision = nodes.size() > 1;

        for (int node_id : nodes) {
            float value = value_map.count(node_id) ? value_map[node_id] : 0.0f;
            double h = std::abs(this->channel_response[current_time % this->channel_response.size()]);
            logger.log(current_time, node_id, true, collision, value, h);
        }

        gateway.processTimeSlot(current_time, channel);
        channel.clearTimeSlot(current_time);
    }

    gateway.printStatistics();
    logger.saveCSV("result.csv");
}
