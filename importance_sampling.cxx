#include<iostream>
#include<cmath>
#include<fstream>
#include<cstdlib>

using namespace std;

//------------------------------

double g(const double x){return 1./(exp(x)+1.);}

double sample_x(const double z){return z*z;}

int main(){
    
    srand(time(NULL));
    
    const int N = 1000000;
    const double a = 0.; const double b = 0.;
    double I = 0.;
    const double int_w = 2.;
    double z,x;
    
    for(int i=0; i<N; i++){
        z = (double)rand()/(double)RAND_MAX;
        x = sample_x(z);
        I += g(x);
    }
    I*=int_w/(double) N;
    
    cout << I << endl;
}
