#include<iostream>
#include<cmath>
#include<fstream>
#include<cstdlib>

using namespace std;

//------------------------------
void gaussian_sample(double& x, double& y, const double sigma);
int scat_man(const int N, const double E, const int Z, const double sigma);
//------------------------------

int main(){
    srand(time(NULL));
    
    const int N = 1000000;
    const int Z = 79;
    const double a_0 = 0.529177210e-10;
    const double sigma = a_0/100.;
   
    for(double E = 1.e5;E<1.e7;E+=1.e5)
        cout << E << "\t" << (double)scat_man(N,E,Z,sigma)/(double)N << endl;
    
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
//------------------------------
int scat_man(const int N, const double E, const int Z, const double sigma){
    
    const double eps_0 = 8.854187e-12;
    const double e = 1.602e-19;
    double b_0 = Z * e/(2*M_PI * eps_0 * E);

    double x,y,b;
    int n = 0;
    
    for(int i=0;i<N;i++){
        gaussian_sample(x,y,sigma);
        b =sqrt(x*x+y*y);
        if(b<b_0) n++;
    }
    
    return n;
}
