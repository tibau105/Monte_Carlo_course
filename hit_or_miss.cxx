#include<iostream>
#include<cmath>
#include<fstream>
#include<cstdlib>

using namespace std;

//------------------------------
double integrand(const double x);

int main(){
    srand(time(NULL));
    
    const int N = 100000;
    double x,y;
    const double A = 2.;
    int k=0;
    const double cor = 1.4514;
    
    for(int t=0; t<N; t++){
        x = (double)rand()/(double)RAND_MAX*2.;
        y = (double)rand()/(double)RAND_MAX;
        if( y < integrand(x)) k++;
        
    }
    double I = (double)k/(double)N*A ;
    cout << I << endl;
    cout << sqrt(I*(A-I)/N) << endl;
}



double integrand(const double x){
    return sin(1./(2.*x-x*x))* sin(1./(2.*x-x*x));
}
