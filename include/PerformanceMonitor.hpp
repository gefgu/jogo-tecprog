#ifndef PERFORMANCE_MONITOR_HPP
#define PERFORMANCE_MONITOR_HPP

#include <chrono>
#include <iostream>

class PerformanceMonitor {
public:
    void startFrame();
    void endFrame();
    void printFPS() const;

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    float frameTime = 0.0f;
    float fps = 0.0f;
};

#endif // PERFORMANCE_MONITOR_HPP
