#ifndef CHAT_USERDATA_H
#define CHAT_USERDATA_H

#include <ostream>
#include <iomanip>
#include <thread>

class UserData
{
private:
    static bool wasInterrupted;
    std::ostream &outFile;
    std::chrono::seconds delay;
    std::string message;
    const size_t id;
public:
    UserData(std::ostream &_outFile, long long _delay, std::string &_message, const size_t _id)
            : outFile{_outFile}, message{_message}, delay{_delay}, id{_id}
    {}

    static void interrupt()
    {
        wasInterrupted = true;
    }
    void workerThread(std::mutex &_mutex);
};
#endif
