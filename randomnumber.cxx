#include<iostream>
#include<cmath>
#include<fstream>

using namespace std;

//------------------------------

int main(){
    
    int N = 2000;
    int a = 1664525;
    long int c = 1013904223;
    long int m = 4294967296;

    long int x = 1;
    long int dx = 0;
    
   
    for(int i = 0; i < N; i++){
        dx = (a * x + c) % m;
        x = dx;
        cout << dx << endl;
    }
}
