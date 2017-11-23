#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <set>
#include <ctime>

//macros:
#define F(i,l) for( i = 0; i < l; i++)
#define Fs(i,s,l) for( i = s; i < l; i++)
#define EPNT(s) fprintf(stderr,"%s\n",s)

#define SZ 256

const int PNT = 1;

using namespace std;


int main(int argc, char ** argv)
{

	if(argc < 4)
	{
		EPNT("usage: a.out max_node, num_edges filename\n");
		exit(0);
	}

	int Num = atoi(argv[1]);

	int NE = Num-1;;

	printf("Need to make %d nodes with %d edges\n", Num, NE);


	ostringstream convert;




	int i= 0, j = 0, k = 0, fd = 0, *ip= NULL;

	double dbl = 0, *dp = NULL;

	float fl = 0.0, *flp = NULL;

	FILE * fp;

	set<int>::iterator sit;
	set<int> IS;
	vector<int> IV;
	vector<vector<int> > IVV;

	string str;

	fp = fopen(argv[3], "w");

	if(fp == NULL) 
	{
		fprintf(stderr,"error opening file %s\n",argv[3]);
		exit(0);
	}
	
	fprintf(fp,"%s\n",argv[1]);

	char buff[1] = {'\n'};
	
	//fwrite(buff,sizeof(char),1,fp);

	vector<string> frm, tw, wt, nodes;

	vector<int> FM, TW, WT, ND;

	char to, fr;

	j = 0;

	int lim;

	if( Num%2 == 0)
	{
		lim= Num/2;
	}
	else
	{
		lim = Num/2;
	}


//	printf("lim is %d\n",lim);


	//F(j, (Num/2)-1)
	F(j, lim)
	{
		FM.push_back(j+1);
		FM.push_back(j+1);
	}

	Fs(j,1, Num)
	{
		TW.push_back(j+1);
	}

	FM.resize(TW.size());


	printf("from size %d, to size %d\n",FM.size(), TW.size());


	F(j, TW.size())
	{
		srand(time(NULL)+j*time(NULL));

		int num = rand()%1000 + 1;
		F(i,100000);
		F(i,100000);
		F(i,100000);
		F(i,100000);
		WT.push_back(num);
	}

//	F(j,TW.size())
//	{
//		printf("from %d\n --Dis %d\nto %d\n", FM[j], WT[j],TW[j]);
//	}
	
	fprintf(fp,"%d\n",Num);

	F(j,TW.size())
	{
		if(j < TW.size() -1)
		{
			fprintf(fp,"%d ",FM[j]);
		}
		else
		{
			fprintf(fp,"%d\n",FM[j]);
		}
	}


	F(j,TW.size())
	{
		if(j < TW.size() -1)
		{
			fprintf(fp,"%d ",TW[j]);
		}
		else
		{
			fprintf(fp,"%d\n",TW[j]);
		}
	}

	F(j,TW.size())
	{
		if(j < TW.size() -1)
		{
			fprintf(fp,"%d ",WT[j]);
		}
		else
		{
			fprintf(fp,"%d\n",WT[j]);
		}
	}

	fprintf(fp,"%d\n",Num*2);

	fclose(fp);

	return 0;
}
