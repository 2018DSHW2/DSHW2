#pragma once

#include "define.h"
#include"User.h"
#include"similar_Recommend.h"
#include "stem.h"
using namespace std;

typedef struct Article
{
	int id;
	string title;
	string abstra;
	vector<int> users;
	unordered_map<string, double> keyWords;
	int keyRepeatMax;
}Article;


class Articlesystem
{
public:
    vector<User*> userList;
	vector<Article*> articleList;
	unordered_set<string> stopWord;


public:
	Articlesystem();
	~Articlesystem();


	void loadUserTrain(string route );
	void getsimilarReco();
	void getStopWord();//获取高频词表，找一个txt然后去除
	vector<string> divideWords(string input);//分词
	unordered_map<string, double> countWords(vector<string> input);//计算单词数量,去除停用词
	string getStem(string input);//获取词干

	void updateArticle(Article *input);//更新Article，完成分词等
//	bool loadArticle(string route );

		
	/*void IndividualRecommendation();
	void ItemRecommendation();
	void similarRecommendation();
	void mixRecommendation();
	void showUserList();
	void showArticleList();
	void WriteResult();*/
};
