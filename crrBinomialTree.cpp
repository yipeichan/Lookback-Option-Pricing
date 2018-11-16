/*
	This program implements CRR Binomial Tree model to price an European put
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
double sd(double Array[], int n, double mean); //standard deviation


static double stockPrice[100][100];
static double nosmax[100][100];
static double smax[100][100][100];
static double calput[100][100][100];



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
	double p; // prob of going up
	double q; // q=1-p

	spotPrice0=50;
	iRate=0.1;
	yield=0;
	sigma=0.4;
	tOption=0.25;
	strikeP=70;

	int n; // time interval

	// Create a stockPrice array of n elements initialised to 0
	cout<<"set number of intervals (suggest 100 times)"<<endl;
	cin>>n;


    /*//static double** stockPrice= new double*[n]; 
    for (int i=0; i<n;++i)		// 2d dynamic price simulation matrix
    {
    	stockPrice[i]=new double[n];
    }

    //static double** nosmax= new double*[n]; 
    for (int i=0; i<n;++i)		// 2d dynamic price simulation matrix
    {
    	nosmax[i]=new double[n];
    }

    //static double ***smax=new double**[n];  // 3d dynamic price simulation matrix
    for(int i =0; i<n;i++)
    {
    	smax[i]=new double*[n];
    	for(int j=0; j<n ;++j)
    	{
    		smax[i][j]=new double[n];
    	}
    } 

    //static double ***calput=new double**[n];  // 3d dynamic price simulation matrix
    for(int i =0; i<n;i++)
    {
    	calput[i]=new double*[n];
    	for(int j=0; j<n ;++j)
    	{
    		calput[i][j]=new double[n];
    	}
    } */

	up=exp(sigma*(sqrt(tOption/n)));
	down=1/up;
	p=(exp((iRate-yield)*tOption/n)-down)/(up-down);
	q=1-p;

	// Debug and verification
	/*cout<<"p="<<p
		<<"\nq="<<q
		<<"\nup="<<up
		<<"\ndown="<<down<<endl;*/

	stockPrice[0][0]=spotPrice0;
	for (int i =1; i<n;i++)
	{
		stockPrice[i][0]=stockPrice[i-1][0]*down;
		for(int j=1; j<i;j++)
		{
			stockPrice[i][j]=stockPrice[i-1][j-1]*up;
		}
	}

	smax[0][0][1]=max(strikeP, stockPrice[0][0]);
	calput[0][0][1]=smax[0][0][1]-stockPrice[0][0];
	nosmax[0][0]=1;


	//find smax
	for(int i=1; i<n;i++)
	{
		smax[i][0][1]=smax[0][0][1];
		calput[i][0][1]=smax[0][0][1]-stockPrice[i][0];
		nosmax[i][0]=1;
		smax[i][i][1]=max(stockPrice[i][i],smax[0][0][1]);
		calput[i][i][1]=smax[i][i][1]-stockPrice[i][i];
		nosmax[i][i]=1;

	}

	for(int i=2;i<n;i++)
	{
		for(int j=1; j<i;j++)
		{
			int m=1;
			int ui=1;
			int di=1;
			double temp;
			temp=stockPrice[i][j];
			//double temp2;
			//temp2=nosmax[i-1][j-1];
			for(int k=1 ; k<nosmax[i-1][j-1];k++)
			{
				if((smax[i-1][j-1][ui]>=stockPrice[i][j])||((smax[i-1][j-1][ui]-stockPrice[i][j]<0.00001)&&(smax[i-1][j-1][ui]-stockPrice[i][j]>-0.00001)))
					break;
				else
				{
					if(smax[i-1][j-1][ui]<stockPrice[i][j])
					{
						if(smax[i-1][j-1][ui]==0)
							break;
						else
							ui=ui+1;
					}
					else
						break;
				}
			}

			for(int k=1 ; k<nosmax[i-1][j];k++)
			{
				if((smax[i-1][j][di]>=stockPrice[i][j])||((smax[i-1][j-1][di]-stockPrice[i][j]<0.00001)&&(smax[i-1][j-1][di]-stockPrice[i][j]>-0.00001)))
					break;
				else
				{
					if(smax[i-1][j-1][di]<stockPrice[i][j])
					{
						if(smax[i-1][j-1][di]==0)
							break;
						else
							di=di+1;

					}
					else
						break;
				}
			}

			// to derive smax

			for(int k=1 ; nosmax[i-1][j-1]+nosmax[i-1][j];k++)
			{
				if(smax[i-1][j-1][ui]<=smax[i-1][j][di])
				{
					if(smax[i-1][j-1][ui]==0)
					{
						if(smax[i-1][j-1][di]==0)
							continue;		///////////////// careful
						else
						{
							if(smax[i-1][j][di]==smax[i][j][m-1])
								di=di+1;
							else
							{
								smax[i][j][m]=smax[i-1][j][di];
								calput[i][j][m]=max(smax[i][j][m]-stockPrice[i][j],0);
								m=m+1;
								di=di+1;

							}
						}

					}
					else
					{
						if(smax[i-1][j-1][ui]==smax[i][j][m-1])
							ui=ui+1;
						else
						{
							smax[i][j][m]=smax[i-1][j-1][ui];
							calput[i][j][m]=max(smax[i][j][m]-stockPrice[i][j],0);
							m=m+1;
							ui=ui+1;

						}
					}
				}
				else
				{
					if(smax[i-1][j][di]==0)
					{
						if(smax[i-1][j-1][ui]==0)
							continue;
						else
						{
							if(smax[i][j][m]==smax[i][j][m-1])
								ui=ui+1;
							else
							{
								smax[i][j][m]=smax[i-1][j-1][ui];
								calput[i][j][m]=max(smax[i][j][m]-stockPrice[i][j],0);
								m=m+1;
								ui=ui+1;
							}
						}	
					}
					else
					{
						if(smax[i-1][j][di]==smax[i][j][m-1])
							di=di+1;
						else
						{
							smax[i][j][m]=smax[i-1][j][di];
							calput[i][j][m]=max(smax[i][j][m]-stockPrice[i][j],0);
							m=m+1;
							di=di+1;
						}
					}

				}

			}
			nosmax[i][j]=m-1;
		}
	}


for(int i=n-1; i<-1;i--)
{
	for(int j=i; j<-1;j--)
	{
		for(int k=1; k<nosmax[i][j];k++)
		{
			double rhs=0;
			double lhs=0;
			for(int uindex=1; uindex<nosmax[i+1][j+1];uindex++)
			{
				if((smax[i][j][k]<=smax[i+1][j+1][uindex])||((smax[i][j][k]-smax[i+1][j][uindex]<0.0001)&&(smax[i][j][k]-smax[i+1][j][uindex]>-0.0001)))
					rhs=calput[i+1][j][uindex];

			}
			for(int dindex=1; dindex<nosmax[i+1][j];dindex++)
			{
				if((smax[i][j][k]<=smax[i+1][j+1][dindex])||((smax[i][j][k]-smax[i+1][j][dindex]<0.0001)&&(smax[i][j][k]-smax[i+1][j][dindex]>-0.0001)))
					lhs=calput[i+1][j][dindex];

			}	
			calput[i][j][k]=max((p*rhs+(1-p)*lhs)*exp(-iRate*tOption/n),calput[i][j][k]);
		}
	}
}

cout<<"price of the European put = "<<calput[0][0][1];


}



double max(double value1, double value2)
{
	double maximumValue=value1;

	if(value2>value1)
		maximumValue=value2;

	return maximumValue;

}

