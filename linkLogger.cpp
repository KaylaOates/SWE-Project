#include <iostream>
#include<vector>
#include<string>
#include <windows.h>
#include <shellapi.h>
using namespace std;

struct meeting {
private:
	string url;
	string info;
	string time;
	string date;
public:
	meeting(string url, string info, string time, string date) {
		this->url = url;
		this->info = info;
		this->time = time;
		this->date = date;
	}
	void setURL(string newUrl);
	void setInfo(string newInfo);
	void setTime(string newTime);
	void setDate(string newDate);
	string getURL();
	string getInfo();
	string getTime();
	string getDate();
};
class linkLogger
{
private:
	vector<meeting*> list;
	unsigned int cnt;
public:
	linkLogger();
	linkLogger(vector<meeting*> newList, int cnt);
	~linkLogger();
	void openURL(string& URL);
	void insertMeeting(string url, string info, string time, string date);
	meeting* getMeeting();
};

linkLogger::linkLogger()
{
	this->cnt = 0;
}

linkLogger::linkLogger(vector<meeting*> newList, int cnt)
{
	this->list = newList;
	this->cnt = cnt;
}

linkLogger::~linkLogger()//Remove Meeting
{
}

void linkLogger::openURL(string& URL)
{
	ShellExecuteA(NULL, "open", URL.c_str(),NULL, NULL, SW_SHOWNORMAL);
}

void linkLogger::insertMeeting(string url, string info, string time, string date)
{
	cnt = cnt + 1;
	meeting* newMeeting = new meeting(url, info, time, date);
	list.push_back(newMeeting);
}

meeting* linkLogger::getMeeting()
{
	return list[0];
}

void meeting::setURL(string newUrl)
{
	this->url = newUrl;
}

void meeting::setInfo(string newInfo)
{
	this->info = newInfo;
}

void meeting::setTime(string newTime)
{
	this->time = newTime;
}

void meeting::setDate(string newDate)
{
	this->date = newDate;
}
string meeting::getURL()
{
	return url;
}
string meeting::getInfo()
{
	return info;
}
string meeting::getTime()
{
	return time;
}
string meeting::getDate()
{
	return date;
}


int main()
{
	linkLogger* meetingList = new linkLogger();
	meetingList->insertMeeting("www.google.com", "google", "3:48", "3/23/2022");
	string newurl = meetingList->getMeeting()->getURL();
	meetingList->openURL(newurl);
	return 0;
}