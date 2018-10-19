#include <iostream>
#include <fstream>

using namespace std;

void swap(int in1, int in2, int *&x);
void quicksort(int *&S, int l, int h);
int partition(int *&S, int l, int h);

int main()
{
    int *data, n;
    ifstream infile("data.txt");
    infile >> n;
    data = new int[n];
    for(int i = 0; i < n; i++)
    {
        infile >> data[i];
    }

    quicksort(data, 0, n+1);

    for(int i = 0; i < n; i++)
    {
        cout << data[i] << ' ';
    }

    return 0;
}

void swap(int in1, int in2, int *&x)
{
	int temp;
	temp = x[in1];
	x[in1] = x[in2];
	x[in2] = temp;
}

void quicksort(int *&S, int l, int h)
{
    int p;
    if((h - l) > 0)
    {
        p = partition(S, l, h);
        quicksort(S, l, p-1);
        quicksort(S, p+1, h);
    }
}

int partition(int *&S, int l, int h)
{
    int i, p, firsthigh;
    p = h;
    firsthigh = l;
    for(i = l; i < h; i++)
    {
        if(S[i] < S[p])
        {
            swap(i, firsthigh, S);
            firsthigh++;
        }
    }
    swap(p, firsthigh, S);
    return firsthigh;
}
