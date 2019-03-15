#include<iostream>
#include<cmath>
#include<fstream>
#include<cstdlib>
//#include <sstream>
//#include <string>

using namespace std;
//------------------------------
class particle{
    public:
        particle(double x, double v){this->x=x;this->v=v;};
        particle();
        double getx() const{return x;};
        double getv() const{return v;};
        void setx(double xpos){x = xpos;};
        void setv(double veloc){v = veloc;};
        void move(const double dt,const double xwall,const double absorp);
    private:
        double x, v;
};
//------------------------------
int gridpos(const double x, const double xmin, const double xmax, const int Nx);
void countparticles(int* grid, particle* part, const int N, const int Nx, const double xmin, const double xmax);
void printgrid(const int* grid, const int Nx, const double t);
//------------------------------
int main(){
    
    srand(time(NULL));
    const int Nx = 10;
    const double xmin = 0.;
    const double xmax = 10.;
    const int N = 1000;
    const double dt = 1.;
    const double tmax = 10.;
    const double absorp=0.1;
    
    int grid[Nx+1];
    for(int i=0;i<Nx+1;i++)
        grid[i]=0;
    
    particle part[N];
    //part[0].setv(10.);
    //cout << part[2].getv() << endl;
    countparticles(grid,part,N,Nx,xmin,xmax);
    printgrid(grid,Nx,0.);
    
    for(double t=0.;t<tmax;t+=dt){
        for(int i=0;i<N;i++){
            part[i].move(dt,xmax,absorp);
        }
        countparticles(grid,part,N,Nx,xmin,xmax);
        printgrid(grid,Nx,t);
    }
    return 0;   
}
//------------------------------
int gridpos(const double x, const double xmin, const double xmax, const int Nx){
    if(x<xmin || x>xmax)
        return Nx;
    else
        return floor(x);
}
//------------------------------
void countparticles(int* grid, particle* part, const int N, const int Nx, const double xmin, const double xmax){   
    for(int i=0;i<Nx+1;i++)
        grid[i]=0;
    for(int i=0;i<N;i++)
        grid[gridpos(part[i].getx(),xmin,xmax,Nx)]++;
}
//------------------------------
particle::particle(){
    x = (double)rand()/(double)RAND_MAX*2.+3.;
    double vmax = 1.;
    v = (double)rand()/(double)RAND_MAX*2.*vmax-vmax;
    
}
//------------------------------
void particle::move(const double dt, const double xwall,const double absorp){
    x += v*dt;
    if(x>xwall){
        x = 2.*xwall-x;
        v *= -1.;
    }
    
}
//------------------------------
void printgrid(const int* grid, const int Nx, const double t){
    cout << "after time t=" << t << endl;
    for(int i=0; i<Nx;i++)
        cout << grid[i] << endl;
    cout << "number of particles outside the grid: " << grid[Nx] << endl;
    cout << "--------------" << endl;
}
