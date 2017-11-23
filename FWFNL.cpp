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
#define MX 6000000

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


void node::ADDCHILD(int id, int dis, node * kp)
{
	map<int, node *>::iterator mit;
	map<int, node *>::iterator kmit;

	adj[id] = dis;

		mit = kids.begin();

		while( mit != kids.end())
		{
			//mit = kids.find(dis);

			if( (*mit).second == kp)
			{
				kids.erase(mit);
				break;
			}
			
			mit++;
		}
	
		printf("adding dis %d to node %d toward %d \n", dis, num, kp->num);

		kids.insert(make_pair(dis,kp));
}


node::node(int number)
{
	num = number;
	v = 0;
	adj.clear();
}

node::node(int number, int Nnodes)
{
	num = number;
	v = 0;
	adj.clear();
	adj.resize(Nnodes,MX);

	sp.resize(Nnodes);

	for(int i = 0; i < Nnodes; i++)
	{
		sp.at(i).resize(0);
	}

}





class graph
{
	public:
		vector<vector<int> > gph;
		vector<vector<int> > Sgph;
		vector<vector<int> > Lgph;
		vector<vector<int> > A;
		vector<vector<long> > AC;
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
		void MakeA();
		long MakeAchgs( int chgs);
		void ResetG();
		//int GDIKSTRA(int &sn, queue<int> &Q, queue<int> &dist);
		int GDIKSTRA(int &sn, queue<int> &Q, int &dist);
		void MINDIKSTRA();
		queue<int> GBFS( queue<int> &Q, int from,queue<int> D, int sk);
		vector <int> BFSFIND(int sk);
		int MXST();
}*GRAPH;

void graph::ResetG()
{
	set<node *>::iterator sit;

	SF(sit,G)
	{
		(*sit)->v = 0;
	}
}

