#include<iostream>
#include<cmath>
#include<cstdlib>

using namespace std;
//------------------------------
double radius(const double x, const double y);
double circle_quadrant(const double x); //alternative implementation
//------------------------------
int main(){
    srand(time(NULL));					//seed
    
    const int N = 1000000;				//number of samples
    double x,y;
    const double A = 1.;				//area of bounding rectangle
    int k = 0;							//number of "hits"
    
    for(int t=0; t<N; t++){
		//sample point in bounding rectangle:
        x = (double)rand()/(double)RAND_MAX;
        y = (double)rand()/(double)RAND_MAX;

		if(radius(x,y)<1) k++;			//hit
		//if(y<circle_quadrant(x)) k++;	//alternative condition
    }
    double I = (double)k/(double)N*A ; 	//integral value I=k*A/N

	//calculated value is the area of one quadrant of a circle with radius 1 (i.e. pi/4)
    cout << "calculated value for pi: " << I*4. << endl;				
	//standard deviation = sqrt(I*(A-I)/N)
    cout << "standard deviation: " << sqrt(I*(A-I)/(double)N) << endl;	
}
//------------------------------
double radius(const double x, const double y){
	//calculate the distance of the sampled point from the origin (radius in polar coordinates)
	return sqrt(x*x+y*y);
}
//------------------------------
double circle_quadrant(const double x){
	//the function describes the curvature of the first quadrant of a circle
    return sqrt(1.-x*x);
}

