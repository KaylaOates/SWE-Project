#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <sstream>
using namespace std;

struct Notification
{
    Notification();
    ~Notification();
    void getTime(string time);
    void timeDiffer();
    bool start_noti(string date);
    void setStopAlarm();
    bool stopALarm = true;
    tm notificationTime;
    tm current;
    tm diff;
    time_t now;
    string todayDay(int dayInt);
    void stopAlarm();
};