long graph::MakeAchgs( int chgs)
{

	//printf("chgs is %d\n", chgs);
	int hchg = chgs/2;
	int hchg16 = chgs/16;
	int hchg32 = chgs/32;

	int imed;

	int i, j, k, f, z, t, num = Sgph.size();

	vector<vector<long> > ACC(num), Ai(num), Alft, Alast;
	vector<vector<long> > AC1(num), AC8, AC16, AC32;

	vector<vector<long> > AMX(num);
	
	AC.resize(A.size());


	F(i,num)
	{
		AMX[i].resize(A[i].size(),MX);
		ACC[i].resize(A[i].size());
		AC[i].resize(A[i].size());
		AC1[i].resize(A[i].size());
	}

	vector< vector<vector<long> > > all;

	all.resize(7);

	i = 0;
	for(i = 0; i < A.size(); i++)
	{
		for(j = 0; j < A[i].size(); j++)
		{
			AC[i][j] = (long)A[i][j];
			ACC[i][j] = (long)A[i][j];
			AC1[i][j] = (long)A[i][j];
		}
	}


	int sofar, next, l, cnt = 1;;
	int fr = 4, h = 128, eight = 8, K = 1024, OK = 131072, OM = 1048576, HM = 524288;

	for( l = 2; l < hchg; l = l*2);


//	printf("l is %d\n",l);
//	printf("l/2 is %d\n",l/2);


	int ll = l/2;

	int ll4 = l/4;



	while( ll + ll4 > chgs)
	{	
		ll4 = ll4/2;
	}

///	printf("ll4 is %d\n", ll4);
	int ll8 = ll4/2;
	int ll16 = ll8/2;
	int ll32 = ll16/2;
	//printf("ll8 is %d\n", ll8);
	//printf("ll16 is %d\n", ll16);
	//printf("ll32 is %d\n", ll32);

	int lastmade = l/2;

//	printf("lastmade is %d\n", lastmade);
//	printf("will need to do %d more \n", chgs - lastmade);



	int nddd = chgs - lastmade;

	int ON = nddd;

	int last = 1;

	int nmcnt = 1;

	while( nmcnt < nddd)
	{
		nmcnt = nmcnt * 2;
	}


	int g2 = nmcnt/2;

	int g3 = g2/2;

	int kkl = 0;

//	printf("can get to %d\n",g2);
//	printf("next get to %d\n",g3);
//	printf("summed they are %d\n", g2+g3);
//	printf("leaves %d \n", nddd - (g2+g3));

	int olndd = nddd - (g2+g3);

	int clst = 1;

	while( clst < nddd - (g2+g3))
	{
		clst = clst * 2;
	}

	int g4 = clst/2;


	int g5 = g4/2;


//	printf("can get to %d\n",g4);
//	printf("next get to %d\n",g5);
//	printf("summed they are %d\n", g4+g5);
//	printf("leaves %d \n", olndd - (g4+g5));

	int a = 1, b = 1, limit = chgs; ;

	Ai = AMX;
	//Ai = A;

	//for(sofar = 1; sofar*2 <= chgs; sofar = sofar*2)
	for(sofar = 2; sofar <= limit; sofar = next)
	{
	//	printf("sofar is %d\n", sofar);
	//	printf("last is A%d\n",last); 
		//printf("making A%d\n", sofar*2);
	//	printf("making A%d\n", sofar);


	//	printf("\na + b = %d + %d = %d\n", a, b, a+b);
		
		Ai = AMX;

		F(f,Sgph.size() )
		{
			F(t,Sgph.size())
			{
				F(z,Sgph.size())
				{
					//if( z != t)
		//			if( z != t && f != z && f != t)
					if(1)
					{
						long fz = AC[f][z];
						long zt = ACC[z][t];

						int sml = (fz < zt) ? fz : zt;

					//	if(Ai[f][t] > sml)
					//	if(fz != 0 && zt != 0 && Ai[f][t] > fz + zt)
						//if(fz != 0 && zt != 0 && Ai[f][t] > sml)
						if(Ai[f][t] > fz + zt)
						{
							Ai[f][t] = fz + zt;
							//Ai[f][t] = sml;
						}
					}
				}
			}

		}


			if( sofar == OM)
			{ 
//				printf("-------------------------saving om\n");
				all[6] = Ai;;
			}
			else if( sofar == HM)
			{
//				printf("-------------------------saving HM\n");
				all[5] = Ai;;

			}
			else if( sofar ==  OK)
			{
//				printf("-------------------------saving OK\n");
				all[4] = Ai;;

			}
			else if( sofar == K)
			{
//				printf("-------------------------saving K\n");
				all[3] = Ai;;

			}
			else if( sofar == h)
			{
//				printf("-------------------------saving h\n");
				all[2] = Ai;;

			}
			else if( sofar == eight)
			{
//				printf("-------------------------saving eight\n");
				all[1] = Ai;;

			}
			else if( sofar == fr)
			{
//				printf("-------------------------saving fr\n");
				all[0] = Ai;;

			}

//0-6

		if( sofar * 2 < limit)
		{
//			printf("made A%d\n", sofar);
			next = sofar*2;
//			printf("NEXT is %d\n",next);
			//Alast = AC;
			last = sofar;
			AC = Ai;
			ACC = Ai;
			a = sofar;
			b = sofar;

		}
		else
		{
//			printf("made A%d\n", sofar);
			ACC = Ai;
			last = sofar;

			b = sofar;

			if( chgs - sofar >= OM)
			{
	//			printf("\n\nusing om\n\n");
				AC = all[6];
				next = sofar + OM;
				a = OM;
			}
			else if( chgs - sofar >= HM)
			{
	//			printf("\n\nusing HM\n\n");
				AC = all[5];
				next = sofar + HM;
				a = HM;

			}
			else if( chgs - sofar >=  OK)
			{
	//			printf("\n\nusing ok\n\n");
				AC = all[4];
				next = sofar + OK;
				a = OK;

			}
			else if( chgs - sofar >= K)
			{
	//			printf("\n\nusing k\n\n");
				AC = all[3];
				next = sofar + K;
				a = K;

			}
			else if( chgs - sofar >= h)
			{
	//			printf("\n\nusing h\n\n");
				AC = all[2];
				next = sofar + h;
				a = h;

			}
			else if( chgs - sofar >= eight)
			{
	//			printf("\n\nusing eight\n\n");
				AC = all[1];
				next = sofar + eight;;
				a = eight;

			}
			else if( chgs - sofar >= fr)
			{
	//			printf("\n\nusing fr\n\n");
				AC = all[0];
				next = sofar + fr;
				a = fr;

			}
			else
			{
	//			printf("\n\nusing 1 \n\n");
				AC = AC1;
				next = sofar+1;;
				a = 1;;
			}
		}
		/*
		if(sofar *2 > chgs/2)
		{
			pmsg("\n\n\n\nchanging limit\n\n\n\n\n");
			limit = chgs;
		}
		*/
	}





	//printf("returning %ld\n", Ai[0][num-1]);

	return Ai[0][num-1];
}

