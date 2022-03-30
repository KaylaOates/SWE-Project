#include "LinkLogger.h"
linkLogger::linkLogger()
{
	this->cnt = 0;
}

linkLogger::linkLogger(vector<meeting*> newList, int cnt)
{
	this->list = newList;
	this->cnt = cnt;
}

linkLogger::~linkLogger()//desructor
{
}
bool linkLogger::removeLink(meeting* link) //Remove a link by going through the list and choosing which ones to remove. If removal cannot happen, return false, otherwise return true.
{
	//if the linkLogger count is 0, it is empty so removal is not possible
	if (this->cnt == 0)
	{
		return false;
	}
	//find the link to be deleted and then remove it from the linkLogger
	for (int i = 0; i < cnt; i++)
	{
		if (list[i]->getURL() == link->getURL())
		{
			list.erase(list.begin() + i);
			cnt--;
			break;
		}
	}
	//update the CSV
	this->updateCSV();
	return true;
}

void linkLogger::updateCSV()
{
	ofstream linksCSV("csv/links.csv", std::ios::out | std::ios::trunc);
	if (linksCSV.is_open())
	{
		for (int i = 0; i < cnt; i++)
		{
			string temp = "";
			temp.append(list[i]->getURL());
			temp.append(",");
			temp.append(list[i]->getInfo());
			temp.append(",");
			temp.append(list[i]->getDate());
			temp.append(",");
			temp.append(list[i]->getTime());
			temp.append(",\n");
			linksCSV << temp;
		}
	}
	linksCSV.close();
}

void linkLogger::openURL(string& URL)
{
	ShellExecuteA(NULL, "open", URL.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

void linkLogger::insertMeeting(string url, string info, string time, string date,string password)
{
	cnt = cnt + 1;
	meeting* newMeeting = new meeting(url, info, time, date,password);
	list.push_back(newMeeting);
}

meeting* linkLogger::getMeeting(string url_)
{
	for (int i = 0; i < cnt; i++)
	{
		if (list[i]->getURL() == url_)
		{
			return list[i];
		}
	}
	return nullptr;
}

unsigned int linkLogger::getCount()
{
	return cnt;
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
void meeting::setPassword(string password)
{
	this->password = password;
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

string meeting::getPassword()
{
	return password;
}
