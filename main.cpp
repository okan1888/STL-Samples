#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include<ctime> 
#include<algorithm>
#include<array>
#include<map>


#define CLIENT_SIZE 999
#define SONG_SIZE 9999
#define COUNT_SIZE 999

using namespace std;

template<typename K, typename V>
int countByValue(std::multimap<K, V> &mapOfElemen, V value)
{
	int count=0;
	vector<string> vec;
	auto it = mapOfElemen.begin();
	// Iterate through the map
	while (it != mapOfElemen.end())
	{
		// Check if value of this entry matches with given value
		if (it->second == value)
		{
			// Yes found
			// Push the key in given map
			vec.push_back(it->first);
		}
		// Go to next entry in map
		it++;
	}
	vector<string>::iterator ip;
	ip = unique(vec.begin(), vec.end());
	vec.resize(std::distance(vec.begin(), ip));
	return vec.size();
}


int main() {

	//for time measurements,gets system time
	struct tm * tiStart, *tiEnd;
	time_t ttStart, ttEnd;
	time(&ttStart);
	tiStart = localtime(&ttStart);
	std::cout << " start time = " << asctime(tiStart) << endl;

	//grep the lines for a specific date via system call,faster than getline parsing.
	system("echo. >> testOK.csv");
	system("type exhibitA-input.csv | findstr \"10/08/2016\" >> testOK.csv");
	ifstream inputFile("testOK.csv");
	string tempLine;
	string play_id, song_id, client_id, playtime;
	multimap <string, string> fileTable;
	while (getline(inputFile, tempLine, '\n'))
	{
		inputFile >> play_id >> song_id >> client_id >> playtime;
		fileTable.insert(pair<string, string>(song_id, client_id));
	}
	vector<int> allVec;
	for (int cID = 1; cID <= CLIENT_SIZE; cID++) 
	{
		int dCount = countByValue(fileTable,to_string(cID));
		allVec.push_back(dCount);
	}

	for (int cID = 1; cID <= COUNT_SIZE; cID++)
	{
		int fCount = count(allVec.begin(),allVec.end(), cID);
		cout << "songCOUNT=" << cID << "clientcount=" << fCount << endl;
	}

	cout << endl;

	time(&ttEnd);
	tiEnd = localtime(&ttEnd);
	std::cout << " end time = " << asctime(tiEnd) << endl;

	return 0;

}
