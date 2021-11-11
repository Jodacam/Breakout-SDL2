#ifndef LOGGER_H_
#define LOGGER_H_ true
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>

#define LOG_TO_CONSOLE 0x01
#define LOG_TO_FILE 0x02
#define LOG_ALL 0x03

static const char *LOG_FILE_INIT = "log.txt";
static std::string LOG_FILE = std::string(LOG_FILE_INIT);
static void printLog(const char *stream, uint8_t options = LOG_TO_FILE)
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

static void printLog(std::string stream, uint8_t options = LOG_TO_FILE)
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

static void InitLogger()
{
    printLog("---Empezando nuevo log---",LOG_TO_FILE);
}

#endif