void graph::MakeA()
{
	int i, j, k, f, t;

	A.resize(Sgph.size());

	//	printf("the size of main is %d\n",Sgph.size());

	F(i,Sgph.size() )
	{
		A[i].resize(Sgph[i].size(),MX);
	}

	//	pmsg("\nllll\n");
	int fi, ij, jt ,ft, min = -MX;;

	F(f, Sgph.size())
	{
		//		pmsg("\nloooo\n");

		F(t,Sgph.size())
		{
			//			pmsg("\npppp\n");

			min = MX;		

			F(i,Sgph.size())
			{

				F(j, Sgph.size())
				{
					if(1)
						//if(f != i && i != j && j != t )
					{
						fi = Sgph[f][i];
						//ij = -1*Lgph[i][j];
						ij = Lgph[i][j];
						jt = Sgph[j][t];

						if(PNT)	printf("f %d, t %d,=%d  i %d,  j %d, = %d\n", f, t, A[f][t],i, j , ij);
						if(PNT)	printf("fi %d, ij %d, jt %d, total %d\n",fi , -ij, jt, fi-ij+jt);


						if( min > fi-ij+jt)
						{
							A[f][t] = fi-ij+jt;
							min = fi-ij+jt;
						}
					}
				}
			}

		}
	}

	return ;

}


void graph::printGAry(int t)
{
	int i = 0, j = 0;;


	vector<vector<int> > gh;

	if(t == 0) gh = gph;
	else if(t == 1) gh = Sgph;
	else if(t == 2) gh = Lgph;
	else gh = A;

	if(t == 0) printf("printing Gph\n");
	else if(t == 1) printf("printing SGph\n");
	else if(t == 2) printf("printing LGph\n");
	else printf("printing A\n");

	F( i, gh.size())
	{
		printf("NODE %d:\n",i+1);
		F(j, gh[i].size())
		{
			//if(gh[i][j] < MX && i != j)
			//if(i != j)
			//	{
			//		printf("---%d--->Node: %d\n", gh[i][j], j+1);
			//
			printf("%d ",gh[i][j]);
			//	}
		}
		printf("\n");
	}
}

void graph::printGSet()
{

	int i = 0, j, k;
	node * np;

	set<node *>::iterator sit;
	map<int, node * >::iterator mit;

	for(sit = G.begin() ; sit != G.end(); sit++)
	{
		np = (*sit);
		printf("Node: %d:\n", np->num);

		for(mit = np->kids.begin(); mit != np->kids.end(); mit++)
		{
			printf("child %d:--- %d--->NODE %d\n",i, mit->first,mit->second->num);
		}

	}
}


