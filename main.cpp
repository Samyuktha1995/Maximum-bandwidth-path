#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<vector>
#include<algorithm>
#include<random>
#include<ctime>
#include<chrono>

#include "random_graphs.h"
#include "kruskal.h"
#include "dijkstra_with_heap.h"
#include "dijkstra_without_heap.h"

using namespace std;
using namespace std::chrono;

int main()
{
	int N = 10, queries = 5;
	int s,t;
	int avgTime[3] = {0,0,0};
	srand(time(NULL));
	
	vector< vector<pair<int,int> > > graph;
	
	graph = generate_graph_G1(N);

	for(int i = 0; i < queries; i++)
	{
	  s = rand()%N;
	  t = rand()%N;
	  
	  while(s == t)
	    t = rand()%N;

    	cout<<"\n Query : "<<i+1<<" , source : "<<s<<" - destination : "<<t<<endl;
	 
	    auto start1 = high_resolution_clock::now();
	    cout<<"\nMBP: Dijkstra without heaps \n";
	    DijkstraN_algorithm(graph, s, t);
	    auto stop1 = high_resolution_clock::now();
	    auto duration1 = duration_cast<microseconds>(stop1 - start1);
	    avgTime[0] += duration1.count();
	    cout << "\n Duration(in microseconds) : "<< duration1.count() << endl;
	    
	    auto start2 = high_resolution_clock::now();
	    cout<<"\nMBP: Dijkstra with heaps \n";
	    dijkstra_algorithm(graph, s, t);
	    auto stop2 = high_resolution_clock::now();
	    auto duration2 = duration_cast<microseconds>(stop2 - start2);
	    avgTime[1] += duration2.count();
	    cout << "\n Duration(in microseconds) : "<< duration2.count() << endl;
	    
	    auto start3 = high_resolution_clock::now();
	    cout<<"\nMBP with kruskal\n";
	    kruskal_algorithm(graph,s,t);
	    auto stop3 = high_resolution_clock::now();
	    auto duration3 = duration_cast<microseconds>(stop3 - start3);
	    avgTime[2] += duration3.count();
	    cout << "\n Duration(in microseconds) : "<< duration3.count() << endl;
    }
    cout<<"\n Average time: \n";
    for(int i = 0; i < 3; i++)
      cout<<avgTime[i]/queries<<" , ";
    return 1;
    
    
}
