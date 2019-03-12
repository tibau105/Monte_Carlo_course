#include<iostream>
#include<cmath>
#include<fstream>
#include<cstdlib>
#include<array>
#include <algorithm>

using namespace std;

//------------------------------


int main(){
    srand(time(NULL));
    
    const int N0 = 1000;
    const int dt = 1;
    const int T = 1000;
    const double tau = 3.053 * 60.;
    const double mu = log(2)/tau;
    double z;
    array<double,N0> t;
    
    for(int i=0; i<N0; i++){
        z = (double)rand()/(double)RAND_MAX;
        t[i] = -1./mu*log(1.-z);
    }
    
    sort(t.begin(),t.end());
    
    for(int i=0; i<N0; i++)
        cout << t[i] <<  "\t"  << N0-i << endl;
}

