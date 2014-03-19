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

using namespace std;

class TimeCounter
{
    private:
        chrono::high_resolution_clock::time_point m_begin;
        string m_msg;

    public:
        TimeCounter(string msg = "");
        ~TimeCounter();
};
#endif
