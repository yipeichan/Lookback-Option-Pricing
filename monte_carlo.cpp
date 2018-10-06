#include<iostream>
#include<iomanip>
#include <sstream>
#include<math.h> 
#include<stdlib.h> //srand, rand
#include<new>  //dynamic array
using namespace std;
double NormalCDFInverse(double p);  //to compute the inverse cumulative distribution function
double RationalApproximation(double t);  


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

	spotPrice0=50;
	iRate=0.1;
	yield=0;
	sigma=0.4;
	tOption=0.25;
	strikeP=70;
	n=100;


    // test the inverse CDF
	/*double test;
  	cout<<"enter a number:";
  	cin>>test;
  	cout<<NormalCDFInverse(test);*/

	int size;
	// Create an stockPrice array of n elements initialised to 0
	cout<<"how many times of simulation would you like to do?"<<endl;
	cin>>size;
    double* stockPrice=new double[size]; //dynamic price simulation array

	srand(13); //random seed
	for (int j=0; j<size; j++)
	{
		double u; //uniform dist
		double computed ;

		u=rand()/(double)RAND_MAX;
		computed = NormalCDFInverse(u);
		stockPrice[j]=computed;

		// for debug and verification
		cout<<"in the for loop, the uniformly dist. number="<<u<<endl
			<<"computed="<<computed<<endl
			<< "the normal r.v is :"<< "stockPricePtr["<<j<<"]="<<stockPrice[j]<<endl<<endl;

	}
 	
	cout<<"hello world"<<endl;
}

double RationalApproximation(double t)
{
    // Abramowitz and Stegun formula 26.2.23.
    // The absolute value of the error should be less than 4.5 e-4.
    double c[] = {2.515517, 0.802853, 0.010328};
    double d[] = {1.432788, 0.189269, 0.001308};
    return t - ((c[2]*t + c[1])*t + c[0]) / (((d[2]*t + d[1])*t + d[0])*t + 1.0);
}


double NormalCDFInverse(double p)
{
    if (p <= 0.0 || p >= 1.0)
    {
    	stringstream os;
        os << "Invalid input argument (" << p 
           << "); must be larger than 0 but less than 1.";
        throw invalid_argument( os.str() );
    }
 
    if (p < 0.5)
    {
        // F^-1(p) = - G^-1(p)
        return -RationalApproximation( sqrt(-2.0*log(p)) );
    }
    else
    {
        // F^-1(p) = G^-1(1-p)
        return RationalApproximation( sqrt(-2.0*log(1-p)) );
    }
}















