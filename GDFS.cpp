#include "Ggph.h"



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



void graph::ResetG()
{
	set<node *>::iterator sit;

	SF(sit,G)
	{
		(*sit)->v = 0;
	}
}


void graph::printGAry(int t)
{
	int i = 0, j = 0;;


	vector<vector<int> > gh;

	if(t == 0) gh = gph;
	else if(t == 1) gh = Sgph;
	else gh = Lgph;

	F( i, gh.size())
	{
		printf("NODE %d:\n",i+1);
		F(j, gh[i].size())
		{
			//if(gh[i][j] < MX && i != j)
			if(i != j)
			{
				printf("---%d--->Node: %d\n", gh[i][j], j+1);
			}
		}
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

	if(PNT)printf("f size %d, t size %d, w size %d\n",f.size(), t.size(), w.size());

	gph.resize(N);
	Sgph.resize(N);
	Lgph.resize(N);

	F(i,N)
	{
		gph[i].resize(N,MX);
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
		Sgph[fm-1][to-1] = wt;
		Lgph[fm-1][to-1] = wt;


		if(type == 1)
		{
			tw->kids.insert(make_pair(wt,fr));
			gph[to-1][fm-1] = wt;
			Sgph[to-1][fm-1] = wt;
			Lgph[to-1][fm-1] = wt;
		}
		
		
		//printf("from: %d to %d is %d\n", fm,to,wt);

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



void graph::BDFS(int nd,int dis, int sn)
{

	if( GETNODE(nd+1)->v == 1)
	{
		return;
	}
	
	int i, j, k, num, dist;

	//printf("processing node %d\n", nd);

	GETNODE(nd+1)->v = 1;

	F(i,Sgph[nd].size())
	{

//		if(Sgph[nd][i] != MX && nd != i)
		if(nd != i)
		//if(Sgph[nd][i] != MX && Sgph[nd][i] != 0 && GETNODE(i+1)->v == 0)
		{
			int newdist = dis + Sgph[nd][i];

			if( newdist < Sgph[sn][i])
			{
				Sgph[sn][i] = newdist;
			}

			//if(Sgph[nd][i] != MX && GETNODE(i+1)->v == 0 ) BDFS(i, newdist, sn);
			if(Sgph[nd][i] != MX) BDFS(i, newdist, sn);

			//BDFS(i, newdist, sn);
		}
	}

	return;
}

void graph::SPBDFS()
{

	int i = 0;
	F(i,Sgph.size())
	{
		BDFS(i,0,i);


		ResetG();

//		GETNODE(i+1)->v = 1;
	}
}

void graph::GDFS(int nd, int dis, int sk, int sn)
{
	multimap<int, node *>::iterator mit;

	if(PNT)printf("processing node %d start node %d dist %d\n",nd, sn, dis);

	if(sk == nd)
	{
		if(PNT)printf("found node %d\n",sk);
	}

	node * nde = GETNODE( nd);
	node * snd = GETNODE( sn);

	if(nde->v == 1)
	{
		return;
	}

	nde->v = 1;

	MF(mit, nde->kids)
	{
		int dist = (*mit).first;
		node * child = (*mit).second;

		if(PNT) printf("child node %d dist %d\n",child->num, dist);

		if(Sgph[sn-1][child->num-1] > dist + dis)
		{
			if(PNT)printf("smaller dis %d\n", dist+dis);
			Sgph[sn-1][child->num-1] = dist + dis;
		}


		if(child->v == 0)
		{
			GDFS(child->num, dis+dist, sk, sn);
		}
	}

	return;
}

int graph::SPDFS(int sk)
{
	int i, j, k;

	set<node *>::iterator sit;

	SF(sit, G)
	{
		node * cnd = (*sit);

		GDFS(cnd->num, 0, sk, cnd->num);

		ResetG();
	}

	return 0;
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
				if(PNT)printf("dist from %d to %d is %d\n", cnode+1, to+1 , dis);
				
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
						mx = MS[dis].size();
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
							//sit = MSET.end();;
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

					printf("G[%d][%d] %d > G[%d][%d]= %d + G[%d][%d]= %d\n",i,j,G[i][j], i,k,G[i][k], k, j, G[k][j]);

				if( t == 0 && ik < MX && kj < MX && ij > ik + kj)
				{
					printf("new shortest path %d\n", ik+kj);
					G[i][j] = G[i][k] + G[k][j];
				}
				else if(( t == 1 && ik > -MX && kj > -MX && ij < ik + kj))
				{
					printf("new longest path %d\n", ik+kj);
					G[i][j] = G[i][k] + G[k][j];
				}
				else if(t == 0)pmsg("no new sp\n");
				else pmsg("no new lp\n");

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
	
	int cnt = 0;

	while(cnt < fv.size())
	{
		cin>>numb;
		cnt++;
		if(PNT)printf("num is %d\n", numb);
		wtv.push_back(numb);	
	}

	//getline(cin,wt);
	getline(cin,chg);


	int n = atoi(N.c_str());
	int chn = atoi(chg.c_str());

	printf("N: %d, charges: %d\n", n, chn);



	//convert the string vectors into integer vectors
	//wtv = (SVtoIV( StoSV(wt,"wt") ));

	//pmsg("its here\n");
	graph gph(fv, tv, wtv,n,1);
//	graph Dgph(fv, tv, wtv,n,0);
//	graph Fgph(fv, tv, wtv,n,0);
//	graph Bgph(fv, tv, wtv,n,0);

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

//	gph.printGAry(1);

//	pmsg("l\n\n\n");
	
//	gph.printGSet();

//	pmsg("\n\n\n");


	//gph.MINDIKSTRA();
	
	//gph.SPDFS(-22);
	gph.SPBDFS();
	
//	gph.printGAry(1);
//	pmsg("\n\n\n");

	gph.MXST();

	return 0;
}
