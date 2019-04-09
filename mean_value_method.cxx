#include<iostream>
#include<cmath>
#include<cstdlib>

using namespace std;

//------------------------------
double integrand(const double x){return sin(1./(2.*x-x*x))* sin(1./(2.*x-x*x));} //integrand of integral
//------------------------------
int main(){
    srand(time(NULL));									//seed
    
    const int N = 100000;								//number of samples
    double x;
	//considered intervall:
    const double a = 0.;
    const double b = 2.;

    const double correct_value = 1.4514;
    double f[N];										//array for function values
    double I;											//integral value
	double f1 = 0.;										//sum of function values
	double f2 = 0.;										//sum of squared function values
    double sigma = 0.;									//standard derivation

    for(int t=0; t<N; t++){
        x = (double)rand()/(double)RAND_MAX*(b-a)+a;	//sample random number uniformly between a and b	
        f[t] = integrand(x);							//evaluate integrand at sampled position
    }

	//approximate integral I:
	//average over all calculated function values * size of intervall:
    for(int t=0; t<N; t++)
		f1 += f[t];
	
    I = (b-a)/(double)N*f1;		

	//calculate standard derivation sigma:
	for(int t=0; t<N; t++)
		f2 += f[t]*f[t];

	//sigma = (b-a)/N*sqrt(N*var(f)) where var(f) = <f^2> - <f>^2 is variance of single random number
    sigma = (b-a)/(double)N*sqrt(f2-f1*f1/(double)N); 
        
    cout << "calculated value for integral: " << I << endl;
	//cout << "correct value of the integral: " << correct_value << endl;
    cout << "standard derivation: " << sigma << endl;

	return 0;
}


