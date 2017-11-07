#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <set>

//macros:
#define F(i,l) for( i = 0; i < l; i++)
#define Fs(i,s,l) for( i = s; i < j; i++)
#define EPNT(s) fprintf(stderr,"%s\n",s)

#define SZ 256

const int PNT = 1;

using namespace std;


/*Basic node structure*/
class node
{
	public:
		vector<int>  adj;
		vector<vector<int> > vadj;
		int num;
		int Ival;
		float fval;
		double dval;
		long lval;
		char cval;
		string name;
		class node * parent;
}*NODE;

class graph
{
	public:
		vector<vector<int> > gph;
		int nodecnt;
		int max;
		int min;
		graph(int size,int initval);
		void SetNodes(int &i, int &j, int &wt);
}*GRAPH;

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

	

	PNTSV(sv,name);

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
	graph gph(num,SZ);


	string N,from,to,wt,chg;

	getline(cin,N);
	getline(cin,from);
	getline(cin,to);
	getline(cin,wt);
	getline(cin,chg);

	vector<int> fv,tv,wtv;

	int n = atoi(N.c_str());
	int chn = atoi(chg.c_str());

	printf("N: %d, charges: %d\n", n, chn);

	string fm = "from", tt = "to", ww = "wt";

	fv = (SVtoIV( StoSV(from,fm) ));
	tv = (SVtoIV( StoSV(to  ,tt) ));
	wtv = (SVtoIV( StoSV(wt,"wt") ));


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


	return 0;
}
