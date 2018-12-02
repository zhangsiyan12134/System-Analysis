/*
Assignment #3 Simplified Verison
Programmer: Siyan Zhang
BO#: B00815329
*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

class planes
{
private:
    int date;           //date that available
    int zone;			//number of zones on plane
    float *price;       //array of price for each zone
    int *seats;         //array of sold seats of each zone
    int seatperzone;
public:
    planes(int d = 1, int z = 5, int sp = 10);  //plane arrangement
    ~planes(void);
    void set_zoneprice(int z, int p);
    int get_date(void) const;       //get the available date
    float get_price(void) const;    //get the lowest available seat price
    bool full(void) const;          //check if plane still available
    void seat_sold();               //one of seat in given zone was sold
    void write(ostream &fout);		//print out the customer list
} ;

class customer
{
private:
    int login_time;                 //time that current customer logged in
    float price;                    //maximum price that customer can accept
    float ticket;                   //price of ticket if they bought one
public:
    customer(int t = 0, int p = 0);
    void set_time(int t);           //set login time
    void set_price(float p);        //set customer maximum acceptable price
    void set_ticket(float p);       //set actual price that customer paied
    int get_time(void) const;       //get the customer login time
    float get_price(void) const;    //get customer maximum acceptable price
    float get_ticket(void) const;   //get actual price that customer paied
};

int main()
{
    int system_timeout, customer_time, n_customer;
    int t = 0;                                      //system time counter
    int price_zone[]={100, 200, 300, 400, 500};     //price for each zone
    queue<customer> customer_waiting;               //create a queue for waiting customers
    vector<customer> customer_list;                 //create a vector for customer who purchesed a ticket
    customer *ptr;                                  //a customer type pointer for load customer info dynamiclly
    planes flight(1,5,10);                          //one and only one scheduled plane
    for(int i = 0; i < 5; i++)
    {
        flight.set_zoneprice(i, price_zone[i]);     //load the price list for zones
    }
    ifstream fin("input.txt");                      //read in data
    ofstream fout("output.txt");
    fin >> system_timeout;
    fin >> customer_time;
    fin >> n_customer;

    for(int i = 0; i < n_customer; i++)
	{
        int time, price;
        fin >> time >> price;                       //read a line
        ptr = new customer;                         //create a new account for customer
        ptr->set_time(time);                        //store user info
        ptr->set_price(price);
        ptr->set_ticket(0.0);
        customer_waiting.push(*ptr);                //put customer into waiting area
    }

    for(t = 1; t <= system_timeout; t++)
    {
		customer temp = customer_waiting.front();        	//check the status of customer in front of the waiting line
        if((!customer_waiting.empty())&&(!flight.full()))   //if there is customer waiting
        {
            if(temp.get_price() >= flight.get_price())  	//check if current price is acceptable
            {
                if(temp.get_time() + customer_time == t)    //check if customer finally make up their mind
                {
                    temp.set_ticket(flight.get_price());    //customer bought the ticket
                    customer_list.push_back(temp);          //add customer info into flight list
                    flight.seat_sold();                     //undate available seats list
                    customer_waiting.pop();                 //finished payment and logout customer
                }
            } else
    		{
       			customer_list.push_back(temp);
        		customer_waiting.pop();                     //logout customer if no seats meet their requirement
    		}
        }
	}

    for(int i = 0; i < customer_list.size(); i++)
    {
        if(!customer_list.empty())
        {
            cout << customer_list[i].get_ticket() << endl;
            fout << customer_list[i].get_ticket() << endl;
        }
    }

	while(!customer_waiting.empty())
    {
        cout << customer_waiting.front().get_ticket() << endl;
        fout << customer_waiting.front().get_ticket() << endl;		//print rest of the customer
        customer_waiting.pop();										//logout rest of the customer
    }

	fout.close();
    fin.close();
    return 0;
}

/*--------------------------------------------------------------------------------------
						Methodes implmentation of planes class
--------------------------------------------------------------------------------------*/
planes::planes(int d, int z, int sp)
{
    date = d;
    zone = z;
    seatperzone = sp;
    price = new float[z];
    seats = new int[z];
    for(int i = 0; i < z; i++)
    {
        seats[i] = 0;
    }
}
planes::~planes(void)
{
    delete [] price;
    delete [] seats;				//delete those two dynamically allocated array
}

void planes::set_zoneprice(int z, int p)
{
    price[z] = p;
}

int planes::get_date(void) const     //get the available date
{
    return date;
}
float planes::get_price(void) const    //get the lowest available seat price
{
	for(int i = 0; i < zone; i++)
    {
		if(seats[i] < seatperzone) return price[i];
    }
}
bool planes::full(void) const             //check if plane still available
{
	int count = 0;
    for(int i = 0; i < zone; i++)
    {
		if(seats[i] == seatperzone)
		{
			count++;
		}
	}
	if(count == zone)
	{
		return true;
	} else
    {
    	return false;
	}
}

void planes::seat_sold()     //one of seat in given zone was sold
{
	for(int i = 0; i < zone; i++)
    {
		if(seats[i] < seatperzone)
        {
            seats[i]++;
            break;
        }
    }
}

/*--------------------------------------------------------------------------------------
						Methodes implmentation of customer class
--------------------------------------------------------------------------------------*/

customer::customer(int t, int p)
{
	login_time = t;
	price = p;
}
void customer::set_time(int t)
{
	login_time = t;
}
void customer::set_price(float p)
{
	price = p;
}
void customer::set_ticket(float p)
{
    ticket = p;
}
int customer::get_time(void) const
{
	return login_time;
}
float customer::get_price(void) const
{
	return price;
}
float customer::get_ticket(void) const
{
    return ticket;
}

