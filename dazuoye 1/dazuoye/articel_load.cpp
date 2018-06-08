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

//load "raw-data"
bool Articlesystem::loadArticle(string route )
{
	ifstream file(route);

	if (!file.is_open())
	{
		cout << "Load " << route << " failed." << endl;
		return false;
	}
	int id_count = 0;

	Article *p_article;
	while (!file.eof())
	{
		string temp;

		getline(file, temp, ',');
		p_article->id = stoi(temp);
		getline(file, temp, '"');
		getline(file, temp, '"');
		p_article->title = temp;
		getline(file, temp, '"');
		getline(file, temp, '"');
		p_article->abstra = temp;
		while (p_article->abstra[p_article->abstra.length() - 1] != '"')
		{
			getline(file, temp, '"');
			p_article->abstra += temp;
		}
		articleList.push_back(p_article);
	}
	file.close();
	cout << "Load " << route << " succesfully." << endl;
	return true;
}

/*
	
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
	vector<string> word = divideWords(input->abstra);
	vector<string>::iterator itr;
	for (itr = word.begin(); itr !=  word.end(); itr++)
	{
		if (stopWord.find(*itr) != stopWord.end())
		{
			itr = word.erase(itr);
		}
		else
		{
			continue;
		}
	}//È¥³ýÍ£ÓÃ´Ê
	unordered_map<string,double> a = countWords(word);

}

unordered_map<string, double>Articlesystem::countWords(const vector<string> input)
{
	unordered_map<string, double> output;
	for (int i = 0; i < input.size(); i++)
	{

		if (output.find(input[i]) == output.end())
		{
			output.insert(pair<string,double>(input[i], 1.0));
		}
		else
		{
			output[input[i]] += 1.0;
		}
	}
	return output;
}

void Articlesystem::getStopWord()
{
	stopWord.clear();
	string a;
	ifstream file(STOPWORD_PATH);
	while (!file.eof())
	{
		file >> a;
		stopWord.insert(a);
	}
	return;

}

string Articlesystem::getStem(string  input)
{
	return stemword(input);
}

vector<string> Articlesystem::divideWords(string input)
{
	vector<string> output;

}


/////////////////////
