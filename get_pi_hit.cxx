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
    double x,y;
    const double A = 1.;
    int k=0;
    
    for(int t=0; t<N; t++){
        x = (double)rand()/(double)RAND_MAX;
        y = (double)rand()/(double)RAND_MAX;
        if( y < integrand(x)) k++;
        
    }
    double I = (double)k/(double)N*A ;
    cout << I*4. << endl;
    cout << sqrt(I*(A-I)/N) << endl;
}



double integrand(const double x){
    return sqrt(1.-x*x);
}
