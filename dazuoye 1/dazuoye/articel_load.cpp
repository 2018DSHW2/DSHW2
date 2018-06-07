#pragma once

#include"article_load.h"

Articlesystem::Articlesystem()
{
	getStopWord();
}


Articlesystem::~Articlesystem()
{
}
void Articlesystem::loadUserTrain(string route ){
	ifstream file(route);

	if (!file.is_open())
	{
		cout << "Load " << route << " failed." << endl;
		return ;
	}
	
	int id_count = 0;
	
	User *p_user;
	while (!file.eof())
	{
		int id_s, article_s;
		string temp; 
		
		getline(file, temp, ',');
		id_s = stoi(temp);
		getline(file, temp);
		article_s = stoi(temp);
		
		if (id_s != id_count)
		{   
			id_count = id_s;
			p_user = new User(id_count);
			userList.push_back(p_user);
			p_user->addPastArticle(article_s);
		}
		else
		{
			p_user->addPastArticle(article_s);
		}
	} 
	/*for(int i=0;i<userList[0]->pastArticleList.size();i++)
	cout<<userList[0]->pastArticleList[i]<<endl;*/
	file.close();
	cout << "Load " << route << " succesfully." << endl;
	getsimilarReco();
	return ;
}
/*
bool loadArticle(string route ){
return 0;}

	


	
	void IndividualRecommendation(){}
	void ItemRecommendation(){}
	void similarRecommendation(){}

	void mixRecommendation(){}

	void showUserList(){}
	void showArticleList(){}
	void WriteResult(){}*/


void Articlesystem::getsimilarReco()
{
	//SocialRecommendSolution *s = new SocialRecommendSolution(userList, articleList.size());
	similarReco *s = new similarReco();
	//s->loadAnswerFromFile("TestData\\answer1.txt");
	s->getuserList(userList);
}

void Articlesystem::updateArticle(Article* input)
{

}

void Articlesystem::getStopWord()
{

}