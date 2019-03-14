#include<iostream>
#include<cmath>
#include<fstream>
#include<cstdlib>

using namespace std;

//------------------------------

int main(){
    
    srand(time(NULL));
    
    const int N = 1000;
    const int C0 = 10;
    const double p = 0.5;
    double z;
    int C[N];
    
    for(int i=0;i<N;i++)
        C[i] = 0;
    C[0] = C0;
    
    cout << C[0] << endl;
    for(int j=0; j<100;j++({ 
        for(int i=1; i<N; i++){
            z = (double)rand()/(double)RAND_MAX;
            if(z<p)
                C[i] = C[i-1]+1;
            else 
                C[i] = C[i-1]-1;
            //cout << C[i] << endl;
            if(C[i]==0){
              //cout << "stop by i=" << i << endl;
            break;
            }
        }
    }
}
