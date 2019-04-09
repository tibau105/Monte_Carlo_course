#include<iostream>
#include<cmath>
#include<cstdlib>

using namespace std;
//------------------------------
class particle{ 
	//every particle has a velocity, position and is either absorbed or not absorbed
    public:
        double getx() const{return x;};
        double getv() const{return v;};
		bool getabsorb() const{return absorbed;};
        void setx(double xpos){x = xpos;};
        void setv(double veloc){v = veloc;};
        void move(const double dt, const double xwall, const double absorp);
		void initialize(const int Nx, const double xmin, const double xmax, const double vmax);
    private:
        double x, v;
		bool absorbed;
};
//------------------------------
int gridpos(const double x, const double xmin, const double xmax, const int Nx);
void countparticles(int* grid, particle* part, const int N, const int Nx, const double xmin, const double xmax);
void printgrid(const int* grid, const int Nx, const double t);
//------------------------------
int main(){   
    srand(time(NULL));

	//grid:
    const int Nx = 10;							//number of grid cells
    const double xmin = 0.;
    const double xmax = 10.;

	const int N = 1000; 						//number of particles
	const double vmax = 1.; 					//maximum absolute value of velocity
   	const double absorp=0.1; 					//rate of absorption

    const double dt = 1.; 						//timestep
    const double tmax = 10.; 					//length of timespan
    
    int grid[Nx+2]; 
	//count the number of particles for every cell 
	//aswell as the number of particles outside the grid (grid[Nx]) and of absorbed particles (grid[Nx+1])
	//initialize:
    for(int i=0;i<Nx+2;i++)
        grid[i]=0;
    
    particle part[N];
	//initialize position and velocity of each particle:
	for(int i=0;i<N;i++)
		part[i].initialize(Nx,xmin,xmax,vmax);	

	countparticles(grid,part,N,Nx,xmin,xmax); 	//fill array grid with numbers of particles 
    printgrid(grid,Nx,0.); 						//print out array grid
    
	//for each timestep: move particles, count the number of particles for each cell and print out result:
    for(double t=dt;t<tmax;t+=dt){
        for(int i=0;i<N;i++){
            part[i].move(dt,xmax,absorp);
        }
        countparticles(grid,part,N,Nx,xmin,xmax); 
        printgrid(grid,Nx,t);
    }
    return 0;   
}
//------------------------------
int gridpos(const double x, const double xmin, const double xmax, const int Nx, bool absorbed){	
	double w = (xmax-xmin)/(double)Nx; 			//width of one cell
	if(absorbed==true)
		return Nx+1; 							//index of number of absorped particles
	else{	
		if(x<xmin)
		    return Nx; 							//index of number of particles outside of the grid
		else
		    return floor(x/w);
	}
}
//------------------------------
void countparticles(int* grid, particle* part, const int N, const int Nx, const double xmin, const double xmax){  
	//reset array:    
	for(int i=0;i<Nx+2;i++)
        grid[i]=0;
	//count by considering every particle:
    for(int i=0;i<N;i++)
        grid[gridpos(part[i].getx(),xmin,xmax,Nx,part[i].getabsorb())]++;
	return;
}
//------------------------------
void printgrid(const int* grid, const int Nx, const double t){
    cout << "after time t=" << t << endl;
	//print out the number of particles in each cell
    for(int i=0; i<Nx;i++)
        cout << grid[i] << endl;
    cout << "number of particles outside the grid: " << grid[Nx] << endl;
	cout << "number of absorbed particles: " << grid[Nx+1] << endl;
    cout << "--------------" << endl;
	return;
}
//------------------------------
//member functions of the class particle:
void particle::initialize(const int Nx, const double xmin, const double xmax, const double vmax){
	absorbed = false;

	//initialize random velocity between -vmax and vmax:
	v = (double)rand()/(double)RAND_MAX*2.*vmax-vmax;

	//initialize random position in the middle of the grid:
	double w = (xmax-xmin)/(double)Nx; 			//width of one cell
	if(Nx%2==0)	//for even Nx:
		x = (double)rand()/(double)RAND_MAX*2.*w+((double)Nx/2.-1.)*w;
	else //for odd Nx:
		x = (double)rand()/(double)RAND_MAX*w+((double)(Nx-1)/2.)*w;
	return;
}
//------------------------------
void particle::move(const double dt, const double xwall,const double absorp){
	double dx = v*dt;

	//absorption:
	//note that in this implementation particles outside the grid can still be absorbed
	//to change this, set v=0. for particles with x<xmin
	double z = (double)rand()/(double)RAND_MAX;
	double l = -abs(v)/absorp*log(z); 			//sample l from exponential distribution
	if(abs(dx)>l) 								//absorption of particle if dx > mean free path l
		absorbed = true;

	//consider only movement of not absorbed particles:
	if(absorbed==false){   
		x += dx;
		//reflection of particle at xwall(=xmax):
		if(x>xwall){
			//d:=x-xwall=distance between wall and not reflected particle (outside the grid)
			//xwall-d=position of reflected particle (inside the grid)
		    x = 2.*xwall-x; 
		    v *= -1.;
		}
	}
	return;
}



