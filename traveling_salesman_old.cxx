#include<iostream>
#include<cmath>
#include<fstream>
#include<cstdlib>
#include <sstream>
#include <string>

using namespace std;

//------------------------------
void city_creator(const int N,double cities[][2],const double xmax,const double ymax);
double traveling_dist(const int N,const double cities[][2],const int* route);
void metropolis(const int N,const double cities[][2],int* route,const double T_0,const double T_min,const double tau,const double dt);
double probabilty(const int N,const double cities[][2],int* route,const int z1,const int z2,const double T);
void plot_route(const int N,const double cities[][2],int* route, const string name);
//------------------------------
int main(){
     srand(99);
     
     const int N = 25;      //cities
     const double T_0 = 10.;
     const double T_min = 1.e-3;
     const double tau = 1.e4;
     const double xmax = 40.; const double ymax = 40.;
     const double dt = 1.;
     
     double cities[N][2];
     city_creator(N,cities,xmax,ymax);
     
     //for(int i=0;i<N;i++)
       //cout << cities[i][0] << "\t" << cities[i][1] << endl;
     
     int route[N];
     
     for(int i=0;i<N;i++)
         route[i] = i;
     
     cout << "initial traveling distance: " << traveling_dist(N,cities,route) << endl;
    
     plot_route(N,cities,route,"begin.txt");
    
     srand(time(NULL));
     
     metropolis(N,cities,route,T_0,T_min,tau,dt);
     
     cout << "final traveling distance: " << traveling_dist(N,cities,route) << endl;
	 cout << "--------------------------------------" << endl;
     
     plot_route(N,cities,route,"end.txt");
     
     return 0;
}
//------------------------------
void city_creator(const int N,double cities[][2],const double xmax,const double ymax){
    for(int i=0;i<N;i++){
        cities[i][0] = (double)rand()/(double)RAND_MAX*xmax;
        cities[i][1] = (double)rand()/(double)RAND_MAX*ymax;
    }
}
//------------------------------
double traveling_dist(const int N,const double cities[][2],const int* route){
    double x,y;
    double D = 0.;
    for(int i=0;i<N-1;i++){
        x = cities[route[i]][0]-cities[route[i+1]][0];
        y = cities[route[i]][1]-cities[route[i+1]][1];
        D += sqrt(x*x+y*y);
    }
    x = cities[route[N-1]][0]-cities[route[0]][0];
    y = cities[route[N-1]][1]-cities[route[0]][1];
    D += sqrt(x*x+y*y);
    
    return D;
}
//------------------------------
void metropolis(const int N,const double cities[][2],int* route,const double T_0,const double T_min,const double tau,const double dt){
    stringstream strm;
    ofstream out("traveling_dist.txt");
    
    int z1,z2,z;
    int n_steps = 0;
    int n_changes = 0;
    double p,x;
    double D;
    double Dmin = traveling_dist(N,cities,route);
    for(double T=T_0;T>T_min;T*=exp(-dt/tau)){
        z1 = rand()%N;
        z2 = rand()%N;
        while(z2==z1)
            z2 = rand()%N;
        p = probabilty(N,cities,route,z1,z2,T);
        x = (double)rand()/(double)RAND_MAX;
        if(x<p){
            z = route[z1];
            route[z1] = route[z2];
            route[z2] = z;
            n_changes++;
            
            strm.str("");
            strm << "salesman//change_" << n_changes << ".txt";
            plot_route(N,cities,route,strm.str());
            
            out << traveling_dist(N,cities,route) << endl;
        }
        D = traveling_dist(N,cities,route);
        if(D<Dmin) Dmin = D; 
        n_steps++;
    }
    cout << "total number of steps: " << n_steps << endl;
    cout << "total number of changes: " << n_changes << endl;
    cout << "minimal (found) traveling distance: " << Dmin << endl;
    
    out.close();
}
//------------------------------
double probabilty(const int N,const double cities[][2],int* route,const int z1,const int z2,const double T){
    double D0,D1,dD;
    double p = 1.;
    D0 = traveling_dist(N,cities,route);
    int z = route[z1];
    route[z1] = route[z2];
    route[z2] = z;
    D1 = traveling_dist(N,cities,route);
    dD = D1-D0;
    if(dD>0) p = exp(-dD/T);
    z = route[z1];
    route[z1] = route[z2];
    route[z2] = z;
    
    return p;
}
//------------------------------
void plot_route(const int N,const double cities[][2],int* route, const string name){
    ofstream out(name.c_str());
    for(int i=0;i<N;i++)
        out << cities[route[i]][0] << "\t" << cities[route[i]][1] << endl;
    out << cities[route[0]][0] << "\t" << cities[route[0]][1] << endl;
    out.close(); 
}



