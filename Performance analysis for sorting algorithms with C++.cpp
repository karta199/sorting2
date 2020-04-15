#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <iomanip>

using namespace std;

void max_heapify(string arr[], int end , int size) {
    int left = end*2;
    int righ = end*2+1;
    int lar=end;
    if(left<=size && arr[left-1]>arr[end-1]){
    	lar = left;
	}
	else{
		lar = end;
	}
	if(righ<=size && arr[righ-1] > arr[lar-1]){
		lar = righ;
	}
	if(lar!=end){
		swap(arr[end-1],arr[lar-1]);
		max_heapify(arr,lar,size);
	}
}

void build_max_heap(string a[]  , int size){
	for(int i=size/2 ; i>=1 ; i--){
		max_heapify(a,i , size);
	}
}

void heap_sort(string arr[] , int size) {
	build_max_heap(arr ,size);
	for(int j = size ; j>=2 ; j--){
		swap(arr[0] , arr[j-1]);
		size--;
		max_heapify(arr,1 , size);
	}
}

void merge(string *a , string *c , int L , int R){
	if(L>=R){
		return;
	}
	int mid = (L+R)/2;
	merge(a , c , L , mid);
	merge(a , c , mid+1 , R);
	
	for(int i=L ; i <= R ; i++){
		c[i]  = a[i];
	}
	int li = L,ri = mid+1 , i=L;
	
	while(li<=mid && ri <=R){
		if(c[li]<c[ri]){
			a[i] = c[li];
			i++;
			li++;
		}
		else{
			a[i] = c[ri];
			i++;
			ri++;
		}
	}
	
	if(li>mid){
		while(i<=R){
			a[i] = c[ri];
			ri++;
			i++;
		}
	}
	
	if(ri>R){
		while(i<=R){
			a[i] = c[li];
			i++;
			li++;
		}
	}
	
}

void iterative_merge(string *a , int L , int R){
	string *b = new string[R+1];
	
	for(int i=0 ; i<=R ; i++){
		b[i] = a[i];
	}
	
	for(int i=1 ; i<=R ; i+=i){
		for(int j=0 ; j<=R ; j  = j + (2 * i)){
			int k = j+(2*i) - 1;
			int mid = (k+j)/2;
			int ll = j , rr = mid+1;
			
			if(rr>R)
			break;
			for(int temp = j ; temp<=k && temp<=R ; temp++){
				if(ll>mid){
					while( temp<=k && temp<=R){
						b[temp] = a[rr];
						rr++;
						temp++;
					}
					break;
				}
				
				if(rr>k || rr>R){
					while( temp<=k && temp<=R){
						b[temp] = a[ll];
						ll++;
						temp++;
					}
					break;
				}
				
				if(a[ll] < a[rr]){
					b[temp] = a[ll];
					ll++;
				}
				else{
					b[temp] = a[rr];
					rr++;
				}
				
			}
			
			for(int temp = j ; temp<=k && temp<=R ; temp++){
				a[temp] = b[temp];
			}
		}
	}
}

int partion(string *a , int L , int R){
	int i=L;
	for(int j=i ; j<R ; j++){
		if(a[j]<a[R]){
			swap(a[i] , a[j]);
			i++;
		}
	}
	swap(a[i],a[R]);
	
	return i;
}

void quick(string *a , int L , int R){
	if(L<R){
		int q;
		q = partion(a,L,R);
		quick(a , L , q-1);
		quick(a , q+1 , R);
		
	}
}

void iterative_quick(string *a , int L , int R){
	
	int *stack = new int[R-L+1];
	int count=0 , q , Left , Right;
	stack[count] = L;
	stack[count+1] = R;
	count++;;
	
	while(count>=0){	
		Right = stack[count];
		Left = stack[count-1];
		count-=2;
		
		q = partion(a,Left,Right);
		
		if(q - Left>1){
			count++;
			stack[count] = Left;
			stack[count+1] = q-1;
			count++;
		}
		
		if(Right - q > 1){
			count++;
			stack[count] = q+1;
			stack[count+1] = Right;
			count++;
			
		}
		
	}
}

void Select_sort(string *arr , int len){
	int min;
	
	for(int j=0 ; j<len - 1 ; j++){
		min = j;
		for(int k=j+1 ; k<len ; k++){
			if(arr[min]>arr[k]){
				min = k;
			}
		}
		swap(arr[j] , arr[min]);
	}
}

