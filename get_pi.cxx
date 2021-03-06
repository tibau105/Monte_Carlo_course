#include<iostream>
#include<cmath>
#include<fstream>
#include<cstdlib>

using namespace std;

//------------------------------
double integrand(const double x);

int main(){
    srand(time(NULL));
    
    const int N = 1000000;
    double x;
    const double a = 0.;
    const double b = 1.;
    const double h = 1.;
    const double A = (b-a)*h;
    double f2 = 0.;
    double f[N];
    double I = 0.;
    double sigma = 0.;
    for(int t=0; t<N; t++){
        x = (double)rand()/(double)RAND_MAX*(b-a);
        f[t] = integrand(x);
    }
    
    for(int t=0; t<N; t++){
        f2 += f[t]*f[t];
        I += f[t];
    }
    sigma = (b-a)/(double)N*sqrt(f2-I*I/(double)N);
    
    I*=(b-a)/(double)N;
    
    cout << I*4. << endl;
    cout << sigma << endl;
}

double integrand(const double x){
    return sqrt(1.-x*x);
}
