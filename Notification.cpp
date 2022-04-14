#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <sstream>
using namespace std;
class Notification
{
public:
	Notification();
    ~Notification();
    void getTime();
    void timeDiffer();
    void start_noti();
    void setStopAlarm();
    bool stopALarm = true;;
    tm notificationTime;
    tm current;
    tm diff;
    time_t now;
};

Notification::Notification()
{
    now = time(0);
    current = *localtime(&now);
    notificationTime = current;
    notificationTime.tm_sec = 0;
}

Notification::~Notification()
{
}
void Notification::getTime()
{
    string time;
    cout << "Enter Alarm Time in 24-hour format [HH:MM]: "; getline(cin, time);
    int pos = 0, h;
    while ((pos = time.find(':')) != string::npos)
    {
        string token = time.substr(0, pos);
        stringstream convert(token);
        convert >> notificationTime.tm_hour;
        time.erase(0, pos + 1);
    }
    stringstream convert(time);
    convert >> notificationTime.tm_min;

}
void Notification::timeDiffer()
{
    int sec = difftime(mktime(&notificationTime), now);
    diff.tm_min = sec / 60;
    diff.tm_hour = diff.tm_min / 60;
    diff.tm_min = diff.tm_min % 60;
    diff.tm_sec = sec % 60;
    if (sec < 0)
    {
        diff.tm_hour = 24 + diff.tm_hour - 1;
        diff.tm_min = 0 - diff.tm_min;
        diff.tm_sec = 0 - diff.tm_sec;
    }
}
void Notification::start_noti()
{
    stopALarm = true;
    while (stopALarm)
    {
        system("cls");
        now = time(0);
        current = *localtime(&now);
        string ans;
        timeDiffer();
        cout << "TIME REMAINING:    " << diff.tm_hour << ":" << diff.tm_min << ":" << diff.tm_sec;
        if (diff.tm_hour == 0 && diff.tm_min == 0 && diff.tm_sec == 0)
        {
            cout << endl << "Time Ended" << endl << ">>> You can only close this page to turn off the alarm for now kinda annoy to be honest <<<" << endl;
            break;
        }
    }
}
void Notification::setStopAlarm()
{
    stopALarm = true;
}
int main()
{
    Notification a;
    a.getTime();
    a.start_noti();
    for (int i = 0; ; i = i + 50) {
        Beep(i, 1000);
    }
    return 0;
}
