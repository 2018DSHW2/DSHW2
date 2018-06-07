#pragma once


#include"define.h"
#include"User.h"
#define NUM_USER 5553
#define TOPNUM   30
#define TRY_TIME 5551
struct top{
	 int id;
	 double similarity;
	
};
struct listt{
	int id;
	double weight;
};
class similarReco 
{
public:
	
	vector<double> user_article_list[NUM_USER] ;
	top topp[TOPNUM];
	 listt list[1000];
	
	similarReco ();
	~similarReco();
   
	void getuserList( vector<User*>& userList);
	void getanswer();
	double paixu(double a,int id);
	double  in(double a,int id,int reduce);
};