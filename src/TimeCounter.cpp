/*!
 * \class TimeCounter
 * \author Daniel Sundfeld
 * \copyright MIT License
 */
#include <chrono>
#include <iostream>
#include <iomanip>
#include <string>

#include "TimeCounter.h"

using namespace std;

TimeCounter::TimeCounter(const string &msg)
: m_msg(msg)
{
    m_begin = chrono::high_resolution_clock::now();
}

TimeCounter::~TimeCounter()
{
    auto end = chrono::high_resolution_clock::now();
    auto dur = end - m_begin;
    auto ms = chrono::duration_cast<chrono::milliseconds>(dur).count() % 1000;
    auto s = chrono::duration_cast<chrono::seconds>(dur).count() % 60;
    auto m = chrono::duration_cast<chrono::minutes>(dur).count();

    cout << m_msg
         << (m) << "m" << std::fixed
         << setfill('0') << setw(2) << s << '.'
         << setfill('0') << setw(3) << ms << " s" << endl;
}
