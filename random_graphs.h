#include<iostream>
#include<cstdio>
#include<vector>
#include<cstdlib>
#include<ctime>


using namespace std;

void printGraph(vector< vector< pair<int,int> > > G)
{
	int i,j;
	int N = G.size();
	cout<<"Print graph:"<<endl;
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < G[i].size(); j++)
		{
			cout<<i<<"->"<<G[i][j].first<<" : "<<G[i][j].second<<endl;
		}
		cout<<endl;
	}
}
void dfs(vector< vector< pair<int,int> > > G, int v, vector<int> &colour)
{
	colour[v] = 1;
	for(int i = 0; i < G[v].size(); i++)
	{
		int w = G[v][i].first;
		if(colour[w] == 0)
		   dfs(G, w, colour);
	}
	colour[v] = 2;
}

void checkCycle(vector< vector< pair<int,int> > > G)
{
	int N = G.size();
	vector<int> colour(N,0);
	int count = 0;
	for(int i = 0; i < N; i++)
	{
		if(colour[i] == 0)
		{
			count++;
			dfs(G, i, colour);
		 } 
	}
	
	cout<<"\n No. of comp: "<<count<<endl;
	
	
}
//Generating standard Graph:

vector< vector<pair<int,int> > > test_graph_1()
{
	vector< vector<pair<int,int> > > adjList;
	int n = 7;
	
	for(int i = 0; i < n; i++)
	{
		vector< pair<int,int> > row;
		adjList.push_back(row);
	}
	
	adjList[0].push_back(make_pair(1, 2));
    adjList[0].push_back(make_pair(2, 3));
    
    adjList[1].push_back(make_pair(0, 2));
    adjList[1].push_back(make_pair(5, 6));
    adjList[1].push_back(make_pair(3, 4));
    
    adjList[2].push_back(make_pair(0, 3));
    adjList[2].push_back(make_pair(5, 7));
    
    adjList[3].push_back(make_pair(1, 4));
    adjList[3].push_back(make_pair(4, 5));
    adjList[3].push_back(make_pair(6, 8));
    
    adjList[4].push_back(make_pair(3, 5));
    adjList[4].push_back(make_pair(5, 9));
    adjList[4].push_back(make_pair(6, 1));
    
    adjList[5].push_back(make_pair(1, 6));
    adjList[5].push_back(make_pair(2, 7));
    adjList[5].push_back(make_pair(4, 9));
    adjList[5].push_back(make_pair(6, 10));
    
    adjList[6].push_back(make_pair(3, 8));
    adjList[6].push_back(make_pair(4, 1));
    adjList[6].push_back(make_pair(5, 10));
    
    return adjList;
}

vector< vector<pair<int,int> > > generate_graph_G1(int N)
{
	int i,j;
	vector<int> count(N,0);
	vector< vector< pair<int,int> > > G(N);
	int x = 5*N;
	srand(time(NULL));
	vector<vector<int>> visited(N, vector<int>(N,0));
	for(i = 0; i < N; i++)
	{
	
		while(count[i] < 6)
		{
			int p = rand()%N;
			if(p!=i && !visited[i][p])
			{
				int wt = rand()%x;
				G[i].push_back(make_pair(p,wt));
				G[p].push_back(make_pair(i,wt));
				count[i] += 1;
				count[p] += 1;
				visited[i][p] = 1;
				visited[p][i] = 1;
			}
		}
	}
	
	return G;
}

vector< vector<pair<int,int> > > generate_graph_G2(int N)
{
	int i,j;
	int x = 0.2*N;
	int y = 10*N;
	srand(time(NULL));
	vector<vector<int>> visited(N, vector<int>(N,0));
	vector< vector< pair<int,int> > > G(N);
	
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < x; j++)
		{
		int p = rand()%N;
		if(p!=i && !visited[i][p])
			{
				int wt = rand();
				G[i].push_back(make_pair(p,wt));
				G[p].push_back(make_pair(i,wt));
				visited[i][p] = 1;
				visited[p][i] = 1;
			}	
		 } 
	}
	
    
    return G;
}

vector< vector<pair<int,int> > > generate_graph_G3(int N)
{
	int i,j;
	vector< vector< pair<int,int> > > G(N);
	
	for(i = 0; i < N; i++)
	{
	  for(j = 0; j < N; j++)
	  {
	  	int p = rand()%N;
	  	if(j != i && p < 20)
	  	{
	  	   int wt = rand();
		   G[i].push_back(make_pair(j, wt));
		   G[j].push_back(make_pair(i, wt));	
		}
	  }	
	}
	
    return G;
}


vector< vector<pair<int,int> > > test_graph_2()
{
	vector< vector<pair<int,int> > > adjList;
	int n = 6;
	
	for(int i = 0; i < n; i++)
	{
		vector< pair<int,int> > row;
		adjList.push_back(row);
	}
	
	adjList[0].push_back(make_pair(1, 2));
    adjList[0].push_back(make_pair(2, 2));
    
    adjList[1].push_back(make_pair(0, 2));
    adjList[1].push_back(make_pair(2, 1));
    
    adjList[2].push_back(make_pair(0, 2));
    adjList[2].push_back(make_pair(1, 1));
    
    adjList[3].push_back(make_pair(4, 2));
    adjList[3].push_back(make_pair(5, 2));
    
    adjList[4].push_back(make_pair(3, 2));
    adjList[4].push_back(make_pair(5, 2));
    
    adjList[5].push_back(make_pair(3, 2));
    adjList[5].push_back(make_pair(4, 2));
    
    
    return adjList;
}