graph::graph(vector<int> f, vector<int> t, vector<int> w, int N, int type)
{
	int i = 0, j = 0;

	//	printf("f size %d, t size %d, w size %d\n",f.size(), t.size(), w.size());

	gph.resize(N);
	Sgph.resize(N);
	Lgph.resize(N);

	F(i,N)
	{
		//gph[i].resize(N,MX);
		gph[i].resize(N,0);
		Sgph[i].resize(N,MX);
		Lgph[i].resize(N,-MX);
	}

	node * nd;


	F(i,N)
	{
		F(j,N)
		{
			if(i == j)
			{
				gph[i][j] = 0;
				Sgph[i][j] = 0;
				Lgph[i][j] = 0;
			}
		}
	}


	set<node *>::iterator sit;
	set<int>::iterator isit;

	set<int> sh;

	F(i,f.size())
	{
		if( sh.find(f[i]) == sh.end())
		{
			sh.insert(f[i]);
			nd = new node(f[i],N);
			G.insert(nd);
		}

		if( sh.find(t[i]) == sh.end())
		{
			sh.insert(t[i]);
			nd = new node(t[i],N);
			G.insert(nd);
		}
	}

	F(i,f.size())
	{
		int fm, to, wt;
		fm = f[i];
		to = t[i];
		wt = w[i];

		//printf("i is %d\n",i);

		node * fr, * tw;


		sit = G.begin();
		fr = (*sit);

		while( sit != G.end()&& fr->num != fm)
		{
			sit++;
			fr = (*sit);
		}

		sit = G.begin();
		tw = (*sit);
		while(sit != G.end() && tw->num != to)
		{
			sit++;
			tw = (*sit);
		}

		//fr->kids[wt] = tw;;
		fr->kids.insert(make_pair(wt,tw));

		gph[fm-1][to-1] = wt;
		if(Sgph[fm-1][to-1] > wt) Sgph[fm-1][to-1] = wt;
		if(Lgph[fm-1][to-1] < wt ) Lgph[fm-1][to-1] = wt;


		if(type == 1)
		{
			tw->kids.insert(make_pair(wt,fr));
			//gph[to-1][fm-1] = wt;
			if(gph[to-1][fm-1] < wt) gph[to-1][fm-1] = wt;
			if(Sgph[to-1][fm-1] > wt) Sgph[to-1][fm-1] = wt;
			if(Lgph[to-1][fm-1] < wt) Lgph[to-1][fm-1] = wt;
		}


		//printf("from: %d to %d is %d\n", fm,to,wt);

	}


	F(i,N)
	{
		F(j,N)
		{
			if(i == j)
			{
				//				gph[i][j] = 0;
				//				Sgph[i][j] = 0;
				//				Lgph[i][j] = 0;
			}
		}
	}



}


graph::graph(int size, int initval)
{
	int i = 0;

	if(size <= 0) 
	{
		EPNT("Bad size given to graph initializer\n");
		exit(0);
	}

	gph.resize(size);

	F(i,size)
	{
		gph[i].resize(size,initval);
	}
}

void graph::SetNodes(int &i, int &j, int &wt)
{
	gph[i][j] = wt;
	return;
}

node * graph::GETNODE(int id)
{
	set<node*>::iterator sit;

	for(sit = G.begin(); sit != G.end();sit++)
	{
		node * np = (*sit);

		if( np->num == id) return np;

	}
	return NULL;
}



void makegraph(vector<int> &f, vector<int> &t, vector<int> &w, graph &gph)
{
	int i, j, z = 0;;

	F(i, f.size())
	{
		if(f[i] == t[i]) gph.SetNodes(f[i],f[i],z);
		else gph.SetNodes( f[i] , t[i], w[i]); 
		//if(f[i] == f[i]) gph.gph[ f[i] ][ t[i] ] = 0;
		//else gph.gph[ f[i] ][ t[i] ]= w[i]; 
	}

	return;
}


//int graph::GDIKSTRA(int &sn, queue<int> &Q, queue<int> &DIST)
int graph::GDIKSTRA(int &sn, queue<int> &Q, int &DIST)
{

	if(Q.empty()) return -1;

	int cn = Q.front();
	int dist = DIST;
	Q.pop();
	//DIST.pop();


	if(PNT) printf("-----------processing node %d from %d, current D %d\n",cn,sn,dist);

	set<int>::iterator sit;
	map<int, node *>::iterator kmit;
	map<int, node *>::iterator it;

	node * SN = GETNODE(sn);
	node * CN = GETNODE(cn);
	node * child;

	if(CN->v ==1)
	{
		return -1;
	}

	CN->v = 1;

	MF(kmit, CN->kids)
	{

		child = GETNODE((*kmit).second->num);

		int D = (*kmit).first + dist;


		printf("str %d , cn %d child %d\n", sn, cn, child->num);
		printf("possible new dis is %d\n", D);

		if(child->num != sn && Sgph[sn-1][child->num-1] > D)
		{
			printf("new min dist of %d vs %d from %d to %d\n", D, Sgph[sn-1][child->num-1],sn, child->num);
			Sgph[sn-1][child->num-1] = D;


			MF(it, SN->kids)
			{
				if((*it).second == child)
				{
					//ADDNODE();
					SN->ADDCHILD( child->num, D, child);
				}
			}
		}
	}


	MF(kmit, CN->kids)
	{
		child = GETNODE((*kmit).second->num);

		int D = (*kmit).first + dist;
	
		if(child->v == 0)
		{
			Q.push(child->num);
			//DIST.push(Sgph[sn-1][child->num-1]);
			printf("adding dist %d\n",Sgph[sn-1][child->num-1]);
		}
		//if(child->v == 0)	GDIKSTRA(sn, child->num, Sgph[sn][child->num]);
	}


	return 1;
}

