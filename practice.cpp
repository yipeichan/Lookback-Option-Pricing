#include<iostream>
#include<iomanip>
using namespace std;

unsigned long factorial(unsigned long);
unsigned long fibonacci(unsigned long number);

int main()
{
	for (int counter=0; counter<=10;counter++)
	{	cout<<setw(2)<<counter<<"!="<<factorial(counter)<<endl;
		//cout<<"fibonacci("<<counter<<")="<<fibonacci(counter)<<endl;
	//cout<<factorial(5);
	}
	for (int counter=0; counter<=10;counter++)
	{	//cout<<setw(2)<<counter<<"!="<<factorial(counter)<<endl;
		cout<<"fibonacci("<<counter<<")="<<fibonacci(counter)<<endl;
	//cout<<factorial(5);
	}

}

unsigned long factorial(unsigned long number)
{
	if(number<=1)
		return 1;
	else
		return number*factorial(number-1);
}

unsigned long fibonacci(unsigned long number)
{
	if((number==0)||(number==1))
		return number;
	else
		return fibonacci(number-1)+fibonacci(number-2);
}
