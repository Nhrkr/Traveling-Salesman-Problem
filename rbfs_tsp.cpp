#include <iostream>
#include <vector>
#include <list>
#include <queue>          
#include <algorithm>
#include<stdlib.h>
#define V 4
#define INF 999
#define H 10;
int goalreached=0;

using namespace std;

typedef struct prio_queue
{
	vector<int> to;
	vector<int> from;
	int cost;
	int total;
	int goal=0;
}p_queue;

vector<p_queue> global_fringe;
vector<int> visited;

int graph[V][V]= {{0, 5, 2, 4},
                  {5, 0, 5, 3},
                  {2, 5, 0, 2},
                  {4, 3, 3, 0}
                };
bool compareByCost(const p_queue &a, const p_queue &b)
{
    return a.total < b.total;
}

int prims(int graph[V][V],int start,int size)
{}
int heuristic(int original_graph[V][V],int parent_node, int node,vector<int> visited_node)
{
	int graph[V][V];
	int x=0,y=0;
	for(int i=0;i<visited_node.size();i++)
	cout<<visited_node[i];
	std::sort(visited_node.begin(), visited_node.end());
	int selected[V];
	for(int i=0;i<V;i++)
		selected[V]=0;
	selected[node]=1;
	int ne=0;
	for(int i=0;i<=V-visited_node.size();i++)
	{
		y=0;
		if(!(find(visited_node.begin(), visited_node.end(), i) != visited_node.end()))
		{
			for(int j=0;j<=V-visited_node.size();j++)
			{
				if(!(find(visited_node.begin(), visited_node.end(), j) != visited_node.end()))
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
	cout<<endl<<x<<y<<endl;
	int S=V-visited.size();
	cout<<"heuristic"<<endl;
	int cost=0;
	cost=prims(original_graph,node,S);	
	return cost;
}

void rbfs(p_queue &root,int gb2)
{
	if(goalreached==1)
	{
		return;
	}
	cout<<"yey "<<root.from.size()<<" cost "<<root.cost<<endl;
	if(root.to.size()==0)
		{
			root.cost+=graph[root.from.size()-1][root.from[0]];
			printf("cost=%d\n",root.cost);
			for(int i=0;i<root.from.size();i++)
			{
				cout<<root.from[i]<<" ";
			}
			
			
			goalreached=1;
			return;
		}
		
	vector<p_queue> local_fringe;
	
	for(int i=0;i<root.to.size();i++)
	{
			int toadd=root.to[i];
			p_queue newnode;
			newnode.cost=+graph[root.from[root.from.size()-1]][toadd];//+heuristic(graph,root,i,visited);
			newnode.total=newnode.cost+H;
			newnode.from=root.from;
			newnode.from.push_back(toadd);
			newnode.to=root.to;
			newnode.to.erase(std::remove(newnode.to.begin(), newnode.to.end(), toadd), newnode.to.end());
			local_fringe.push_back(newnode);
			//global_fringe.push_back(node);
	}
	//sort local fringe
	std::sort(local_fringe.begin(), local_fringe.end(),compareByCost);
	cout<<"local fringe length  "<<local_fringe.size()<<endl;

	int lb2=gb2;
	if(local_fringe.size()>1)
	{
		lb2=min(local_fringe[1].total,lb2);
	}
	
	while(goalreached==0)
	{
		
			if(local_fringe[0].total<=lb2)
			{
				rbfs(local_fringe[0],lb2);
				// update lb2
				std::sort(local_fringe.begin(), local_fringe.end(),compareByCost);
				lb2=gb2;
				if(local_fringe.size()>1)
				{
					lb2=min(local_fringe[1].total,lb2);
				}
			}
			else
			{
				root.total=local_fringe[0].total;
				return;
			}
	
	}
}





int main()
{
	p_queue root;
	goalreached=0;
	root.from.push_back(2);
	root.to.push_back(0);
	root.to.push_back(1);
	root.to.push_back(3);
	root.cost=0;
	root.total=root.cost+H;
 	rbfs(root,INF);
	return 0;
}
