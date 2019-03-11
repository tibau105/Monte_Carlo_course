#include<iostream>
#include<cmath>
#include<fstream>
#include<cstdlib>

using namespace std;

//------------------------------


int main(){
    srand(time(NULL));
    
    int N0 = 1000;
    const int dt = 1;
    const int T = 1000;
    const double tau = 3.053 * 60.;
    int N = N0;
    double p = 0.;
    double probab = 1 - pow(2,-(double)dt/tau);
    
    ofstream out("decay_10.txt");
    
    for(int t=0; t<T; t+=dt){
       for(int n=0; n<N0; n++){
           p = (double)rand()/(double)RAND_MAX;
           if(p<probab)
               N--;
       }
       N0 = N;
       out << t << "\t" << N0 << endl;
    }
    out.close();
}

