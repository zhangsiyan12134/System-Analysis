#include <iostream>
#include <fstream>

using namespace std;

void swap(int in1, int in2, int *&x);
void sort(int *&in);

int main(void) 
{
	ifstream fin("data.txt");
	int *data;
	data = new int[6];
	
	for(int i = 0; i < 6; i++)
	{
		fin >> data[i];
	}
	
	sort(data);
	
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

void sort(int *&in)
{
	int j;
	for(int i = 0; i < 6; i++)
	{
		j = i;
		while(in[j] > in[j+1])
		{
			swap(j, j+1, in);
			if(j > 0)
			{
				j--;
			}
		}
	}
}

