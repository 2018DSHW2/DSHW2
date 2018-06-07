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
	void getStopWord();//��ȡ��Ƶ�ʱ���һ��txtȻ��ȥ��
	vector<string> divideWords(string input);//�ִ�
	unordered_map<string, double> countWords(vector<string> input);//���㵥������,ȥ��ͣ�ô�
	string getStem(string input);//��ȡ�ʸ�

	void updateArticle(Article *input);//����Article����ɷִʵ�
//	bool loadArticle(string route );

		
	/*void IndividualRecommendation();
	void ItemRecommendation();
	void similarRecommendation();
	void mixRecommendation();
	void showUserList();
	void showArticleList();
	void WriteResult();*/
};
