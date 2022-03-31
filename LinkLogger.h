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
	string password;
public:
	meeting(string url, string info, string time, string date, string password) {
		this->url = url;
		this->info = info;
		this->time = time;
		this->date = date;
		this->password = password;
	}
	void setURL(string newUrl);
	void setInfo(string newInfo);
	void setTime(string newTime);
	void setDate(string newDate);
	void setPassword(string password);
	string getURL();
	string getInfo();
	string getTime();
	string getDate();
	string getPassword();
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
	void insertMeeting(string url, string info, string time, string date,string password);
	meeting* getMeeting(string url_);
	bool removeLink(meeting* link);
	void addLink(meeting* newMeeting);
	void updateCSV();
	unsigned int getCount();
};
