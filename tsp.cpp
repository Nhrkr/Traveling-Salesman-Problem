#include <iostream>
#include <vector>
#include <list>
#include <queue>          
#include <algorithm>
#include<stdlib.h>

#define V 4
using namespace std;

typedef struct prio_queue
{
	int to;
	int from;
	int cost;
}p_queue;

int prims(int graph[V][V],int start,int size)
{
	int selected[V];
	
	int min=999;
	for(int i=0;i<V;i++)
	{
		selected[i]=0;
	}
	selected[0]=1;
	int y=0,x=0,cost=0;
	int ne=0;
	
	while(ne<size-1)
	{
		min=999;
		for(int i=0;i<size;i++)
		{
			if(selected[i]==1)
			{
				for(int j=0;j<size;j++)
				{
					if(selected[j]==0)
					{
						if(graph[i][j]<min)
							min=graph[i][j];
							y=j;x=i;
					}
				}
			}
		}
		selected[y]=1;
		cost=cost+min;
		ne++;
	}
	return cost;
}
int heuristic(int original_graph[V][V],int parent_node, int node,vector<int> visited)
{
	int graph[V][V];
	int x=0,y=0;
	for(int i=0;i<visited.size();i++)
	cout<<visited[i];
	std::sort(visited.begin(), visited.end());
	int selected[V];
	for(int i=0;i<V;i++)
		selected[V]=0;
	selected[node]=1;
	int ne=0;
	for(int i=0;i<=V-visited.size();i++)
	{
		y=0;
		if(!(find(visited.begin(), visited.end(), i) != visited.end()))
		{
			for(int j=0;j<=V-visited.size();j++)
			{
				if(!(find(visited.begin(), visited.end(), j) != visited.end()))
				{
					graph[x][y]=original_graph[i][j];
					cout<<graph[x][y];
					y++;
				}
			}
			x++;	
			cout<<endl;
		}
	}
	int S=V-visited.size();
	int cost=0;
	cost=prims(graph,node,S);	
	return cost;
}

bool compareByCost(const p_queue &a, const p_queue &b)
{
    return a.cost < b.cost;
}

void add_to_pq(std::vector<p_queue>& pQ,int from,int to,int cost)
{
	p_queue node={to,from,cost};
	pQ.push_back(node);
	std::sort(pQ.begin(), pQ.end(),compareByCost);

	return;
}


pair<int,int> pop_queue(std::vector<p_queue>& pQ)
{
	pair<int,int>retval;
	retval.first=pQ[0].to;
	retval.second=pQ[0].from;
	pQ.erase(pQ.begin());
	return retval;
}



void tsp(int graph[V][V])
{
	vector<int> visited;
	vector<int> not_visited;
	vector<p_queue> prio_queue;
	int cost=0;
	pair<int,int> node;
	visited.push_back(0);
	for(int j=0;j<V-1;j++){
		cout<<"visited node"<<visited[j]<<endl;
		for(int i=0;i<V;i++)
		{
			if(!(find(visited.begin(), visited.end(), i) != visited.end()))
			{
				cost=graph[visited[j]][i]+heuristic(graph,j,i,visited);
				cout<<"Cost"<<cost<<endl;
				cout<<"adding node"<<i<<"from"<<visited[j]<<endl;
				add_to_pq(prio_queue,j,i,cost);
			}
		}
		cout<<"size of queue"<<prio_queue.size()<<endl;
		
			node=pop_queue(prio_queue);
			cout<<"node popped"<<node.first<<endl;
			visited.push_back(node.first);			
	}	
	int tsp_cost=0;
	int k;
	for( k=0;k<visited.size()-1;k++)
	{
		tsp_cost=tsp_cost+graph[visited[k]][visited[k+1]];
		cout<<"Path"<<visited[k]<<"->"<<visited[k+1]<<endl;
	}
	cout<<"Path"<<visited[k]<<"->"<<visited[0]<<endl;
	tsp_cost=tsp_cost+graph[visited[k]][visited[0]];
	cout<<tsp_cost;
	return;
}


int main()
{
	int graph[V][V] = {{0, 5, 2, 4},
                      {5, 0, 5, 3},
                      {2, 5, 0, 2},
                      {4, 3, 3, 0}
                      };
 tsp(graph);
 return 0;
}
