#include<iostream>
//#include"article_load.h"
//#include"User.h"
#include "stem.h"
using namespace std;
/*
void run()
{    
	
 	Articlesystem *ar = new Articlesystem();
//	ar->loadArticle("Data\\raw-data.txt");
	ar->loadUserTrain("data\\user-info-train.txt");
  
/*	ar->IndividualRecommendation();
	ar->ItemRecommendation();
	ar->similarRecommendation();	
	ar->WriteResult();
}/
**/
void test()
{
	string a = string("pencils");
	cout<<stemword(a);
}

int main()
{
	test();
//	run();
	system("pause");
	return 0;
}