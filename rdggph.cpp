#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <set>
#include <map>
#include <ctime>

//macros:
#define F(i,l) for( i = 0; i < l; i++)
#define Fs(i,s,l) for( i = s; i < j; i++)
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

	map<int,int> done;


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
	
	vector<string> frm, tw, wt, nodes;

	vector<int> FW, TW, WT, ND, W;

	char to, fr;

	j = 0;

	F(j , Num)
	{
	
		FW.push_back(j+1);
	
	}

	F(j, 1000)
	{
		WT.push_back(j+1);
	}



	convert.str().erase(0, convert.str().size());


	for(i = 0; i < NE; i++)
	{
		//srand(time(NULL));
		srand(time(NULL)+i);
		//sleep(2000);
	printf("herere\n");	
		clock_t start_time = clock();
		clock_t end_time = 5 * 1000 + start_time;
		while(clock() < end_time);

		fr = rand()%Num + 1;

		while(fr == FW[i])
		{
	printf("herere\n");	
			srand(time(NULL)+i);
			start_time = clock();
			end_time = 5 * 1000 + start_time;
			while(clock() < end_time);

			fr = rand()%Num+1;

		}

		TW.push_back(fr);

		srand(time(NULL)+i*2);
		start_time = clock();
		end_time = 5 * 1000 + start_time;
		while(clock() < end_time);


		int len = rand()%1000;

		if( done.find(WT[len]) == done.end()) 
		{
			done[WT[len]] = 1;

			W.push_back(len+1);


		}
		else if( done[ WT[len] ] < Num/4)
		{	
			done[WT[len]] +=1;
			W.push_back(len+1);
		}
		
	}


	fprintf(fp,"%d\n",Num);

	printf("herere\n");	
	F(j, TW.size())
	{

		if(j < TW.size()-1)
		{
			fprintf(fp,"%d ",FW[j]);
		}
		else
		{
			fprintf(fp,"%d\n",FW[j]);
		}
	}


	printf("herere\n");	
	F(j, TW.size())
	{

		if(j < TW.size()-1)
		{
			fprintf(fp,"%d ",TW[j]);
		}
		else
		{
			fprintf(fp,"%d\n",TW[j]);
		}
	}

	F(j, TW.size())
	{

		if(j < W.size()-1)
		{
			fprintf(fp,"%d ",W[j]);
		}
		else
		{
			fprintf(fp,"%d\n",W[j]);
		}
	}

	printf("herere\n");	
	fprintf(fp,"%d\n",Num);

	fclose(fp);

	return 0;

}
