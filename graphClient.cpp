/*******************************************************************
Group Name: ABET - Dijstra's Storm
Name: Minh T., Eduardo R., Aaron H.
Description: We code, we compile, we kill.🔥
*******************************************************************/
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <stack>
#include "graph.h"
using namespace std;

const int MAX = 20;

void showDescription();
void collectCityInfo(Place st[]);
void showDistance(const Place& a, const Place& b);

int main(int argc, char** argv)
{
	//cout << "You have entered " << argc << " arguments:" << endl;
	//cout << argv[1] << argv[2] << endl;
  
	Place cityData[MAX];
  
	//Do ./a.out AN BK
	showDescription(); //Showing the basic ideas.

	graph road(77);
	ifstream fin;
	fin.open("road.txt");
	int v, u, w;
	fin >> v >> u >> w;
	while(fin)
	{
		road.addEdge(v, u, w);
		fin >> v >> u >> w;
	}
	collectCityInfo(cityData);

	string place_start = argv[1];
	string place_dest = argv[2];
  
	int abr_start = -1;
	int abr_dest = -1;
  
	for(int i = 0; i < MAX; i++)
    {
      if (place_start == cityData[i].abr)
      {
        abr_start = i;
      }

      if (place_dest == cityData[i].abr)
      {
        abr_dest = i;
      }
    }
	
	if(abr_start == -1)
	{
		cout << "Invalid city code: " << argv[1] << endl;
	}
	else if (abr_dest == -1)
	{
		cout << "Invalid city code: " << argv[2] << endl;
	}
	else
	{
		showDistance(cityData[abr_start], cityData[abr_dest]);
		road.DijkstraShortestPath(abr_start, abr_dest, cityData); //ANAHEIM to BAKERSFIELD
	}
	
	fin.close();

	return 0;
}

void showDescription()
{
  cout << "Author: Eduardo R., Minh T., Aaron H." << endl;
  cout << "Date: 11/28/2022" << endl;
  cout << "Course: CS311 (Data structures and Algorithms)" << endl;
  cout << "Description: Program to find the shortest route between cities" << endl;
  cout << "---------------------------------------------------------------- " << endl;
}

void collectCityInfo(Place st[])
{
ifstream inputfile;
  inputfile.open("city.txt");
  
   int i = 0;
  inputfile >> st[0].num;
  inputfile >> st[0].abr;
  inputfile >> st[0].name;
  inputfile >> st[0].population;
  inputfile >> st[0].elevation;
  while(inputfile && i < MAX)
    {
      i++;
      inputfile >> st[i].num;
      inputfile >> st[i].abr;
      inputfile >> st[i].name;
      inputfile >> st[i].population;
      inputfile >> st[i].elevation;
    }
  inputfile.close();
}

void showDistance(const Place& a, const Place& b)
{
cout << "From city: " << a.name << ", population " << a.population << ", elevation " << a.elevation << endl;
cout << "To city: " << b.name << ", population " << b.population << ", elevation " << b.elevation << endl;  
}
