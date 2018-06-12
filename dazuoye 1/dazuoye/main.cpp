#include<iostream>
//#include"article_load.h"
//#include"User.h"
#include "define.h"
#include "article_load.h"
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
	Articlesystem* a = new Articlesystem();
	a->loadArticle(ARTICLE_PATH);
	a->loadUserTrain(USERTRAIN_PATH);
	a->loadUserTest(USSERTEST_PATH);
	a->updateUserSimiliar();
	
	
}

int main()
{
	test();
//	run();
	system("pause");
	return 0;
}