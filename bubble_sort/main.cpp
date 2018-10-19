#include <iostream>
#include <fstream>

using namespace std;

void swap(int in1, int in2, int *&x);

int main(void) 
{
	ifstream fin("data.txt");
	int *data;
	data = new int[6];
	
	for(int i = 0; i < 6; i++)
	{
		fin >> data[i];
	}
	
	for(int i = 0; i < 6; i++)
	{
		for(int j = i; j < 6; j++)
		{	
			if(data[i] > data[j])
				{
					swap(i, j, data);
				}
		}
	}
	
	for(int i = 0; i < 6; i++)
	{
		cout << data[i] << ' ' ;
	}
	
	fin.close();
	return 0;
}

void swap(int in1, int in2, int *&x)
{
	int temp;
	temp = x[in1];
	x[in1] = x[in2];
	x[in2] = temp; 
}

