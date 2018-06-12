#pragma once

#include "define.h"
#include"User.h"
#include"similar_Recommend.h"

using namespace std;

typedef struct Article
{
	int id;
	string title;
	string abstra;
	unordered_set<int> users;

	unordered_map<string, int> keyWords;
	unordered_map<string, double> TFIDF;
	double Modulus;//tfidf摸长
	int wordsNum;
	int keyRepeatMax;
}Article;


class Articlesystem
{
public:
    
	vector<Article*> articleList;
	vector<User*> userList;
	unordered_set<string> stopWord;//停用词
	unordered_map<string, int> dict;//词典，所有文章中所有出现单词出现的文档数目

public:
	Articlesystem();
	~Articlesystem();

	void outputTFIDFresult();//杈撳嚭TFIDF鐨勬帹鑽愮粨鏋?
	void loadUserTrain(string route );
	void getsimilarReco();

	void getStopWord();//获取高频词表，找一个txt然后去除
	vector<string> divideWords(string input);//分词
	unordered_map<string, int> countWords(const vector<string> input);//计算单词数量,去除停用词

	void AddUserArticle(const int ,const int);//从article到user
	void updateArticle(Article *input);//更新Article，完成分词等
	void countAll();//所有文档所有单词出现情况
	double getSimiliarity(Article*,Article*);//计算两个文档相似度
	unordered_map<string, double> getTFIDF(Article*);//计算每个文本TF-IDF向量
	double getModulus(unordered_map<string, double>&);//计算向量的摸长
//	bool loadArticle(string route );
	void updateAllArticle();
	bool loadArticle(string route );

	void  loadUserTest(string route);

	Article* Combine(vector<int>);//把一个用户的文章综合成一片

	void updateUserSimiliar();//更新所有用户的推荐文章，基于内容


		
	/*void IndividualRecommendation();
	void ItemRecommendation();
	void similarRecommendation();
	void mixRecommendation();
	void showUserList();
	void showArticleList();
	void WriteResult();*/
};


