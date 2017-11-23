#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <set>
#include <map>
#include <queue>
#include <utility>

//macros:
#define F(i,l) for( i = 0; i < l; i++)
#define Fi(i,s,l) for( i = s; i < j; i++)
#define SF(sit, st) for( sit = st.begin(); sit != st.end(); sit++)
#define MF(mit, mp) for( mit = mp.begin(); mit != mp.end(); mit++)
#define EPNT(s) fprintf(stderr,"%s\n",s)
#define pmsg(s) printf("%s\n",s)

#define SZ 256
#define MX 100100

const int PNT = 0;

using namespace std;

/*Basic node structure*/
class node
{
	public:
		vector<int>  adj;		//is the size of the number of nodes, to self = 0;
		vector<vector<int> > sp;		//shortest paths repd as a vector of ints at that nodes row number
		int v;					//the visited field
		int num;				// the id number of the node
		int Ival;				//integer value if there is one
		multimap<int ,node *> kids;	//map of distances, and children
		float fval;				//float value if there is one
		double dval;			//double value if there is one
		long lval;              //long value if there is one
		char cval;				//char value if there is one
		string name;			//string value if there is one
		class node * parent;	//this nodes parent
		node(int num);
		node(int num, int Nnodes);
		void ADDCHILD(int id, int dis, node * kp);
}*NODE;


//represents a graph(collection of ndes and edges
class graph
{
	public:
		vector<vector<int> > gph;
		vector<vector<int> > Sgph;
		vector<vector<int> > Lgph;
		set<node * > G;
		int nodecnt;
		int max;
		int min;
		int source;
		int sink;
		int root;
		set<int> VS;
		set<int> US;
		void printGAry(int t);
		void printGSet();
		graph(int size,int initval);
		graph(vector<int> f, vector<int> t, vector<int> wt, int N, int type);
		void SetNodes(int &i, int &j, int &wt);
		node * GETNODE(int num);
		void ResetG();
		//int GDIKSTRA(int &sn, queue<int> &Q, queue<int> &dist);
		int GDIKSTRA(int &sn, queue<int> &Q, int &dist);
		void MINDIKSTRA();
		void BDFS(int nd, int dis, int sn);
		void SPBDFS();
		void GDFS(int nd, int dis, int sk, int sn);
		int FLOYDW(int chg, vector<vector<int> >&G, int t);
		int SPDFS(int sk);
		queue<int> GBFS( queue<int> &Q, int from,queue<int> D, int sk);
		vector <int> BFSFIND(int sk);
		int MXST();
}*GRAPH;

//adds a child to the given nodes adjacency list
//void node::ADDCHILD(int id, int dis, node * kp);

//node::node(int number);

//node::node(int number, int Nnodes);

//resets the visited for all nodes
//void graph::ResetG();

//prints the array verstion of the graph t determins which one(basic, sp, lp
//void graph::printGAry(int t);

//prints the set version of the graph
//void graph::printGSet();

//constructor of the graph takes a 3 vectors(from, to weights, the number of nodes N, 
//and a type
//graph::graph(vector<int> f, vector<int> t, vector<int> w, int N, int type);


//constructor , takes number of nodes(size) and the initial value for all nodes dist, 
//graph::graph(int size, int initval);

//will set the dist in dis array at i,j
//void graph::SetNodes(int &i, int &j, int &wt);

//takes a node id number and returns a pointer to that node
//node * graph::GETNODE(int id);

//a dikstra style graph traversal
//takes the start node, a queue of nodes to process and the distance to this point from start node
//int graph::GDIKSTRA(int &sn, queue<int> &Q, int &DIST);

//sets the min distance graph using dijkstra traversal
//void graph::MINDIKSTRA();


//void graph::GDFS(int nd, int dis, int sk);

//A bfs graph traversal, can be used to find a path to a specific node (sk)
//queue<int> graph::GBFS( queue<int> &Q, int from,queue<int> D, int sk);

//uses GBFS to find the given node number
//vector <int> graph::BFSFIND(int sk);

//t will decide of it finds the shortest path(t= 0) or longest path(t = 1)
//works in tandem with the constructor for the given graph. use the relevant
//t with constructor to correctly set up the graph 
//int FLOYDW(int chg, vector<vector<int> >&G, int t);


//int GFW(int i,int j,int k,graph gph)
int GFW(int &i,int &j,int &k,graph  &gph, int chg);

//prints the given vector of strings
void PNTSV( vector<string> sv);

//takes a string and turns the words into a vector of strings
vector<string> StoSV( string s, string name);

//takes a vector of strings and turns it 
//into a vector of ints
vector<int> SVtoIV(vector<string> sv);

