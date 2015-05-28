/*!
 * \class TimeCounter
 * \author Daniel Sundfeld
 * \copyright MIT License
 */
#include "TimeCounter.h"

#include <chrono>
#include <iostream>
#include <iomanip>
#include <string>

TimeCounter::TimeCounter(const std::string &msg)
: m_msg(msg)
{
    m_begin = std::chrono::high_resolution_clock::now();
}

TimeCounter::~TimeCounter()
{
    auto end = std::chrono::high_resolution_clock::now();
    auto dur = end - m_begin;
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count() % 1000;
    auto s = std::chrono::duration_cast<std::chrono::seconds>(dur).count() % 60;
    auto m = std::chrono::duration_cast<std::chrono::minutes>(dur).count();

    std::cout << m_msg
         << std::setfill('0') << std::setw(2) << m << ":"
         << std::setfill('0') << std::setw(2) << s << "."
         << std::setfill('0') << std::setw(3) << ms << " s" << std::endl;
}
