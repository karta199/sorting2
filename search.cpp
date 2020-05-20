#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <map>
#include <unordered_map> 

using namespace std;

class chain_node{
	public:
		string s;
		chain_node *linkit;
		chain_node(){
			s="";
			linkit = NULL;
		}
		chain_node(string str){
			s = str;
			linkit = NULL;
		}
};

class hash_chain{
	public:
		chain_node *CN;
		long long prime;
		hash_chain(){
			prime = 54018521;
			//prime = 100;
			CN = new chain_node[prime];
		}
		hash_chain(double p){
			prime = p;
			CN = new chain_node[prime];
		}
		long long hashtable(string s){
			long long c = ((s[0]&0x10101)+1) * ((s[2]&0x11001)+1) * ((s[4]&0x10011)+1) * (s[2] + s[4]) * (((s[5] - s[3])^0x10111)+1) * (((s[3] - s[1])^0x11001)+1) * (pow((s[0] ^ s[1] ^ s[2] ^ s[3] ^ s[4] ^ s[5]), 3)+1);
			if(c<0)
				c*=-1;
			return c%prime;
		}
		void insert_node(string a){
			long long c = hashtable(a);
			if(CN[c].s==""){
				CN[c].s=a;
				CN[c].linkit = NULL;
			}
			else{
				chain_node *temp = &CN[c];
				chain_node *temp2 = new chain_node(a);
				while(temp->linkit!=NULL){
					temp = temp->linkit;
				}
				temp->linkit = temp2;
			}
		}
		int search_chain(string a){
			long long c = hashtable(a);
			if(CN[c].s==a){
				return 1;
			}
			else{
				chain_node *temp = CN[c].linkit;
				if(temp==NULL)
					return -1;
				while(temp!=NULL){
					if(temp->s==a)
						return 1;
					temp = temp->linkit;
				}
				return -1;
			}
		}
		int chain_print(){
			long long c=0;
			for(;c<prime ; c++){
				cout << "CN[" << c << "] is : " << CN[c].s << " ->  ";
				chain_node *temp = CN[c].linkit;
				while(temp!=NULL){
					cout <<  " ->  " << temp->s;
					temp = temp->linkit;
				}
				cout << endl;
			}
		}
		~hash_chain(){
			cout << endl << "Delete hash chain";
			long long c=0;
			for(;c<prime ; c++){
				while(CN[c].linkit!=NULL){
					chain_node *temp = CN[c].linkit , *temp2 = &CN[c];
					while(temp->linkit!=NULL){
						temp2 = temp;
						temp = temp->linkit;
					}
					delete temp;
					temp = NULL;
					temp2->linkit = NULL;
				}
			}
			delete []CN;
			CN = NULL;
			
		}
};

class bin_tree_node{
	public:
		string s;
		bin_tree_node *left , *right;
		bin_tree_node(){
			s = "";
			left = right = NULL;
		}
		bin_tree_node(string str){
			s = str;
			left = right = NULL;
		}
		void insert_node(string str){
			if(s==""){
				s = str;
				return;
			}
			bin_tree_node *temp = this;
			while(1){
				if(str>=temp->s){
					if(temp->right==NULL){
						bin_tree_node *temp2 = new bin_tree_node(str);
						temp->right = temp2;
						return;
					}
					else{
						temp = temp->right;
					}
				}
				else{
					if(temp->left==NULL){
						bin_tree_node *temp2 = new bin_tree_node(str);
						temp->left = temp2;
						return;
					}
					else{
						temp = temp->left;
					}
				}
			}
		}
		int search_key(string str){
			if(str==s)
				return 1;
			bin_tree_node *temp = this;
			while(temp!=NULL){
				if(str==temp->s)
					return 1;
				if(str>=temp->s){
					temp = temp->right;
				}
				else{
					temp = temp->left;
				}
			}
			return -1;
		}
};

int bin_search(string *a , int L , int R , string key){
	int mid = L + ((R-L)/2);
	
	if(L>R)
		return -1;
	
	if(key>a[mid]){
		return bin_search(a , mid+1 , R , key);
	}
	else if(key<a[mid]){
		return bin_search(a , L , mid-1 , key);
	}
	else{
		return 1;
	}
}

int iterative_bin_search(string *a , int L , int R , string key){
	int mid;
	
	while(L<=R){
		mid = L + ((R-L)/2);
		if(key>a[mid]){
			L = mid+1;
		}
		else if(key<a[mid]){
			R = mid-1;
		}
		else{
			return 1;
		}
	}
	
	return -1;
}

