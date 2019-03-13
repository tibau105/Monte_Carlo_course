#include<iostream>
#include<cmath>
#include<fstream>

using namespace std;

//------------------------------

double rescale(long int N, const long int m, const double xmin, const double xmax);

int main(){
    
    int N = 1000;
    long int a = 567321;
    long int c = 10139045;
    long int m = 4294967296;

    long int x = 1;
    long int dx = 0;
    
   
    for(int i = 0; i < N; i++){
        dx = (a * x + c) % m;
        x = dx;
        cout << rescale(dx,m,-1.,1.) << endl;
        //cout << dx << endl;
    }
}

