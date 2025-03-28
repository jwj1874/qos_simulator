#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <vector>

struct LogEntry {
    int time;
    int node_id;
    bool transmitted;
    bool collision;
    float value;
    float channel_gain;
};

class Logger {
private:
    std::vector<LogEntry> entries;

public:
    void log(int time, int node_id, bool transmitted, bool collision, float value, float channel_gain);
    void saveCSV(const std::string& filename) const;
};

#endif // LOGGER_H
