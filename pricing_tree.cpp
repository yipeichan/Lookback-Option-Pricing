#include<iostream>
#include<iomanip>
#include <math.h>  
using namespace std;
//template <typename T> ;
//T eucall ();

int main()
{
	double spotPrice0; //stock price of t=0
	double iRate; // risk free rate
	double yield // yield income
	double sigma // volatility of the stock price
	double tOption // time to maturity of option
	double strikeP // strike price
	double up// stock price go up
	double down// stock price go down
	double Smax // S_{max,t}=max S_u
	double n // time interval
	double p // prob of going up
	double q // q=1-p


	spotPrice=50;
	iRate=0.1;
	yield=0;
	sigma=0.4;
	tOption=0.25;
	Smax=70;

	//stock price
	up=exp(sigma*pow((t/n),0.5))
	down=1/up

	p= (exp((r-q)*t/n)-d)/(up-down)
	q=1-p

	











}



/*unsigned long eucall()
{
	if(number<=1)
		return 1;
	else
		return number*factorial(number-1);
}*/



