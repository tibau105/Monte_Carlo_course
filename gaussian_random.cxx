#include<iostream>
#include<cmath>
#include<fstream>
#include<cstdlib>

using namespace std;

//------------------------------
void gaussian_sample(double& x, double& y, const double sigma);
//------------------------------

int main(){
    srand(time(NULL));
    
    const int N = 100000;
    const double sigma = 1.;
    double x,y;
    
    for(int i=0;i<N;i++){
        gaussian_sample(x,y,sigma);
        cout << x << "\t" << y << endl;
    }
}
//------------------------------
void gaussian_sample(double& x, double& y, const double sigma){
    double r,theta,z;
    
    z = (double)rand()/(double) RAND_MAX;
    theta = 2 * M_PI * z;
    z = (double)rand()/(double) RAND_MAX;
    r = sqrt(-2 * sigma * sigma * log(1-z));
    x = r * cos(theta);
    y = r * sin(theta);
}

