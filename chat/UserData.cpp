#include "UserData.h"

bool UserData::wasInterrupted = false;


void UserData::workerThread(std::mutex &_mutex)
{
    while(outFile.good() && !wasInterrupted)
    {
        auto now = std::chrono::system_clock::now();
        auto timer = std::chrono::system_clock::to_time_t(now);
        std::tm bt = *std::localtime(&timer);
        _mutex.lock();
        outFile << std::put_time(&bt, "%H:%M:%S") << " "  << id << " " << message << std::endl;
        _mutex.unlock();
        outFile.flush();
        std::this_thread::sleep_for(delay);
    }
}