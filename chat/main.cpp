#include <iostream>
#include <vector>
#include <fstream>
#include <thread>
#include <csignal>
#include "UserData.h"

void interruptHandler(int signum)
{
    UserData::interrupt();
}

int main()
{
    std::string fileName;
    std::cin >> fileName;

    std::ofstream file;
    file.open(fileName);

    int usersNumber;
    std::cin >> usersNumber;

    std::vector<UserData> usersData;
    long long delay;
    std::string message;
    std::mutex mutex;

    std::vector<std::thread> usersThread(usersNumber);

    signal(SIGINT, interruptHandler);

    for(size_t i = 0; i < usersNumber; i++)
    {
        std::cin >> delay >> message;
        usersData.emplace_back(file, delay, message, i);
    }

    for(size_t i = 0; i < usersNumber; i++)
    {
        usersThread[i] = std::thread(&UserData::workerThread, usersData[i], std::ref(mutex));
    }

    for(size_t i = 0; i < usersNumber; i++)
    {
            usersThread[i].join();
            std::cout << i << std::endl;
    }
    file.close();
    return EXIT_SUCCESS;
}