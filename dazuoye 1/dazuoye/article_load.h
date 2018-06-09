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
	unordered_map<string, int> keyWords;
	int wordsNum;
	int keyRepeatMax;
}Article;


class Articlesystem
{
public:
    vector<User*> userList;
	vector<Article*> articleList;
	unordered_set<string> stopWord;//停用词
	unordered_map<string, int> dict;//词典，所有文章中所有出现单词出现的文档数目


public:
	Articlesystem();
	~Articlesystem();


	void loadUserTrain(string route );
	void getsimilarReco();

	void getStopWord();//获取高频词表，找一个txt然后去除
	vector<string> divideWords(string input);//分词
	unordered_map<string, int> countWords(const vector<string> input);//计算单词数量,去除停用词
	string getStem(string input);//获取词干

	void updateArticle(Article *input);//更新Article，完成分词等
	void countAll();//所有文档所有单词出现情况
	double getSimiliarity(Article*,Article*);//计算两个文档相似度
	unordered_map<string, double> getTFIDF(Article*);
	double getModulus(unordered_map<string, double>&);//计算向量的摸长
//	bool loadArticle(string route );
	void getStopWord();//获取停用词表
	vector<string> divideWords(string input);//分词
	unordered_map<string, int> countWords(const vector<string> input);//计算每个单词在所有文档中出现的次数
	string getStem(string input);//提取词干

	void updateArticle(Article *input);//对article进行分词词干提取等操作
	bool loadArticle(string route );

		
	/*void IndividualRecommendation();
	void ItemRecommendation();
	void similarRecommendation();
	void mixRecommendation();
	void showUserList();
	void showArticleList();
	void WriteResult();*/
};
