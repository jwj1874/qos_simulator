#include "Logger.h"
#include <fstream>

void Logger::log(int time, int node_id, bool transmitted, bool collision, float value, float channel_gain) {
    entries.push_back({time, node_id, transmitted, collision, value, channel_gain});
}

void Logger::saveCSV(const std::string& filename) const {
    std::ofstream fout(filename);
    fout << "time,node_id,transmitted,collision,value,channel_gain\n";
    for (const auto& e : entries) {
        fout << e.time << "," << e.node_id << ","
             << e.transmitted << "," << e.collision << ","
             << e.value << "," << e.channel_gain << "\n";
    }
    fout.close();
}
