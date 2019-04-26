//Kruskal algorithm implementation
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<stack>
#include "unionFind.h"

using namespace std;

struct mstPath
{
	vector<pair<int,pair<int,int>>> edge_weights;
	int weight;
};

struct Graph
{
	mstPath P;
	unordered_map<int, vector<pair<int,int>>> T;
};

struct mbpPath
{
  vector<int> paths;
  int bandwidth;	
};

class maxHeap
{
    vector<pair<int, pair<int, int> > > H;
    int n;

    void heapifyDown(int index)
    {
      if (index>=size() || index<0)
        return;

      int left = 2*index+1, right = 2*index+2;
      if (left>=size())
        return;

      int largest = left;
      if (right < size())
      {
        if (H[right].first > H[left].first)
            largest = right;
       }
       
	   if (H[index].first < H[largest].first)
       {
          pair<int, pair<int, int>> temp = H[index];
          H[index] = H[largest];
          H[largest] = temp;
          heapifyDown(largest);
       }
    }
        
    void heapifyUp(int index)                                                                                                                                                 
   {                                                                                                                                                                                   
   	  if (index>=size() || index<0)                                                                                                                                              
        return;                                                                                                                                                             
				                                                                                                                                                                                                                                                                                               
 	int parent = (index-1) / 2;                                                                                                                                                                                                                                                   
	if (H[parent].first < H[index].first)                                                                                                                                     
    {                                                                                                                                                                                                                                                                                                                               
       pair<int, pair<int, int>> temp = H[index];                                                                                                                                  
	   H[index] = H[parent];                                                                                                                                                       
	   H[parent] = temp;                                                                                                                                                           
	   heapifyUp(parent);                                                                                                                                                
	}                                                                                                                                                                   
   }
                                                                                                                                                                                                                                                                                                                                                  
public:                                                                                                                                                                                                                                                                                                                                                         
	 maxHeap()                                                                                                                                                          
    {                                                                                                                                                                                                                                                                                                                           
    	 n = 0;                                                                                                                                                              
    }                                                                                                                                                                                                                                                                                                                                                       
   
   inline int size() { return n; }                                                                                                                                                                                                                                                                                                                         
   
   void insert(pair<int, pair<int, int>> x)                                                                                                                                    
   {                                                                                                                                                                                                                                                                                                                
    H.push_back(x);                                                                                                                                                             
    n++;                                                                                                                                                                        
    heapifyUp(n-1);                                                                                                                                                   
   }

   void deleteVal(int index)
   {
     if (index > size() || index < 0)
        return;
     H[index] = H[size()-1];
     n--;
     heapifyDown(index);
     H.pop_back();
   }
   
   void deleteVal()
   {
   	if(!empty())
   	  deleteVal(0);
   }
   
   bool empty() { return size() == 0; }

   pair<int, pair<int, int>> top()
    {
       if (!empty())
        return H[0];
	  
       return make_pair(0, make_pair(0,0));
    }
};

Graph MBPKruskal(vector< vector < pair<int,int> > > G)
{
	maxHeap H;
	Graph result;
	result.P.weight = 0;
	int i,j, N = G.size();
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < G[i].size(); j++)
		{
			if(i < G[i][j].first)
			   H.insert(make_pair(G[i][j].second, make_pair(i, G[i][j].first)));
		}
	}
	unionFind uF(N);
	int count = 0;
	i = 0;
	while(count < N-1)
	{
		pair<int, pair<int,int>> current = H.top();
		H.deleteVal();
		
		int u = current.second.first;
		int v = current.second.second;
		int wt = current.first;
		
		if(!uF.check_cycle(u,v))
		{
			uF.Union(u,v);
			result.P.edge_weights.push_back(current);
			result.P.weight += wt;
			count++;
		 } 
		i++;
	}
	
	mstPath &temp = result.P;
	
	for(i = 0; i < temp.edge_weights.size(); i++)
	{
	//	cout<<temp.edge_weights[i].second.first<<"->"<<temp.edge_weights[i].second.second<<" : "<<temp.edge_weights[i].first<<endl;
		
		result.T[temp.edge_weights[i].second.first].push_back(make_pair(temp.edge_weights[i].second.second, temp.edge_weights[i].first));
		result.T[temp.edge_weights[i].second.second].push_back(make_pair(temp.edge_weights[i].second.first, temp.edge_weights[i].first));
	}
	
	return result;
}

mbpPath kruskal_getMBP(unordered_map<int, vector<pair<int,int>>> &mst, int src, int dest, int N)
{
	mbpPath result;
	result.bandwidth = 0;
	
	vector<int> BW(N,0);
	vector<int> parent(N,-2);
	queue<int> q;
	
	BW[src] = INT_MAX;
	parent[src] = -1;
	q.push(src);
	
	while (!q.empty())
	{
		int current = q.front();
		if (current == dest)
			break;
		q.pop();
		for (int i=0; i<mst[current].size(); i++)
		{
			if (parent[mst[current][i].first] == -2)
			{
				parent[mst[current][i].first] = current;
				BW[mst[current][i].first] = min(BW[current], mst[current][i].second);
				q.push(mst[current][i].first);	
				
			}
		}
	}
	result.bandwidth = BW[dest];
	stack<int> s;
	int node = dest;
	while (parent[node] != -1)
	{
		s.push(node);
		node = parent[node];
	}
	s.push(src);
	while(!s.empty())
	{
		result.paths.push_back(s.top());
		s.pop();
	}

	return result;
}
void kruskal_algorithm(vector< vector < pair<int,int> > > G, int src, int dest)
{
	int i;
	int N = G.size();
	Graph t = MBPKruskal(G);
	mbpPath MBP_path = kruskal_getMBP(t.T, src, dest, N);
	cout<<"Maximum bandwidth path between source : "<<src<<" and destination : "<<dest<<endl;
	for(i = 0; i < MBP_path.paths.size()-1; i++)
	  cout<<MBP_path.paths[i]<<"->";
	cout<<MBP_path.paths[i];
	cout<<"\n Bandwidth : "<<MBP_path.bandwidth<<endl;
}
