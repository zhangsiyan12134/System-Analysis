#include <iostream>
#include <fstream>

using namespace std;

int find_min(int *&in);

int main(void) 
{
	ifstream fin("data.txt");
	int *data, sort[6];
	data = new int[6];
	
	for(int i = 0; i < 6; i++)
	{
		fin >> data[i];
	}
	for(int i = 0; i < 6; i++)
	{
		sort[i] = find_min(data);
	}

	for(int i = 0; i < 6; i++)
	{
		cout << sort[i] << ' ' ;
	}
	
	fin.close();
	return 0;
}

int find_min(int *&in)
{
	int min = 1000000;
	int min_ind = 0;
	for(int i = 0; i < 6; i++)
	{
		if(min > in[i])
		{
			min = in[i];
			min_ind = i;
		}
	}
	in[min_ind] = 1000000;
	return min;	
}

