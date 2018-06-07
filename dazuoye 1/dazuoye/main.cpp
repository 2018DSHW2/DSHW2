#pragma once

#include<iostream>
#include"article_load.h"
#include"User.h"



void run()
{    
	
 	Articlesystem *ar = new Articlesystem();
//	ar->loadArticle("Data\\raw-data.txt");
	ar->loadUserTrain("data\\user-info-train.txt");
  
/*	ar->IndividualRecommendation();
	ar->ItemRecommendation();
	ar->similarRecommendation();	
	ar->WriteResult();*/
}

int main()
{
	cout<<"a";
	
	run();
	return 0;
}