#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<stack>

using namespace std;

struct mbp_Path
{
  vector<int> paths;
  int bandwidth;	
};

mbp_Path dijkstraWithoutHeaps(vector<vector<pair<int,int>>> G, int src, int dest)
{
	int N = G.size();
	vector<int> parent(N, -2);
	vector<int> status(N, 0);
	vector<int> BW(N, -1);

	parent[src] = 0;
	BW[src] = INT_MAX;
	status[src] = 1;

	while (status[dest] != 2)
	{
		int curr = -1, bw = -1;
		for (int i=0; i< N; i++)
		{
			if (status[i] == 1  && bw < BW[i])
			{
				curr = i;
				bw = BW[curr];
			}
		}
	
		vector<pair<int, int>> &source = G[curr];
		for (int i=0; i<source.size(); i++)
		{
			if ((status[source[i].first] != 2) &&
			    (BW[source[i].first] < min(BW[curr], source[i].second)))
            {
                parent[source[i].first] = curr;
                BW[source[i].first] = min(BW[curr], source[i].second);
                status[source[i].first] = 1;
            }
		}

		status[curr] = 2;
	}
	stack<int> s;
	int node = dest;
	while (parent[node] != 0)
	{
		s.push(node);
		node = parent[node];
	}
	s.push(src);

	static mbp_Path result;
	result.bandwidth = BW[dest];
	while(!s.empty())
	{
		result.paths.push_back(s.top());
		s.pop();
	}
	return result;
}

void DijkstraN_algorithm(vector<vector<pair<int,int>>> G, int src, int dest)
{
	int i;
	int N = G.size();
	
	mbp_Path MBP_path = dijkstraWithoutHeaps(G, src, dest);
	cout<<"Maximum bandwidth path between source : "<<src<<" and destination : "<<dest<<endl;
	for(i = 0; i < MBP_path.paths.size()-1; i++)
	  cout<<MBP_path.paths[i]<<"->";
	cout<<MBP_path.paths[i];
	cout<<"\n Bandwidth : "<<MBP_path.bandwidth<<endl;
}
