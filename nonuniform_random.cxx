#include<iostream>
#include<cmath>
#include<fstream>
#include<cstdlib>

using namespace std;

//------------------------------


int main(){
    srand(time(NULL));
    
    const int N = 100000;
    const int dt = 1;
    //const int T = 1000;
    const double tau = 3.053 * 60.;
    double z = 0.;
    double x = 0.;
    double probab = 1 - pow(2,-(double)dt/tau);
    
    const double mu = log(2)/tau;
    
    for(int t=0; t<N; t++){
        z = (double)rand()/(double)RAND_MAX;
        x = - 1/mu * log(1-z);
        cout << x  << endl;
    }
  
}

