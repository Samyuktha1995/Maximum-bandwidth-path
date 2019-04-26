#include<iostream>
#include<queue>

using namespace std;

#define MAX 10000

class unionFind
{
   int rank[MAX];
   int set[MAX];
   int n;
   
public:
   
   unionFind(int N)
   {
   	  n = N;
   	  for(int i = 0; i < N; i++)
   	  {
   	  	set[i] = i;
   	  	rank[i] = 0;
	  }
   }
   void Union(int u, int v)
   {
   	  u = Find(u);
   	  v = Find(v);
   	  if(rank[u] < rank[v])
   	     set[u] = v;
   	  else if(rank[u] > rank[v])
		   set[v] = u;
	  else
      {
      	 set[v] = u;
      	 rank[u]++;
      }
     	 
    }
    
    int Find(int x)
    {
    	queue<int> q;
    	while(set[x] != x)
    	{
    		q.push(x);
    		x = set[x];
		}
		
		while(!q.empty())
		{
			set[q.front()] = x;
			q.pop();
		}
		return x;
	}
	
	bool check_cycle(int u, int v)
	{
		return Find(u) == Find(v);
	}
	
	

};
