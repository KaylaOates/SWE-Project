#include "catch2/catch.hpp"
#include "LinkLogger.h"
#include <algorithm>
#include <iterator>
#include "functions.h"

//HOW TO USE:
//-add your own TEST_CASE()  down below
//-each TEST_CASE() should have SECTION() areas that seperate different test cases. 
//-each SECTION() has a REQUIRE statement that will test if two value are the same, if they are then the test case passes, else it fails
//-all test cases should pass, if they do not something is wrong!

TEST_CASE("Testing removal behaviour")
{
	SECTION("Testing 1 normal removal of link to empty")
	{
		remove("csv/test.csv");
		linkLogger* meetingList = new linkLogger("test");
		//insert and remove 1 link
		meetingList->insertMeeting("https://ufl.zoom.us/j/99700198187", "test", "5:00 pm monday", "123");
		meetingList->removeLink(meetingList->getMeeting("https://ufl.zoom.us/j/99700198187"));
		ifstream linkCSV(meetingList->getUser());
		REQUIRE(linkCSV.peek() == EOF); //first entry of the file should be the end-of-file
	}
	SECTION("Testing 1 normal removal of link from 5 total")
	{
		remove("csv/test.csv");
		linkLogger* meetingList = new linkLogger("test");
		//insert 5 links and remove one of them
		meetingList->insertMeeting("https://ufl.zoom.us/j/99700198181", "test", "5:00 pm monday", "123");
		meetingList->insertMeeting("https://ufl.zoom.us/j/99700198182", "test", "5:00 pm monday", "123");
		meetingList->insertMeeting("https://ufl.zoom.us/j/99700198183", "test", "5:00 pm monday" , "123");
		meetingList->insertMeeting("https://ufl.zoom.us/j/99700198184", "test", "5:00 pm monday" , "123");
		meetingList->insertMeeting("https://ufl.zoom.us/j/99700198185", "test", "5:00 pm monday" , "123");
		meetingList->removeLink(meetingList->getMeeting("https://ufl.zoom.us/j/99700198183"));

		//open links.csv and the test file for the first test
		ifstream linkCSV(meetingList->getUser());
		ifstream testFile(meetingList->getUser());

		//iterators for compareFile function
		std::istreambuf_iterator<char> file1B(linkCSV);
		std::istreambuf_iterator<char> file2B(testFile);
		std::istreambuf_iterator<char> end;

		bool test1A = compareFile(file1B, file2B, end, end); //check if the files are the same
		bool test1B = false; //bool for checking count
		if (meetingList->getCount() == 4)
		{
			test1B = true;
		}
		bool test1 = test1A && test1B; //check if both are true
		REQUIRE(test1 == true);
	}
	SECTION("Testing 5 normal removals of link from 5 total")
	{
		remove("csv/test.csv");
		linkLogger* meetingList = new linkLogger("test");
		//insert 5 links and remove one of them
		meetingList->insertMeeting("https://ufl.zoom.us/j/99700198181", "test", "5:00 pm monday" , "123");
		meetingList->insertMeeting("https://ufl.zoom.us/j/99700198182", "test", "5:00 pm monday" , "123");
		meetingList->insertMeeting("https://ufl.zoom.us/j/99700198183", "test", "5:00 pm monday" , "123");
		meetingList->insertMeeting("https://ufl.zoom.us/j/99700198184", "test", "5:00 pm monday" , "123");
		meetingList->insertMeeting("https://ufl.zoom.us/j/99700198185", "test", "5:00 pm monday" , "123");

		meetingList->removeLink(meetingList->getMeeting("https://ufl.zoom.us/j/99700198181"));
		meetingList->removeLink(meetingList->getMeeting("https://ufl.zoom.us/j/99700198182"));
		meetingList->removeLink(meetingList->getMeeting("https://ufl.zoom.us/j/99700198183"));
		meetingList->removeLink(meetingList->getMeeting("https://ufl.zoom.us/j/99700198184"));
		meetingList->removeLink(meetingList->getMeeting("https://ufl.zoom.us/j/99700198185"));

		//open links.csv and the test file for the first test
		ifstream linkCSV(meetingList->getUser());
		REQUIRE(linkCSV.peek() == EOF); //first entry of the file should be the end-of-file
	}
	SECTION("Testing removal of edge links from 5 total")
	{
		remove("csv/test.csv");
		linkLogger* meetingList = new linkLogger("test");
		//insert 5 links and remove one of them
		meetingList->insertMeeting("https://ufl.zoom.us/j/99700198181", "test", "5:00 pm monday" , "123");
		meetingList->insertMeeting("https://ufl.zoom.us/j/99700198182", "test", "5:00 pm monday" , "123");
		meetingList->insertMeeting("https://ufl.zoom.us/j/99700198183", "test", "5:00 pm monday" , "123");
		meetingList->insertMeeting("https://ufl.zoom.us/j/99700198184", "test", "5:00 pm monday" , "123");
		meetingList->insertMeeting("https://ufl.zoom.us/j/99700198185", "test", "5:00 pm monday" , "123");

		meetingList->removeLink(meetingList->getMeeting("https://ufl.zoom.us/j/99700198181"));
		meetingList->removeLink(meetingList->getMeeting("https://ufl.zoom.us/j/99700198185"));

		//open links.csv and the test file for the first test
		ifstream linkCSV(meetingList->getUser());
		ifstream testFile("csvTest/csvTest2.csv");

		//iterators for compareFile function
		std::istreambuf_iterator<char> file1B(linkCSV);
		std::istreambuf_iterator<char> file2B(testFile);
		std::istreambuf_iterator<char> end;

		bool test1A = compareFile(file1B, file2B, end, end); //check if the files are the same
		bool test1B = false; //bool for checking count
		if (meetingList->getCount() == 3)
		{
			test1B = true;
		}
		bool test1 = test1A && test1B; //check if both are true
		REQUIRE(test1 == true);
	}
	SECTION("Testing removal of 1 links from 0 total")
	{
		remove("csv/test.csv");
		linkLogger* meetingList = new linkLogger("test");
		//remove from empty linkLogger

		bool test2A = meetingList->removeLink(meetingList->getMeeting("https://ufl.zoom.us/j/99700198181"));
		ifstream linkCSV(meetingList->getUser());
		bool test2B = true;
		bool test2 = false;
		if (linkCSV.peek() == EOF || !linkCSV.good())
		{
			test2B = false;
		}
		if (test2A == false && test2B == false)
		{
			test2 = true;
		}
		REQUIRE(test2 == true);
	}
}