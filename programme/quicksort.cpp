#include "quicksort.h"
#include "common.h"

int partition(vector<vector<int>> &v, int start, int end)
{
	
	int pivot = end;
	int j = start;
	for(int i=start;i<end;++i){
		if(v[i][0]>v[pivot][0]){
			swap(v[i],v[j]);
			++j;
		}
	}
	swap(v[j],v[pivot]);
	return j;
	
}

void quicksort(vector<vector<int>> &v, int start, int end )
{

	if(start<end){
		int p = partition(v,start,end);
		quicksort(v,start,p-1);
		quicksort(v,p+1,end);
	}
}

int partition2(vector <tuple <int, vector <vector <char>>>> &v, int start, int end)
{
	
	int pivot = end;
	int j = start;
	for(int i=start;i<end;++i){
		if(get<0>(v[i])>get<0>(v[pivot])){
			swap(v[i],v[j]);
			++j;
		}
	}
	swap(v[j],v[pivot]);
	return j;
}

void quicksort2(vector <tuple <int, vector <vector <char>>>> &v, int start, int end )
{

	if(start<end){
		int p = partition2(v,start,end);
		quicksort2(v,start,p-1);
		quicksort2(v,p+1,end);
	}
}

int partition3(vector<vector<int>> &v, int start, int end)
{
	
	int pivot = end;
	int j = start;
	for(int i=start;i<end;++i){
		if(v[i][0]<v[pivot][0]){
			swap(v[i],v[j]);
			++j;
		}
	}
	swap(v[j],v[pivot]);
	return j;
	
}

void quicksort3(vector<vector<int>> &v, int start, int end )
{

	if(start<end){
		int p = partition3(v,start,end);
		quicksort3(v,start,p-1);
		quicksort3(v,p+1,end);
	}
}