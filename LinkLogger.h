#pragma once
#include <iostream>
#include<vector>
#include<string>
#include <sstream>
#include <fstream>
#include <windows.h>
#include <shellapi.h>
#include "Notification.h"
using namespace std;

struct meeting {
private:
	string url;
	string info;
	string time;
	string date;
	string password;
	float mTime;
	Notification alert;
	bool allowNoise;
public:
	meeting(string url, string info, string time, string password) {
		this->url = url;
		this->info = info;
		string tempString = "";
		int i = 0;
		for (; i < time.size(); i++)
		{
			tempString += time[i];
			if (time[i] == 'm' || time[i] == 'M')
			{
				break;
			}
		}

		this->time = tempString;
		this->date = time.substr(i+2,time.size()-i);
		this->password = password;
		Notification alert();
		allowNoise = true;
		this->setMtime();
	}
	meeting()
	{
		url = "";
		info = "";
		time = "";
		date = "";
		password = "";
	}
	void setURL(string newUrl);
	void setInfo(string newInfo);
	void setTime(string newTime);
	void setDate(string newDate);
	void setPassword(string password);
	void setMtime();
	string getURL();
	string getInfo();
	string getTime();
	string getDate();
	string getPassword();
	float getMTime();
	bool checkAlert();
	void playAlarm();
	void disallowNoise();
	void allow_Noise();
};
class linkLogger
{
private:
	vector<meeting*> list;
	unsigned int cnt;
	string user;
public:
	linkLogger();
	linkLogger(vector<meeting*> newList, int cnt, string user);
	linkLogger(string user_);
	~linkLogger();
	void openURL(string URL);
	void insertMeeting(string url, string info, string time, string password);
	meeting* getMeeting(string url_);
	bool removeLink(meeting* link);
	void addLink(meeting* newMeeting);
	void updateCSV();
	string getUser();
	unsigned int getCount();
	meeting* checkMeetingAlerts();
	meeting* getMeetingInt(int i);
};