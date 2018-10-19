#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class queue{
private:
    int max;           // maximum size of the queue
    int count;         // number of items in the queue
    int start;         // data[start] is the first entry in the queue
    int end;           // data[end-1] is the last entry in the queue
    vector<int> data;  // vector holding the queue of items

public:
    queue(int sz);                   // constructor, max = sz

    void put(int item);              // put the integer item onto the queue
    int get(void);                   // get an item at the head of the queue
    void write(ostream &out) const;  // send the data stored to out
    bool empty(void) const;          // check for empty queue
    bool full(void) const;           // check for full queue
    int head(void) const;
};

void mergesort(int *&S, int low, int high);
void merge(int *&S, int low, int middle, int high);

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

    mergesort(data, 0, n+1);

    for(int i = 0; i < n; i++)
    {
        cout << data[i] << ' ';
    }

    return 0;
}

queue::queue(int sz) : data(sz)
{
    max = sz;
    count = 0;           // the queue has no entries yet
    start = 0;
    end = 0;
}

void queue::put(int item)
{
	data[end] = item;
	count++;
	end++;
	if(end == max)
    {
        end = 0;
    }
}
int queue::get(void)
{
	int tmp = 0;
	tmp = data[start];
	start++;
	if(start == max)
	{
		start = 0;
	}
	count--;
	return tmp;
}
void queue::write(ostream &out) const
{
	for(int i = 0; i < count; i++)
	{
		if(start+i >= max)
		{
			out << data[i-max+start] << ' ';
		} else
		{
			out << data[i+start] << ' ';
		}
	}
	out << endl;
}

bool queue::empty(void) const
{
    return (count == 0);
}

bool queue::full(void) const
{
    return (count == max);
}

int queue::head(void) const
{
    return data[start];
}

void mergesort(int *&S, int low, int high)
{
    int middle;
    if(low < high)
    {
        middle = (low + high) / 2;
        mergesort(S, low, middle);
        mergesort(S, middle + 1, high);
        merge(S, low, middle, high);
    }
}

void merge(int *&S, int low, int middle, int high)
{
    int i;
    queue buffer1(high);
    queue buffer2(high);
    for(i = low; i < middle; i++)
    {
        buffer1.put(S[i]);
    }
    for(i = middle; i < high; i++)
    {
        buffer2.put(S[i]);
    }
    i = low;
    while(!buffer1.empty() && !buffer2.empty())
    {
        if(buffer1.head() <= buffer2.head())
        {
            S[i++] = buffer1.get();
        } else
        {
            S[i++] = buffer2.get();
        }
    }
    while(!buffer1.empty())
    {
        S[i++] = buffer1.get();
    }
    while(!buffer2.empty())
    {
        S[i++] = buffer2.get();
    }
}
