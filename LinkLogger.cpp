#include "LinkLogger.h"
linkLogger::linkLogger()
{
	this->cnt = 0;
	user = "csv/default.csv";
}

linkLogger::linkLogger(vector<meeting*> newList, int cnt, string user_)
{
	this->list = newList;
	this->cnt = cnt;
	user_ = "csv/" + user_ + ".csv";
	user = user_;
}

linkLogger::linkLogger(string user_)
{
	this->cnt = 0;
	user_ = "csv/" + user_ + ".csv";
	user = user_;
	fstream linksCSV(user);
	string token;
	if (linksCSV.is_open())
	{
		while (getline(linksCSV, token))
		{
			meeting* tempMeeting = new meeting();
			istringstream tempStringS(token);
			string temp;
			getline(tempStringS, temp, ',');
			tempMeeting->setURL(temp);
			getline(tempStringS, temp, ',');
			tempMeeting->setInfo(temp);
			getline(tempStringS, temp, ',');
			tempMeeting->setDate(temp);
			getline(tempStringS, temp, ',');
			tempMeeting->setTime(temp);
			getline(tempStringS, temp, ',');
			tempMeeting->setPassword(temp);
			tempMeeting->setMtime();
			this->list.push_back(tempMeeting);
			cnt++;
		}
	}
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
		if (list[i] == link)
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

void linkLogger::addLink(meeting* newMeeting) //Add a link by adding it to the end of the CSV file
{
    //checks for CSV, creates one if it does not already exist
	fstream linksCSV(user);
    if (!linksCSV) {
        ofstream linksCSV(user);
        linksCSV.close();
    }
    linksCSV.open(user, std::ios::out | std::ios::app); //append the CSV
	linksCSV << newMeeting->getURL() << ", " << newMeeting->getInfo() << ", " << newMeeting->getTime() << ", " << newMeeting->getDate() << "," << newMeeting->getPassword() << "\n"; //add info from new meeting into CSV file
    linksCSV.close();
}

void linkLogger::updateCSV()
{
	ofstream linksCSV(user, std::ios::out | std::ios::trunc);
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
			temp.append(",");
			temp.append(list[i]->getPassword());
			temp.append(",\n");
			linksCSV << temp;
		}
	}
	linksCSV.close();
}

void linkLogger::openURL(string URL)
{
	ShellExecuteA(NULL, "open", URL.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

void linkLogger::insertMeeting(string url, string info, string time, string password)
{
	if (time.size() < 14 || time.size() > 18)
		return;
	cnt = cnt + 1;
	meeting* newMeeting = new meeting(url, info, time,password);
	list.push_back(newMeeting);
	updateCSV();
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
meeting* linkLogger::checkMeetingAlerts()
{
	for (int i = 0; i < cnt; i++)
	{
		bool tempB = list[i]->checkAlert();
		if (tempB == true)
			return list[i];
	}
	return nullptr;
}

unsigned int linkLogger::getCount()
{
	return cnt;
}
string linkLogger::getUser()
{
	return user;
}

meeting* linkLogger::getMeetingInt(int i)
{
	return list[i];
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
void meeting::playAlarm()
{
	if(allowNoise == true)
		Beep(350, 1000);
}
bool meeting::checkAlert()
{
	alert.getTime(time);
	bool alertChecker = alert.start_noti(date);
	if (alertChecker == true)
	{
		playAlarm();
		return true;
	}
	return false;
}

void meeting::disallowNoise()
{
	allowNoise = false;
}
void meeting::allow_Noise()
{
	allowNoise = true;
}
float meeting::getMTime()
{
	return mTime;
}
void meeting::setMtime()
{
	if (this->time.substr(this->time.size() - 2, 2) == "pm" || this->time.substr(this->time.size() - 2, 2) == "PM" || this->time.substr(this->time.size() - 2, 2) == "Pm" || this->time.substr(this->time.size() - 2, 2) == "pM")
	{
		string tempS = this->time.substr(0, this->time.size() - 3);
		string timeString = "";
		int j = 0;
		for (; j < tempS.size(); j++)
		{
			if (tempS[j] == ':')
				break;
			timeString += tempS[j];
		}

		int temp = stoi(timeString);
		temp += 12;
		if (temp == 24)
			temp = 12;
		mTime = temp;
		float tempF = stof(tempS.substr(j + 1, 2));
		mTime += (tempF / 60);
	}
	else
	{
		string tempS = this->time.substr(0, time.size() - 2);
		string timeString = "";
		int j = 0;
		for (; j < tempS.size(); j++)
		{
			if (tempS[j] == ':')
				break;
			timeString += tempS[j];
		}

		int temp = stoi(timeString);
		if (temp == 12)
			temp = 0;
		mTime = temp;
		float tempF = stof(tempS.substr(j + 1, 2));
		mTime += (tempF / 60);
	}
}