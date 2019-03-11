#include<iostream>
#include<cmath>
#include<fstream>
#include<cstdlib>

using namespace std;

//------------------------------

int main(){
    
    srand(time(NULL));
    
    const int N = 10000;
    double p = 0.;
    int head = 0;
    
    for(int i=0; i<N; i++){
        p = (double)rand()/(double)RAND_MAX;
        if(p<0.8)
            head++;
    }
    cout << (double)head/(double)N << endl;
}
