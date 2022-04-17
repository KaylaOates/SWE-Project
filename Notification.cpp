#include "Notification.h"
Notification::Notification()
{
    now = time(0);
    diff = *localtime(&now);
    current = *localtime(&now);
    notificationTime = current;
    notificationTime.tm_sec = 0;
}

Notification::~Notification()
{
}
void Notification::getTime(string time)
{
    int pos = 0;
    if (time.substr(time.size() - 2, 2) == "pm" || time.substr(time.size() - 2, 2) == "PM" || time.substr(time.size() - 2, 2) == "Pm" || time.substr(time.size() - 2, 2) == "pM")
    {
        string tempS = time.substr(0, 1);
        int temp = stoi(tempS);
        temp += 12;
        tempS = to_string(temp);
        tempS += time.substr(1, 4);
        time = tempS;
    }
    else
    {
        time = time.substr(0, time.size() - 3);
    }
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
bool Notification::start_noti(string date)
{
    stopALarm = true;
    system("cls");
    now = time(0);
    current = *localtime(&now);
    string ans;
    timeDiffer();
    cout << "TIME REMAINING:    " << diff.tm_hour << ":" << diff.tm_min << ":" << diff.tm_sec << endl;
    string day = todayDay(diff.tm_wday);
    for (int i = 0; i < date.size(); i++)
    {
        date[i] = tolower(date[i]);
    }
    bool dateCheck = false;
    if (date == day)
        dateCheck = true;
    if (diff.tm_hour == 0 && diff.tm_min == 0 && diff.tm_sec == 0 && dateCheck)
    {
        return true;
    }
    return false;
}
void Notification::setStopAlarm()
{
    stopALarm = true;
}

void Notification::stopAlarm()
{
    stopALarm = false;
}
string Notification::todayDay(int dayInt)
{
    if (dayInt == 0)
    {
        return "sunday";
    }
    else if (dayInt == 1)
    {
        return "monday";
    }
    else if (dayInt == 2)
    {
        return "tuesday";
    }
    else if (dayInt == 3)
    {
        return "wednesday";
    }
    else if (dayInt == 4)
    {
        return "thursday";
    }
    else if (dayInt == 5)
    {
        return "friday";
    }
    else
    {
        return "saturday";
    }
}