int main(){
	srand(time(0));
	int num[5] = {1000000 , 2000000 , 4000000 , 6000000 , 8000000};
	string *search = new string[10000000];
	clock_t start, stop;
	
	cout << "10000000  search data construct time :   ";
	start = clock();
	for(int j=0 ; j<10000000 ; j++){
		search[j] = "";
		
		for(int k=0 ; k<6 ; k++){
			search[j] += rand()%26+97;
		}
	}
	stop = clock();
	cout << double(stop - start)/CLOCKS_PER_SEC << endl;
	
	for(int i=0 ; i<5 ; i++){
		string c;
		string *arr = new string[num[i]] , *arr2 = new string[num[i]] ;
		hash_chain hc;
		bin_tree_node bt;
		map<string,char> Omap;
		map<string,char>::iterator it;
		unordered_map<string,char> Unomap;
		unordered_map<string,char>::iterator Unoit;
		double count_time = 0;
		int g;
		
		cout << endl << "  ---------------------" << num[i] << "   Data : -----------------------" << endl;
		
		start = clock();
		for(int j=0 ; j<num[i] ; j++){
			arr[j] = arr2[j] = "";
			
			for(int k=0 ; k<6 ; k++){
				arr2[j] = arr[j] += rand()%26+97;
			}
		}
		stop = clock();
		count_time += double(stop - start)/CLOCKS_PER_SEC;
		
		cout << endl << " " << num[i] << "   Ordered map data construct time : ";
		start = clock();
		for(int j=0 ; j<num[i] ; j++){
			Omap.insert(pair<string,char>(arr[j] , 0));
		}
		stop = clock();
		cout << count_time + (double(stop - start)/CLOCKS_PER_SEC) << endl;
		
		cout << endl << " " << num[i] << "   Unordered map data construct time : ";
		start = clock();
		for(int j=0 ; j<num[i] ; j++){
			Unomap.insert(pair<string,char>(arr[j] , 0));
		}
		stop = clock();
		cout << count_time + (double(stop - start)/CLOCKS_PER_SEC) << endl;
		
		cout << endl << " " << num[i] << "   Hash data construct time : ";
		start = clock();
		for(int j=0 ; j<num[i] ; j++){
			hc.insert_node(arr[j]);
		}
		stop = clock();
		cout << count_time + (double(stop - start)/CLOCKS_PER_SEC) << endl;
		
		cout << endl << " " << num[i] << "   Binary search tree data construct time : ";
		start = clock();
		for(int j=0 ; j<num[i] ; j++){
			bt.insert_node(arr[j]);
		}
		stop = clock();
		cout << count_time + (double(stop - start)/CLOCKS_PER_SEC) << endl;
		
		cout << endl << " " << num[i] << "  Binary data construct time : ";
		start = clock();
		sort(arr,arr+num[i]);
		stop = clock();
		cout << count_time + (double(stop - start)/CLOCKS_PER_SEC) << endl;
		
		cout << endl << " " << num[i] << "   Binary data construct time : ";
		start = clock();
		sort(arr2,arr2+num[i]);
		stop = clock();
		cout << count_time + (double(stop - start)/CLOCKS_PER_SEC) << endl;
		
		
		cout << endl << "  --------------- " << num[i] << "   Search time : -------------------" << endl;
		
		
		cout << endl << " " << num[i] << "   Recursive Binary Search time : ";
		start = clock();
		for(int j=0 ; j<10000000 ; j++){
			g=bin_search(arr,0,num[i]-1,search[j]);
		}
		stop = clock();
		cout << (double(stop - start)/CLOCKS_PER_SEC) << endl;
		
		cout << endl << " " << num[i] << "   iterative Binary Search time : ";
		start = clock();
		for(int j=0 ; j<10000000 ; j++){
			g=iterative_bin_search(arr,0,num[i]-1,search[j]);
		}
		stop = clock();
		cout << (double(stop - start)/CLOCKS_PER_SEC) << endl;
		
		cout << endl << " " << num[i] << "   Hash Table Search time : ";
		start = clock();
		for(int j=0 ; j<10000000 ; j++){
			g=hc.search_chain(search[j]);
		}
		stop = clock();
		cout << (double(stop - start)/CLOCKS_PER_SEC) << endl;
		
		cout << endl << " " << num[i] << "   Binary search Tree Search time : ";
		start = clock();
		for(int j=0 ; j<10000000 ; j++){
			g=bt.search_key(search[j]);
		}
		stop = clock();
		cout << (double(stop - start)/CLOCKS_PER_SEC) << endl;
		
		cout << endl << " " << num[i] << "   Ordered map Search time : ";
		start = clock();
		for(int j=0 ; j<10000000 ; j++){
			it = Omap.find(search[j]);
		}
		stop = clock();
		cout << (double(stop - start)/CLOCKS_PER_SEC) << endl;
		
		cout << endl << " " << num[i] << "   Unordered map Search time : ";
		start = clock();
		for(int j=0 ; j<10000000 ; j++){
			Unoit = Unomap.find(search[j]);
		}
		stop = clock();
		cout << (double(stop - start)/CLOCKS_PER_SEC) << endl;
		
	}
	return 0;
}
