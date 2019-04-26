#include<iostream>
#include<vector>
using namespace std;

#define nodes  10000

class max_Heap
{
	int H[nodes]; 
	int D[nodes]; 
	int n;
	
	void heapifyDown(int index, int dist[])
	{
		if(index >= size() || index < 0)
		  return;
		
		int l = 2*index + 1;
		int r = 2*index + 2;
		if(l >= size())
		    return;
		int largest = l;
		if(r < size())
		{
			if(dist[H[r]] > dist[H[l]])
			  largest = r;
		}
		
		if(dist[H[index]] < dist[H[largest]])
		{
			swap(H[index], H[largest]);
			swap(D[H[index]], D[H[largest]]);
			heapifyDown(largest, dist);
		 } 
	}
	
	void heapifyUp(int index, int dist[])
	{
		if(index >= size() || index < 0)
		  return;
		
		int p = (index-1)/2;
		if(dist[H[p]] < dist[H[index]])
		{
			swap(H[index], H[p]);
			swap(D[H[index]], D[H[p]]);
			heapifyUp(p, dist);
		} 
	}
	
public:
	
	max_Heap()
	{
		n = 0;
		for(int i = 0; i < nodes; i++)
		{
			H[i] = 0;
			D[i] = -1;
		}
	}
	
	int size()
	{
		return n;
	}
	
	bool empty()
	{
		return size()==0;
	}
	
	void insert(int x, int dist[])
	{
		H[size()] = x;
		D[x] = size();
		n++;
		heapifyUp(n-1, dist);
	}
	
	void deleteVal(int index, int dist[])
	{
		if(index >= size() || index < 0)
		  return;
		D[H[size()-1]] = index;
		D[H[index]] = -1;
		
		H[index] = H[size()-1];
		n--;
		heapifyDown(index, dist);
		heapifyUp(index, dist);
	}
	
	void deleteVal(int dist[])
	{
		if(!empty())
		  deleteVal(0, dist);
		
	}
	
	void update(int x, int dist[])
	{
		if(D[x] != -1)
		  deleteVal(D[x] , dist);
		insert(x, dist);
	}
	
	int top()
	{
		if(!empty())
		  return H[0];
		return -1; 
	}
		
};


