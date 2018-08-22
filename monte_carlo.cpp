#include<iostream>
#include<iomanip>
#include<math.h> 
#include<stdlib.h> //srand, rand
#include<new>  //dynamic array
# include <complex>
#include <time.h>// random time(null)
//#include "array.hpp" 

using namespace std;
//template <typename T> ;
//T eucall ();
/*template<typename T>
T genNor()
{
	srand(time(NULL)); //random seed
	double mean =0, std=1;
	double u, v; //uniform dist
	double x,y; // normal dist
	static complex<double> value;
	
	u=rand()/(double)RAND_MAX;
	v=rand()/(double)RAND_MAX;
	x=sqrt(-2*log(u))*cos(2 * M_PI * v);
	y=sqrt(-2*log(u))*sin(2 * M_PI * v) ;
	
	value= complex<double> (x,y);
	//value[1]= x;
	//value[2]= y;
	//cout<<value[1]<<";"<<value[2]<<endl;
	cout<<value;
	//return value;
}*/

int main()
{
	double spotPrice0; //stock price of t=0
	double iRate; // risk free rate
	double yield; // yield income
	double sigma; // volatility of the stock price
	double tOption; // time to maturity of option
	double strikeP; // strike price
	double up;// stock price go up
	double down;// stock price go down
	double n; // time interval
	double p; // prob of going up
	double q; // q=1-p
	complex<double> value;

	spotPrice0=50;
	iRate=0.1;
	yield=0;
	sigma=0.4;
	tOption=0.25;
	strikeP=70;
	n=100;

	int *pPointer; //dynamic price simulation array
	int i; // number of simulation
	cout<<"how many times of simulation would you like to do?"<<endl;
	cin>>i;
	pPointer=new(nothrow) int[i];

	if (pPointer== nullptr)
		cout<<"Error:memory could not be allocated";
	else
	{
		for (int j=0; j<i; j++)
		{
			srand(time(NULL)); //random seed
			double mean =0, std=1;
			double u, v; //uniform dist
			double x,y; // normal dist
	
			u=rand()/(double)RAND_MAX;
			v=rand()/(double)RAND_MAX;
			x=sqrt(-2*log(u))*cos(2 * M_PI * v);
			y=sqrt(-2*log(u))*sin(2 * M_PI * v) ;
	
			value= complex<double> (x,y);
			cout<<"in the for loop:"<<value<<endl;
			/*p[j]=spotPrice0
			p[j]=p[j]*exp()*/

		}
	}

	/*int *p;

	p=genNor();
	cout<<*(p)<<endl;*/

	//value[1]= x;
	//value[2]= y;
	//cout<<value[1]<<";"<<value[2]<<endl;
	cout<<value;
	cout<<"hello world"<<endl;
}















