#include<iostream>
#include<cmath>
#include<fstream>
#include<cstdlib>

using namespace std;

//------------------------------
double radius(const double* x,const int d);

int main(){
    srand(time(NULL));
    
    const int N = 1000000;
    const int d = 10;
    double x[d];
    const double A = 1.;
    int k=0;
    
    for(int t=0; t<N; t++){
        for(int i=0; i<d; i++)
            x[i] = (double)rand()/(double)RAND_MAX;
        if(radius(x,d)<1) k++;
    }
    double I = (double)k/(double)N*A ;
    cout << I*pow(2,d) << endl;
    cout << sqrt(I*(A-I)/N) << endl;
}



double radius(const double* x,const int d){
    double r = 0.;
    for(int i=0; i<d; i++)
        r += x[i]*x[i];
    return r;
}
