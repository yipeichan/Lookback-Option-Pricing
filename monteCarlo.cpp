
/*
	This program implements Monte Carlo simulation to price an European put
	Written by YI-PEI CHAN on 2016/4/26

*/
#include<iostream>
#include<iomanip>
#include <sstream>
#include<math.h> 
#include<stdlib.h> //srand, rand
#include<new>  //dynamic array
using namespace std;
double NormalCDFInverse(double p);  //to compute the inverse cumulative distribution function
double RationalApproximation(double t);  
double max(double value1, double value2);
double sd(double Array[], int size, double mean); //standard deviation


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
	//double q; // q=1-p

	spotPrice0=50;
	iRate=0.1;
	yield=0;
	sigma=0.4;
	tOption=0.25;
	strikeP=70;
	n=100;


	int size;
	// Create an stockPrice array of n elements initialised to 0
	cout<<"how many times of simulation would you like to do? (suggest 9999 times)"<<endl;
	cin>>size;
    	double* stockPrice=new double[size]; //dynamic price simulation array

    	double mean, standardDev,repPayoff;
    	repPayoff=30; //repetition of the numbers of payoff to average
    	double payoff[30];

	srand(13); //random seed

	double  average2=0;

	mean = (iRate-yield-sigma*sigma/2)*tOption/n;
	standardDev=sigma*sqrt(tOption/n);

	// Debug and verification
	/*cout<<"\nmean="<<mean<<endl
		<<"standardDev="<<standardDev<<endl;*/
	
	for(int j=0; j<repPayoff; j++) 
	{
		double average1=0;	

		for (int i=0; i<size; i++)
		{
			double u; //uniform dist
			double normInv, smax;
			smax=0;
			stockPrice[i]=spotPrice0;
			smax=max(spotPrice0,strikeP);

			for(int k =0; k<n; k++)		// stock price simulation
			{
				u=rand()/(double)RAND_MAX;
				normInv = NormalCDFInverse(u);
				normInv=normInv*standardDev-mean;				
				stockPrice[i]=stockPrice[i]*exp(normInv);
				smax=max(smax,stockPrice[i]);

				// Debug and verification
				/*cout<<"in the for loop, the uniformly dist. number="<<u<<endl
					  <<"normInv="<<normInv<<endl
					  << "stockPricePtr["<<i<<"]="<<stockPrice[i]<<endl<<endl;*/
			}
			//European lookback put
			stockPrice[i]=max(smax-stockPrice[i],0)*exp(-iRate*tOption);
			average1= average1+stockPrice[i];

			//cout<<"stockPrice[i]="<<stockPrice[i]<<endl<<endl;
		}
		// finding the average of the simulated payoffs
		payoff[j]=average1/size;
		if(j % 5 == 0)
			cout<<"simulated payoff="<<payoff[j]<<endl<<endl;
		average2=average2+payoff[j];

	}
	average2=average2/repPayoff;
	cout<<"------------------------------------------------------------------"<<endl
		<<"Price of the European lookback put = "<<average2<<endl
		<<"the standard deviation of the price of the European lookback put = "<<sd(payoff, repPayoff,  average2)<<endl
	    <<"the Upper endpoint of the 95% confidence interval of the price= "<< average2+2*sd(payoff, repPayoff,  average2)<<endl
	    <<"the Lower endpoint of the 95% confidence interval of the price= "<< average2-2*sd(payoff, repPayoff,  average2)<<endl;


}

double max(double value1, double value2)
{
	double maximumValue=value1;

	if(value2>value1)
		maximumValue=value2;

	return maximumValue;

}

double sd(double Array[], int size, double mean)
{
	double var, standardDev;

	for( int n = 0; n < size; n++ )
	{
  		var += (Array[n] - mean) * (Array[n] - mean);
	}
	var /= size;
	standardDev = sqrt(var);
	return standardDev;
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
 
    else if (p < 0.5)
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

















