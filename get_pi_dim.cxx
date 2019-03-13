#include<iostream>
#include<cmath>
#include<fstream>
#include<cstdlib>

using namespace std;

//------------------------------
double integrand(const double* x,const int d);

int main(){
    srand(time(NULL));
    
    const int N = 1000000;
    const int d = 10;
    double x[d-1];
    const double a = 0.;
    const double b = 1.;
    const double h = 1.;
    const double A = (b-a)*h;
    double r = 1.;
    double f2 = 0.;
    double f[N];
    double I = 0.;
    double sigma = 0.;
    for(int t=0; t<N; t++){
        for(int i=0; i<d-1; i++){
            x[i] = (double)rand()/(double)RAND_MAX*r;
            r = r - x[i]*x[i];
        }
        f[t] = integrand(x,d);
    }
    
    for(int t=0; t<N; t++){
        f2 += f[t]*f[t];
        I += f[t];
    }
    sigma = (b-a)/(double)N*sqrt(f2-I*I/(double)N);
    
    I*=(b-a)/(double)N;
    
    cout << I*pow(2,d) << endl;
    cout << sigma << endl;
}

double integrand(const double* x,const int d){
    double I = 0.;
    for(int i=0;i<d-1;i++)
        I+=x[i]*x[i];
    return sqrt(1.-I);
}