void graph::MINDIKSTRA()
{

	set<node *>::iterator sit;

	queue<int> Q, D;

	SF(sit, G)
	{
		Q.push((*sit)->num);
		D.push(0);

		while(!Q.empty())
		{
			GDIKSTRA((*sit)->num, Q, Sgph[(*sit)->num-1][Q.front()-1] );
		}

		ResetG();
	}
}

int graph::MXST()
{
	map<int, set<int> > MS;
	map<int, set<int> >::iterator mit;
	set<int> MSET;
	set<int>::iterator sit;;
	MSET.clear();
	
	int i = 0, j = 0, dis= 0;

	int mx = -MX;

	
	F(i, Sgph.size())
	{
		int cnode = i;
		MS.clear();
		F(j, Sgph[i].size())
		{
				
			int to = j;

			dis = Sgph[cnode][to];

			if( dis != MX)
			{
				if(PNT) printf("dist from %d to %d is %d\n", cnode, to , dis);
				
				mit = MS.find( dis ); 

				//if the dist is not there add it and then
				//add i and j to the set
				if(mit == MS.end())
				{
					if(PNT)printf("dist %d not found\n", dis);
					//MSET.insert(i);
					MS[dis].insert(i);;
					MS[dis].insert(j);;
					//MS[dis] = MSET;
					//MSET.insert(j);

					//MS[dis] = MSET;
					MSET.clear();

					int szs = (int)MS[dis].size();

					if(PNT)printf("the size of the set at %d is now %d\n", dis, szs);
					
					
					if(PNT)printf("mx is %d\n",mx);

					if( mx < szs ) 
					{
						mx = szs;
						if(PNT)printf("-------------------------adjusting max to %d\n",mx);
					}
				}
				else
				{
					MSET = (*mit).second;

					int bdm = 0;

					SF(sit, MSET)
					{
						if( Sgph[(*sit)][j] != dis) 
						{
							bdm = 1; 
						}
					}

					if(bdm == 0) MS[dis].insert(j);
					if( mx < MS[dis].size() ) mx = MS[dis].size();
					MSET.clear();
				}
			}
		}
	}


	printf("max is %d\n",mx);
}


//queue<int> graph::GBFS( vector<vector<int> > &GPH, queue<int> &Q, set<node *> G, vector<int> &path, int from,queue<int> D, int sk)
queue<int> graph::GBFS( queue<int> &Q, int from,queue<int> D, int sk)
{
	if(Q.empty())
	{
		return Q;
	}

	int i, j, k, num, dis;

	queue <int> rq;

	set<int>::iterator sit;
	map<int, node *>::iterator mit, mit2;

	int nde = Q.front();
	int dist = D.front();
	Q.pop();
	D.pop();
	
	if(PNT) printf("processeing node: %d\n",nde);
	if(PNT) printf("dist from start node %d is %d\n",from, dist);

	
	if(nde == sk)
	{
		printf("check path\n");
		return Q;
	}

	//path.push_back(nde);

	node * nd = GETNODE(nde);

	node * nf, * kid;

	if(nd == NULL) 
	{
		printf("node %d NOT FOUND\n",nde);
		exit(0);
	}

	if(nd->v == 1)
	{
		return Q;
	}
	
	nd->v = 1;
	//for(sit = nd->kids.begin(); sit != nd->kids.end(); sit++)
	MF(mit, nd->kids)
	{
		k = (*mit).second->num;
		int dis = (*mit).first;				//distance from current node to child
		
		
		if(dis + dist < Sgph[from][k])
		{
			kid = GETNODE(k);
		
			Sgph[from][k] = dis + dist;

			nf = GETNODE(from);

			MF(mit2,nf->kids)
			{
				if((*mit).second == GETNODE(k))
				{
					nf->kids.erase(mit);
				}
			}
			
			kid->parent = nd;

			//nf->kids[dis+dist] = kid;
			nf->kids.insert(make_pair(dis+dist,kid));
		}

		if(kid->v == 0)
		{
			Q.push(k);
			D.push(dis+dist);
		}
	}

	return Q;
}


