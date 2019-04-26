// Dijkstra with heap:
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<stack>
#include "maxHeaps.h"

using namespace std;

struct max_bandwidth_path
{
  vector<int> paths;
  int bandwidth;	
};

max_bandwidth_path dijkstraWithHeaps(vector<vector<pair<int,int>>> G, int src, int dest)
{
	static max_bandwidth_path result;
	max_Heap h;
	int N = G.size();
	
	vector<int> parent(N, -1);
	vector<int> status(N, 0);
	int BW[N]; 
	for(int i = 0; i < N; i++)
	  BW[i] = -1;
	
	parent[src] = -1;
	status[src] = 0;
	BW[src] = INT_MAX;
	h.insert(src, BW);

	while(status[dest] != 2 && !h.empty())
	{
		int maxVal = h.top();
		int curr = maxVal;
		int bw = BW[maxVal];
		
		h.deleteVal(BW);
		vector<pair<int, int>> &source = G[curr];
		for (int i=0; i<source.size(); i++)
		{
			if ((status[source[i].first] != 2) && 
				(BW[source[i].first] < min(bw, source[i].second)))
			{
				parent[source[i].first] = curr;
				BW[source[i].first] = min(bw, source[i].second);
				h.update(source[i].first, BW);
				status[source[i].first] = 1;
			}
		}
		if (curr == dest)
		   result.bandwidth = bw;
		status[curr] = 2;
    }
    
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

void dijkstra_algorithm(vector<vector<pair<int,int>>> G, int src, int dest)
{
	int i;
	int N = G.size();
	
	max_bandwidth_path MBP_path = dijkstraWithHeaps(G, src, dest);
	cout<<"Maximum bandwidth path between source : "<<src<<" and destination : "<<dest<<endl;
	for(i = 0; i < MBP_path.paths.size()-1; i++)
	  cout<<MBP_path.paths[i]<<"->";
	cout<<MBP_path.paths[i];
	cout<<"\n Bandwidth : "<<MBP_path.bandwidth<<endl;
}
