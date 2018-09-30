/*OKAN KARADAG SEPT.2018
CODE FOR SOLVING EXHIBIT A.
okankaradag@gmail.com*/

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <ctime> 
#include <algorithm>
#include <array>
#include <map>


using namespace std;
//standart binary search algorithm for string array
int binarySearch(string names[], int size, string value)
{
	int first = 0,             
		last = size - 1,       
		middle,                
		position = -1;         
	bool found = false;      

	while (!found && first <= last)
	{
		middle = (first + last) / 2;    
		if (names[middle] == value)   
		{
			found = true;
			position = middle;
		}
		else if (names[middle] > value)
			last = middle - 1;
		else
			first = middle + 1;      
	}
	return position;
}


int main() {
	
	//for time measurements,gets system time
	struct tm * tiStart, *tiEnd;
	time_t ttStart, ttEnd;
	time(&ttStart);
	tiStart = localtime(&ttStart);
	std::cout << " start time = " << asctime(tiStart) << endl;

	//grep the lines for a specific date via system call,faster than getline parsing.
	system("type exhibitA-input.csv | findstr \"10/08/2016\" >> testOK.csv");
	ifstream inputFile("testOK.csv");
	string tempLine;
	//used arrays against template versions,becuase faster for fixed known stacksize.
	string songList[1400001]; 
	string clientList[1400001];
	vector<string> clientV;
	vector<string> songV;
	string play_id,song_id,client_id,playtime;
	int i = 0;
	int j = 0;

	while (getline(inputFile, tempLine, '\n')) 
	{
		inputFile >> play_id >> song_id >> client_id >> playtime;
		string codeStr = song_id + client_id;
		int iFound = binarySearch(clientList,1400001, client_id);
		if (iFound == -1)
		{
			clientList[i]=client_id;
			clientV.push_back(client_id);
			clientList[i].assign(client_id);
			songList[j] = codeStr;
			songV.push_back(song_id);
			i++;
			j++;
		}
		else
		{
			
			int iFound = binarySearch(songList, 1400001, codeStr);
			if (iFound == -1)
			{
				clientV.push_back(client_id);
				clientList[i].assign(client_id);
				songList[j] = codeStr;
				songV.push_back(song_id);
				i++;
				j++;
			}
		}
	}
	vector<int> distinctCountsVec;
	for (int cID = 1; cID <= 999; cID++) // there are known 999 client_id
	{
		int dCount = std::count(clientV.begin(), clientV.end(), std::to_string(cID));
		distinctCountsVec.push_back(dCount);
	}
	map <int, int> countTable;
	for (unsigned int i = 0; i < distinctCountsVec.size(); i++)
	{
		int finalClientCount = std::count(distinctCountsVec.begin(), distinctCountsVec.end(), distinctCountsVec[i]);
		countTable.insert(pair<int, int>(distinctCountsVec[i], finalClientCount));
	}
	//print content of final table
	map <int, int> ::iterator itr;
	cout << "\nThe map CountTable is : \n";
	cout << "\tKEY\tELEMENT\n";
	for (itr = countTable.begin(); itr != countTable.end(); ++itr)
	{
		cout << '\t' << itr->first
			<< '\t' << itr->second << '\n';
	}
	cout << endl;

	time(&ttEnd);
	tiEnd = localtime(&ttEnd);
	std::cout << " end time = " << asctime(tiEnd) << endl;

	return 0;
}