vector <int> graph::BFSFIND(int sk)
{
	int i ,j, k, num, dis;

	node * nd, *kid;

	set<node *>::iterator sit;
	map<int, node *>::iterator mit;
	queue<int> Q;
	queue<int> D;
	vector<int> path;

	SF(sit, G)
	{
		nd = (*sit);

		Q.push(nd->num);
		D.push(0);
		path.push_back(nd->num);

		printf("adding node %d\n", nd->num);
		while(!Q.empty())
		{
           //GBFS( vector<vector<int> > &GPH, queue<int> &Q, set<node *> G, vector<int> &path, int from,queue<int> D, int sk)
			GBFS(Q, nd->num, D, sk);

		}

		/*
		if(path.back() == sk)
		{
			int mn;
			F(mn, path.size())
			{
				printf("%d---->",path[mn]);
			}
			
			printf("\n\n");
		}
		*/

		path.clear();
	}


	return path;

}



//t will decide of it finds the shortest path(t= 0) or longest path(t = 1)
//works in tandem with the constructor for the given graph. use the relevant
//t with constructor to correctly set up the graph 
int FLOYDW(int chg, vector<vector<int> >&G, int t)
{
	int i, j, k;

	F(k, G.size())
	{
		F(i, G.size())
		{
			F(j, G.size())
			{
				int ij = G[i][j];
				int ik = G[i][k];
				int kj = G[k][j];

				if(PNT)	printf("G[%d][%d] %d > G[%d][%d]= %d + G[%d][%d]= %d\n",i,j,G[i][j], i,k,G[i][k], k, j, G[k][j]);

				if( t == 0 && ik < MX && kj < MX && ij > ik + kj)
				{
					if(PNT)printf("new shortest path %d\n", ik+kj);
					G[i][j] = G[i][k] + G[k][j];
				}
				//else if(( t == 1 && ik > -MX && kj > -MX && ij < ik + kj))
				else if( t == 1 && i != j && i != k && k != j && ik > -MX && kj > -MX )
				//else if( t == 1 )
				{
					int f = (ik < kj ) ? ik : kj;

					if(PNT)printf("new longest path %d\n", ik+kj);

					if( ik+kj > G[i][j])
					{
						//G[i][j] = f;;
						G[i][j] = ik+kj;;

					}
				}
				else if(t == 0) if(PNT) pmsg("no new sp\n");
				else if(PNT)pmsg("no new lp\n");

			}
		}
	}

	return chg;
}


//int GFW(int i,int j,int k,graph gph)
int GFW(int &i,int &j,int &k,graph  &gph, int chg)
{

	int c, d, e, inum = 0;

	if( k == 0)
	{
		return gph.gph[i][j];
	}

	F(c, gph.gph.size())
	{
		F(d, gph.gph[i].size())
		{
			if(c == d)
			{
				gph.gph[c][d] = 0;
			}
			else
			{

			}
		}
	}


	int rtn = 0;


	return rtn;
}

void PNTSV( vector<string> sv, string name)
{

		printf("%s....\n",name.c_str());

		for(int i = 0; i < sv.size();i++)
		{
			//printf("%d: %s  ",i, sv[i].c_str());
			printf("%s  ", sv[i].c_str());
		}

		printf("\n");

		return;
}

vector<string> StoSV( string s, string name)
{
	int i = 0, j = 0;

	vector<string> sv;
	sv.clear();

	char * buff[SZ];

	string cs;

	while(i < s.size())
	{
		j = 0;
		while( i < s.size() && s[i] != ' ')
		{
			cs.push_back(s[i]);
			i++;
			j++;
		}


		sv.push_back(cs);
		cs.clear();
		

		while(i < s.size() && s[i] == ' ')
		{
			i++;
		}
	}

	

	//PNTSV(sv,name);

	return sv;
}


vector<int> SVtoIV(vector<string> sv)
{
	int i = 0;

	vector<int> rtv;
	rtv.clear();

	F(i, sv.size())
	{
		rtv.push_back( atoi(sv[i].c_str()));
	}

	return rtv;
}



