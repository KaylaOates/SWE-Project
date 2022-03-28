#pragma once
#include <iostream>
#include<vector>
#include<string>
#include <fstream>
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
	meeting* getMeeting(string url_);
	bool removeLink(meeting* link);
	void updateCSV();
	unsigned int getCount();
};
