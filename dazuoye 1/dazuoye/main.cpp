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
	a->getStopWord();
	Article* temp;
	temp = new Article;
	temp->abstra = "I am a student.";
	temp->id = 1;

	a->articleList.push_back(temp);

	temp = new Article;
	temp->id = 2;
	temp->abstra = "We are teachers.";
	a->articleList.push_back(temp);

	a->updateAllArticle();
	
	
}

int main()
{
	test();
//	run();
	system("pause");
	return 0;
}