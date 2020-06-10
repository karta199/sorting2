#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <cmath>

using namespace std;

int n[5] = {5 , 20 , 30 , 40 , 50};
int size;
double e[52][51];
double w[52][51];
double root[51][51];

void OBST(double q[] , double p[] , int n){
	for(int i=1 ; i<=n+1 ; i++){
		for(int j=0 ; j<=n ; j++){
			e[i][j] = w[i][j] = 0;
		}
	}
	for(int i=1 ; i<=n ; i++){
		for(int j=1 ; j<=n ; j++){
			root[i][j] = 0;
		}
	}
	
	for(int i=1 ; i<=n+1 ; i++){
		e[i][i-1] = q[i-1];
		w[i][i-1] = q[i-1];
	}
	
	for(int len = 1 ; len<=n ; len++){
		for(int i=1 ; i<=n - len +1 ; i++){
			int j = i+len-1;
			e[i][j] = 0x7FFFFFFFFFFFFFFF;
			w[i][j] = w[i][j-1] + p[j] + q[j];
			
			for(int r=i ; r<=j ; r++){
				double t = e[i][r-1] + e[r+1][j] + w[i][j];
				if(t<e[i][j]){
					e[i][j] = t;
					root[i][j] = r;
				}
			}
		}
	}
	
}

void initialMS(){
	for(int i=0 ; i<52 ; i++){
		for(int j=0 ; j<52 ; j++){
			w[i][j] = e[i][j] = 0;
		}
	}
}

int main(){
	srand(time(0));
	clock_t start, stop;
	
	for(int i=0 ; i<1 ; i++){
		double p[n[i]+1] = {0,0.05,0.15,0.05,0.2,0.1} , q[n[i]+1] = {0.05,0.1,0.05,0.05,0.1,0.1} ;
		int count = 100000 , num[(2*n[i])+1];
		size = i;
		
		cout << endl << endl;
		
		initialMS();
		
		OBST(q , p , n[i]);
		
		for(int j=1 ; j<=n[i]+1 ; j++){
			for(int k=0 ; k<=n[i] ; k++){
				cout << setw(8) << e[j][k] << " ";
			}
			cout << endl;
		}
		cout << endl << endl;
		for(int j=1 ; j<=n[i]+1 ; j++){
			for(int k=0 ; k<=n[i] ; k++){
				cout << setw(8) << w[j][k] << " ";
			}
			cout << endl;
		}
		cout << endl << endl;
		for(int j=1 ; j<=n[i] ; j++){
			for(int k=1 ; k<=n[i] ; k++){
				cout << setw(8) << root[j][k] << " ";
			}
			cout << endl;
		}
		cout << endl << endl;
		
	}
	return 0;
}
