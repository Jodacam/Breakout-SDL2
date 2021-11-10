#ifndef _LOGGER_H_
#define _LOGGER_H_
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>

#define LOG_TO_CONSOLE 0x01
#define LOG_TO_FILE 0x02
#define LOG_ALL 0x03

const char *LOG_FILE_INIT = "log.txt";
std::string LOG_FILE;
void printLog(const char *stream, uint8_t options = LOG_TO_CONSOLE)
{
    using namespace std;
    auto end = chrono::system_clock::now();
    time_t end_time = chrono::system_clock::to_time_t(end);
    auto date = ctime(&end_time);
    if (options & LOG_TO_FILE)
    {
        ofstream File;
        File.open(LOG_FILE, std::ios::app);
        File << date << stream << endl;
        File.close();
    }
    if (options & LOG_TO_CONSOLE)
    {
        std::cout << date << stream << endl;
    }
}

void InitLogger()
{
    using namespace std;
    auto end = chrono::system_clock::now();
    time_t end_time = chrono::system_clock::to_time_t(end);
    auto date = ctime(&end_time);
    string name = string(LOG_FILE_INIT);
    LOG_FILE = string(date);
    LOG_FILE.erase(LOG_FILE.end()-1);
    LOG_FILE = LOG_FILE.append("-").append(name);
}

#endif