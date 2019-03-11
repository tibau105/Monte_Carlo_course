#include<iostream>
#include<cmath>
#include<fstream>
#include<cstdlib>

using namespace std;

//------------------------------

void mean_variance(double* n, const int M, double& m, double& v);

int main(){
    
    srand(time(NULL));
    
    const int M = 100;
    const int N = 1000000;
    const int x = 6;
    int d1 = 0;
    int d2 = 0;
    //int n = 0;
    double m = 0.;
    double v = 0.;
    double n[M];
    
    for(int j=0; j<M; j++){
        n[j] = 0.;
        for(int i=0; i<N; i++){
            d1 = rand()%6+1;
            d2 = rand()%6+1;
        
            if(d1==6 && d2==6)
                n[j]++;
        }
        n[j]/= N;
    }    
    mean_variance(n,M,m,v);
    cout << "mean:" << "\t" << m << endl;
    cout << "std:" << "\t" << sqrt(v) << endl;
}


void mean_variance(double* n, const int M, double& m, double& v){
    
    for(int j=0; j<M; j++)
        m += n[j];
    m /= (double)M;
    
    for(int j=0; j<M; j++)
        v += (m - n[j])*(m - n[j]);
    v /= (double)M;
}
