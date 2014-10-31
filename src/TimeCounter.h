/*!
 * \class TimeCounter
 * \author Daniel Sundfeld
 * \copyright MIT License
 *
 * \brief Class that count elapsed time between the creation and destruction
 */
#ifndef _TIMECOUNTER_H
#define _TIMECOUNTER_H
#include <chrono>
#include <iostream>
#include <string>

class TimeCounter
{
    public:
        TimeCounter(const std::string &msg = "");
        ~TimeCounter();

    private:
        std::chrono::high_resolution_clock::time_point m_begin;
        std::string m_msg;
};
#endif
