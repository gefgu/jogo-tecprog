#include "PerformanceMonitor.hpp"

void PerformanceMonitor::startFrame() {
    start = std::chrono::high_resolution_clock::now();
}

void PerformanceMonitor::endFrame() {
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end - start;
    frameTime = duration.count();
    fps = 1.0f / frameTime;
}

void PerformanceMonitor::printFPS() const {
    std::cout << "FPS: " << fps << " (Frame time: " << frameTime << "s)" << std::endl;
}
