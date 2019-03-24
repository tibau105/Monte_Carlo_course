#include<iostream>
#include<cmath>
#include<fstream>
#include<cstdlib>
#include <sstream>
#include <string>

using namespace std;

class city{ //every city has a x and y position. alternative implementation: multidimensional arrays
	public:
		void setx(double xpos){x=xpos;};
		void sety(double ypos){y=ypos;};
		double getx(){return x;}; 
		double gety(){return y;};
	private:
		double x, y;
};
//------------------------------
void city_creator(const int N,city* cities,const double xmax,const double ymax);
double traveling_dist(const int N,city* cities,const int* route);
void metropolis(const int N,city* cities,int* route,const double T_0,const double T_min,const double tau,const double dt);
double probabilty(const int N,city* cities,int* route,const int i1,const int i2,const double T);
void plot_route(const int N,city* cities,int* route, const string name);
void create_gnuplotscript(int n_changes);
//------------------------------

int main(){
	 //seed for the positions of the cities
     srand(99); //for N=25: best result found: 157.733 
     
     const int N = 25; //number of cities
     const double xmax = 40.; const double ymax = 40.;
     //simulated annealing:
	 const double T_0 = 10.; //annealing parameter
	 //const double T_0 = 100.; //larger value improves results just slightly
     const double T_min = 1.e-3;
     const double tau = 1.e4; //cooling time
	 //const double tau = 1.e5; //larger cooling time yields better results more often but increases computing time
     const double dt = 1.; //time steps
     
     city cities[N];
     city_creator(N,cities,xmax,ymax); //create N cities with random positions in [0,xmax] x [0,ymax]
     
     int route[N];
     
	 //initialize with route: 1,2,...,N
     for(int i=0;i<N;i++)
         route[i] = i;
     
     cout << "initial traveling distance: " << traveling_dist(N,cities,route) << endl;
    
     plot_route(N,cities,route,"begin.txt");
    
	 //seed for the sampling in the algorithm
     srand(time(NULL)); 
     
     metropolis(N,cities,route,T_0,T_min,tau,dt);
     
     cout << "final traveling distance: " << traveling_dist(N,cities,route) << endl;
	 cout << "--------------------------------------" << endl;
     
     plot_route(N,cities,route,"end.txt");
     
     return 0;
}
//------------------------------
void city_creator(const int N,city* cities,const double xmax,const double ymax){
	//create N cities with random positions in [0,xmax] x [0,ymax]
    for(int i=0;i<N;i++){
        cities[i].setx((double)rand()/(double)RAND_MAX*xmax);
        cities[i].sety((double)rand()/(double)RAND_MAX*ymax);
    }
	return;
}
//------------------------------
double traveling_dist(const int N,city* cities,const int* route){
	//calculate the traveling distance for a given route
    double x,y;
    double D = 0.;
    for(int i=0;i<N-1;i++){
        x = cities[route[i]].getx()-cities[route[i+1]].getx();
        y = cities[route[i]].gety()-cities[route[i+1]].gety();
        D += sqrt(x*x+y*y);
    }
    x = cities[route[N-1]].getx()-cities[route[0]].getx();
    y = cities[route[N-1]].gety()-cities[route[0]].gety();
    D += sqrt(x*x+y*y);
    
    return D;
}
//------------------------------
void metropolis(const int N,city* cities,int* route,const double T_0,const double T_min,const double tau,const double dt){
    stringstream strm;
    ofstream out("traveling_dist.txt");
    
    int i1,i2,i;
    int n_steps = 0; //number of steps
    int n_changes = 0; //number of changes of the route
    double p,x;
    double D;
    double Dmin = traveling_dist(N,cities,route);

	//simulated annealing: T = exp(-t/tau)
    for(double T=T_0;T>T_min;T*=exp(-dt/tau)){ 
		//pick two random (different) cities
        i1 = rand()%N;
        i2 = rand()%N;
        while(i2==i1)
            i2 = rand()%N;
		//sample probabilty
        p = probabilty(N,cities,route,i1,i2,T);
        x = (double)rand()/(double)RAND_MAX;
        if(x<p){
			//switch positions of cities in the route with probabilty p 
            i = route[i1];
            route[i1] = route[i2];
            route[i2] = i;
            n_changes++;
            
            strm.str("");
            strm << "salesman//change_" << n_changes << ".txt"; //save changed route 
			//WARNING: following line increases computing time 
			//and creates a large number of files (for the animation of the algorithm) 
			//(if the directory with the name "salesman" exists)
            plot_route(N,cities,route,strm.str());            
            out << traveling_dist(N,cities,route) << endl; //write new traveling distance to file
        }
        D = traveling_dist(N,cities,route);
        if(D<Dmin) Dmin = D; //Dmin is the smallest found traveling distance (not necessarily the final route)
        n_steps++;
    }
    cout << "total number of steps: " << n_steps << endl;
    cout << "total number of changes: " << n_changes << endl;
    cout << "minimal (found) traveling distance: " << Dmin << endl;
    
    out.close();

	create_gnuplotscript(n_changes); 

	return;
}
//------------------------------
double probabilty(const int N,city* cities,int* route,const int i1,const int i2,const double T){
    double D0,D1,dD;
    double p = 1.;

    D0 = traveling_dist(N,cities,route); //initial traveling distance 

    //switch positions of cities in the route
	int i = route[i1];
    route[i1] = route[i2];
    route[i2] = i;
    D1 = traveling_dist(N,cities,route); //traveling distance after switching
    dD = D1-D0;

	//if switching increases traveling distance, set probabilty to p to exp(...)
	//otherwise: p=1
    if(dD>0) p = exp(-dD/T);
	
    //switch back to initial route (since sampling takes place in the function "metropolis")
	i = route[i1];
    route[i1] = route[i2];
    route[i2] = i;
    
    return p;
}
//------------------------------
void plot_route(const int N,city* cities,int* route, const string name){
    ofstream out(name.c_str());
    for(int i=0;i<N;i++)
        out << cities[route[i]].getx() << "\t" << cities[route[i]].gety() << endl;
    out << cities[route[0]].getx() << "\t" << cities[route[0]].gety() << endl; //for "closed" route
    out.close(); 	
	return;
}
//------------------------------
void create_gnuplotscript(int n_changes){
	//write gnuplotscript for animation and plot of traveling distance
	//execute with command: gnuplot "plot_traveling_salesman.gp"
	ofstream out("plot_traveling_salesman.gp");
	out << "set terminal qt 0" << endl;
	out << "plot \"traveling_dist.txt\" w l" << endl;

	out << "set terminal qt 1" << endl;\
	out << "do for[i=1:" << n_changes << "]{plot \"salesman/change_\".i.\".txt\" w linespoints title \"change \".i; pause 0.08;}" << endl;
	out << "pause -1" << endl;
	out.close();
}
//------------------------------


