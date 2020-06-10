#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <cmath>

using namespace std;

int n[5] = {5 , 20 , 30 , 40 , 50};
int size;
long long M[51][51];
long long s[51][51];

long long RMC(int p[] , int i , int j){
	if(i==j)
		return 0;
	M[i][j] = 0x7FFFFFFFFFFFFFFF;
	for(int k=i ; k<j ; k++){
		long long q = RMC(p,i,k) + RMC(p,k+1,j) + (p[i-1]*p[k]*p[j]);
		if(q<M[i][j]){
			M[i][j] = q;
			s[i][j] = k;
		}
	}
	
	return M[i][j];
}
long long LC(int p[] , int i , int j){
	if(M[i][j]<0x7FFFFFFFFFFFFFFF)
		return M[i][j];
	if(i==j)
		M[i][j] = 0;
	else{
		for(int k=i ; k<j ; k++){
			long long q = LC(p , i, k) + LC(p , k+1 , j) + (p[i-1]*p[k]*p[j]);
			if(q<M[i][j]){
				M[i][j] = q;
				s[i][j] = k;
			}
		}
	}
	
	return M[i][j];
}

long long MMC(int p[]){
	for(int i=1 ; i<=n[size] ; i++){
		for(int j=1 ; j<=n[size] ; j++){
			M[i][j] = 0x7FFFFFFFFFFFFFFF;
		}
	}
	
	return LC(p,1,n[size]);
}

void MCO(int p[]){
	for(int i=1 ; i<=n[size] ; i++)
		M[i][i] = 0;
	for(int len=2 ; len<=n[size] ; len++){
		for(int i=1 ; i<=n[size]-len+1 ; i++){
			int j=i+len-1;
			M[i][j] = 0x7FFFFFFFFFFFFFFF;
			for(int k =i ; k<j ; k++){
				int q=M[i][k] + M[k+1][j] + (p[i-1]*p[k]*p[j]);
				if(q<M[i][j]){
					M[i][j] = q;
					s[i][j] = k;
				}
			}
		}
	}
}

void initialMS(){
	for(int i=0 ; i<51 ; i++){
		for(int j=0 ; j<51 ; j++){
			M[i][j] = s[i][j] = 0;
		}
	}
}

void POP(int i , int j){
	if(i==j)
		cout << "A" << i;
	else{
		cout << "(";
		POP(i , s[i][j]);
		POP(s[i][j]+1 , j);
		cout << ")";
	}
}

int main(){
	srand(time(0));
	clock_t start, stop;
	
	for(int i=0 ; i<1 ; i++){
		//int p[n[i]+1];
		int p[n[i]+1] = {5 , 2 , 4 , 3 , 10 , 2};
		size = i;
		
		cout << endl << endl << "     ========= " << n[i] <<  " =========    "  << endl << endl << " P :  " ;
		cout << endl << endl;
		for(int j=0 ; j<=n[i] ; j++){
			cout << p[j] << "  ";
		}
		cout << endl << endl;
		
		initialMS();
		
		MMC(p);
		
		cout << endl << "MMC : " << endl;
		for(int j=1 ; j<=n[i] ; j++){
			for(int k=1 ; k<=n[i] ; k++){
				cout << setw(5) << M[j][k] << " ";
			}
			cout << endl;
		}
		cout << endl << endl;
		for(int j=1 ; j<=n[i] ; j++){
			for(int k=1 ; k<=n[i] ; k++){
				cout << setw(5) << s[j][k] << " ";
			}
			cout << endl;
		}
		cout << endl;
		
		POP(1, n[i]);
		cout << endl;
		
		initialMS();
		
		MCO(p);
		
		cout << endl << "MCO : " << endl;
		for(int j=1 ; j<=n[i] ; j++){
			for(int k=1 ; k<=n[i] ; k++){
				cout << setw(5) << M[j][k] << " ";
			}
			cout << endl;
		}
		cout << endl << endl;
		for(int j=1 ; j<=n[i] ; j++){
			for(int k=1 ; k<=n[i] ; k++){
				cout << setw(5) << s[j][k] << " ";
			}
			cout << endl;
		}
		cout << endl;
		
		POP(1, n[i]);
		cout << endl;
		
		initialMS();
		
		RMC(p , 1 , n[i]);
		
		cout << endl << "RMC : " << endl;
		for(int j=1 ; j<=n[i] ; j++){
			for(int k=1 ; k<=n[i] ; k++){
				cout << setw(5) << M[j][k] << " ";
			}
			cout << endl;
		}
		cout << endl << endl;
		for(int j=1 ; j<=n[i] ; j++){
			for(int k=1 ; k<=n[i] ; k++){
				cout << setw(5) << s[j][k] << " ";
			}
			cout << endl;
		}
		cout << endl;
		
		
		POP(1, n[i]);
		cout << endl << endl;
	}
	return 0;
}