void Insertion_sort(string *arr , int len){
	for(int j=1 ; j<len ; j++){
		for(int k=j ; k>0 ; k--){
			if(arr[k]<arr[k-1]){
				swap(arr[k-1],arr[k]);
			}
			else
			break;
		}
	}
}

void Bubble_sort(string *arr , int len){
	for(int i=0 ; i<len-1 ; i++){
		for(int j=len-1 ; j>i ; j--){
			if(arr[j]<arr[j-1]){
				swap(arr[j] , arr[j-1]);
			}
		}
	}
}

int main() {
	srand(time(0));
	
    int size[6] ={10,20,40,60,80,100} , size2[5] = {2000000 , 4000000 , 6000000 , 8000000 , 10000000};
    string *arr , *arr2 , *arr3;
    clock_t start,stop,start2,stop2,start3,stop3;
    double tempt=0;
    
	start3 = clock();
    for(int i=0 ; i<6 ; i++){
    	arr = new string[size[i]];
    	arr2 = new string[size[i]];
    	arr3 = new string[size[i]];
	    
		cout << "----------------------   " << size[i] << "   ----------------------";
	    start2 = clock();
	    
	    
	    start = clock();
	    for(int j=0 ; j<size[i];  j++){
	    	arr[j]="";
	    	for(int k=0 ; k<6 ; k++){
	    		arr[j]+=rand()%26+97;
			}
			arr2[j] = arr[j];
		}
	    stop = clock();
	    cout << endl << "array " << size[i] << " create time : " << double(stop - start) / CLOCKS_PER_SEC << " sec" <<endl; 
		
		
		tempt=0;
		cout << "Select sort time : ";
		for(int y=0 ; y<10000 ; y++){
		    for(int j=0 ; j<size[i];  j++){
		    	arr[j]=arr2[j];
			}
			start = clock();
		    Select_sort(arr ,size[i]);
		    stop = clock();
		    tempt += double(stop - start) / CLOCKS_PER_SEC;
		}
	    cout << tempt << " sec" <<endl; 
		
		tempt=0;
		cout << "Insertion  sort time : ";
		for(int y=0 ; y<10000 ; y++){
		    for(int j=0 ; j<size[i];  j++){
		    	arr[j]=arr2[j];
			}
		    start = clock();
		    Insertion_sort(arr , size[i]);
		    stop = clock();
		    tempt += double(stop - start) / CLOCKS_PER_SEC;
		}
	    cout << tempt << " sec" <<endl; 
		
		tempt=0;
		cout << "Bubble sort time : ";
		for(int y=0 ; y<10000 ; y++){
		    for(int j=0 ; j<size[i];  j++){
		    	arr[j]=arr2[j];
			}
		    start = clock();
		    Bubble_sort(arr , size[i]);
		    stop = clock();
		    tempt += double(stop - start) / CLOCKS_PER_SEC;
		}
	    cout << tempt << " sec" <<endl; 
		
		tempt=0;
		cout << "heap sort time : ";
		for(int y=0 ; y<10000 ; y++){
		    for(int j=0 ; j<size[i];  j++){
		    	arr[j]=arr2[j];
			}
		    start = clock();
		    heap_sort(arr,size[i]);
		    stop = clock();
		    tempt += double(stop - start) / CLOCKS_PER_SEC;
		}
	    cout << tempt << " sec" <<endl; 
		
		tempt=0;
		cout << "recursive merge sort time : ";
		for(int y=0 ; y<10000 ; y++){
		    for(int j=0 ; j<size[i];  j++){
		    	arr[j]=arr2[j];
		    	arr3[j] = "";
			}
		    start = clock();
			merge(arr , arr3 , 0 , size[i]-1);
		    stop = clock();
		    tempt += double(stop - start) / CLOCKS_PER_SEC;
		}
	    cout << tempt << " sec" <<endl; 
		
		tempt=0;
		cout << "iterative merge sort time : ";
		for(int y=0 ; y<10000 ; y++){
		    for(int j=0 ; j<size[i];  j++){
		    	arr[j]=arr2[j];
			}
		    start = clock();
			iterative_merge(arr , 0 , size[i]-1);
		    stop = clock();
		    tempt += double(stop - start) / CLOCKS_PER_SEC;
		}
	    cout << tempt << " sec" <<endl; 
		
		tempt=0;
		cout << "recursive quick sort time : ";
		for(int y=0 ; y<10000 ; y++){
		    for(int j=0 ; j<size[i];  j++){
		    	arr[j]=arr2[j];
			}
			start = clock();
			quick(arr , 0 , size[i]-1);
			stop = clock();
		    tempt += double(stop - start) / CLOCKS_PER_SEC;
		}
	    cout << tempt << " sec" <<endl; 
		
		tempt=0;
		cout << "iterative quick sort time : ";
		for(int y=0 ; y<10000 ; y++){
		    for(int j=0 ; j<size[i];  j++){
		    	arr[j]=arr2[j];
			}
			start = clock();
			iterative_quick(arr , 0 , size[i]-1);
			stop = clock();
		    tempt += double(stop - start) / CLOCKS_PER_SEC;
		}
	    cout << tempt << " sec" <<endl; 
		
		tempt=0;
		cout << "C++ built in sorting function time : ";
		for(int y=0 ; y<10000 ; y++){
		    for(int j=0 ; j<size[i];  j++){
		    	arr[j]=arr2[j];
			}
			start = clock();
			sort(arr2 , arr2 + size[i]);
			stop = clock();
		    tempt += double(stop - start) / CLOCKS_PER_SEC;
		}
	    cout << tempt << " sec" <<endl; 
		
		
		stop2 = clock();
		cout << "Total time : " << double(stop2 - start2) / CLOCKS_PER_SEC << " sec" << endl << endl << endl;
		
		delete []arr;
		delete []arr2;
		delete []arr3;
		arr = NULL;
		arr2 = NULL;
		arr3 = NULL;
	}
	stop3 = clock();
	cout << "Total time : " << double(stop3 - start3) / CLOCKS_PER_SEC << " sec" << endl << endl << endl;
	
	start3 = clock();
	for(int i=0 ; i<5 ; i++){
    	arr = new string[size2[i]];
    	arr2 = new string[size2[i]];
    	arr3 = new string[size2[i]];
	    
		cout << "----------------------   " << size2[i] << "   ----------------------";
	    start2 = clock();
	    start = clock();
	    for(int j=0 ; j<size2[i];  j++){
	    	arr[j]="";
	    	for(int k=0 ; k<6 ; k++){
	    		arr[j]+=rand()%26+97;
			}
			arr2[j] = arr[j];
		}
	    stop = clock();
	    cout << endl << "array " << size2[i] << " create time : " << double(stop - start) / CLOCKS_PER_SEC << " sec" <<endl; 
		
		cout << "heap_soer time : ";
	    start = clock();
	    heap_sort(arr,size2[i]);
	    stop = clock();
	    cout << double(stop - start) / CLOCKS_PER_SEC << " sec" <<endl; 
	    
	    for(int j=0 ; j<size2[i] ; j++){
	    	arr[j] = arr2[j];
		}
	    
		cout << "recursive merge time : ";
	    start = clock();
		merge(arr , arr3 , 0 , size2[i]-1);
	    stop = clock();
	    cout << double(stop - start) / CLOCKS_PER_SEC << " sec" <<endl; 
		
	    for(int j=0 ; j<size2[i] ; j++){
	    	arr[j] = arr2[j];
		}
	    
		cout << "iterative merge time : ";
	    start = clock();
		iterative_merge(arr , 0 , size2[i]-1);
	    stop = clock();
	    cout << double(stop - start) / CLOCKS_PER_SEC << " sec" <<endl; 
		
	    for(int j=0 ; j<size2[i] ; j++){
	    	arr[j] = arr2[j];
		}
	    
		cout << "recursive quick time : ";
		start = clock();
		quick(arr , 0 , size2[i]-1);
		stop = clock();
		cout << double(stop - start) / CLOCKS_PER_SEC << " sec" << endl;
		
	    for(int j=0 ; j<size2[i] ; j++){
	    	arr[j] = arr2[j];
		}
	    
		cout << "iterative quick time : ";
		start = clock();
		iterative_quick(arr , 0 , size2[i]-1);
		stop = clock();
		cout << double(stop - start) / CLOCKS_PER_SEC << " sec" << endl;
		
		cout << "C++ built in sorting function time : ";
		start = clock();
		sort(arr2 , arr2 + size2[i]);
		stop = clock();
		stop2 = clock();
		cout << double(stop - start) / CLOCKS_PER_SEC << " sec" << endl << endl;
		cout << "Total time : " << double(stop2 - start2) / CLOCKS_PER_SEC << " sec" << endl << endl << endl;
		
		delete []arr;
		delete []arr2;
		delete []arr3;
		arr = NULL;
		arr2 = NULL;
		arr3 = NULL;
	}
	stop3 = clock();
	cout << "Total time : " << double(stop3 - start3) / CLOCKS_PER_SEC << " sec" << endl << endl << endl;
	
    return 0;
}