int main(int argc, char ** argv)
{

	if(argc < 0)
	{
		EPNT("usage: a.out stuff\n");
		exit(0);
	}

	int num = 10;

	//CODE SPECific VARS
	//graph gph(num,SZ);


	string N,from,to,wt,chg;

	//get number of vertices N, from, to, and weight vectors, and the number of charges
	getline(cin,N);
	getline(cin,from);
	getline(cin,to);

	vector<int> fv,tv,wtv;
	string fm = "from", tt = "to", ww = "wt";
	
	fv = (SVtoIV( StoSV(from,fm) ));
	tv = (SVtoIV( StoSV(to  ,tt) ));
	int numb = 0;

//	printf("size of fv is %d\n", fv.size());

	//exit(0);
	
	int cnt = 0;

	while(cnt < fv.size())
	{
		cin>>numb;
		cnt++;
		//printf("num is %d\n", numb);
		wtv.push_back(numb);	
	}

	//getline(cin,wt);
	//getline(cin,chg);
	cin>>chg;

//	cout<<"the chng "<<chg<<endl;
	int n = atoi(N.c_str());
	int chn = atoi(chg.c_str());

//	printf("N: %d, charges: %d\n", n, chn);



	//convert the string vectors into integer vectors
	//wtv = (SVtoIV( StoSV(wt,"wt") ));

	graph gph(fv, tv, wtv,n,0);
	//graph Dgph(fv, tv, wtv,n,0);
	//graph Fgph(fv, tv, wtv,n,0);
	//graph Bgph(fv, tv, wtv,n,0);

	//create a graph class
	gph.max = SZ;
	gph.min = -SZ;

	int i= 0, j = 0, k = 0, fd = 0, *ip= NULL;

	double dbl = 0, *dp = NULL;

	float fl = 0.0, *flp = NULL;

	FILE * fp;

	set<int>::iterator sit;
	set<int> IS;
	vector<int> IV;
	vector<vector<int> > IVV;

	string str;

//	gph.printGAry(0);
//	pmsg("\n\n\n\n");
//	gph.printGAry(1);
//	pmsg("\n\n\n\n");
//	gph.printGAry(1);
//	pmsg("\n\n\n\n");
//	Dgph.printGAry(0);

//	pmsg("\n\n\n");
	
//	gph.printGAry(2);
//	Dgph.printGAry(2);

//	pmsg("\n\n\n");

//	gph.printGSet();

//	pmsg("\n\n\n");


//	gph.MINDIKSTRA();
//	gph.printGAry(1);
//	pmsg("\n\n\n");
	FLOYDW(chn,gph.Sgph,0);
//	pmsg("\n\n\n\n");
	
	//FLOYDW(chn,gph.gph,1);
//	pmsg("\n\n\n\n");
//	gph.printGAry(1);
//	pmsg("\n\n\n\n");
//	gph.printGAry(0);
//	pmsg("\n\n\n\n");

	gph.MakeA();
//printf("made A\n");	
//	gph.printGAry(3);
//	pmsg("\n\n\n\n");

//exit(0);
	if( chn == 0)
	{
		printf("%d\n",gph.Sgph[0][n-1]);
		return gph.Sgph[0][n-1];
	}
	else if( n == 1)
	{
		printf("%d\n", -1*gph.gph[0][0]*chn);
		return -1*gph.gph[0][0]*chn;
	}
	else if(chn == 1 || wtv.size() == 1)
	{
		printf("%d\n",gph.A[0][n-1]);
		return gph.A[0][n-1];
	}
	//else if(gph.Sgph.size() == 2)
//	{
		
//	}
	else
	{


//		printf("makeing a chngs with %d chgs\n", chn);

		long ans = gph.MakeAchgs(chn);

		printf("%ld\n",ans);
		return ans;
	}
	//	pmsg("\n\n\nL\n");

	//gph.printGSet();
	//gph.MXST();




	/*
	   FLOYDW(chn,gph.gph,0);
	   FLOYDW(chn,gph.Sgph,0);
	   FLOYDW(chn,gph.Lgph,1);
	   gph.printGAry(0);
	   pmsg("\n\n\nS\n");

	   gph.printGAry(1);

	   pmsg("\n\n\nL\n");


	gph.printGAry(2);

	pmsg("\n\n\n");
*/
	return 0;
}
