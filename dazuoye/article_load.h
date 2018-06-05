#pragma once
#include<vector>
#include <map>
#include<string>
#include <hash_map>
#include <unordered_map>
using namespace std;
#define NUM_OF_USER 5552//最大用户数量
#define ARTICLE_LIST_NUM 160000//

typedef struct ArticleNode
{
	int id;

	map<string,int> divde;//分词结果,没个词出现次数
	string content;//文本内容
}ArticleNode;

typedef struct WordNode
{
	string content;
	map<int,int> info;//文档id,出现次数

}WordNode;

class Article
{
public:
	 int USERLIST[NUM_OF_USER];
	 int ARTICLELIST [ARTICLE_LIST_NUM];


public:
	Article();
	~Article();

	vector<ArticleNode> my_article;//文档分词结果
	unordered_map<string, WordNode*> my_word;//倒排文档

	bool loadUserTrain(string route);//用户偏好

	bool loadArticle(string route);//加载文本

	


	
	void IndividualRecommendation();
	void ItemRecommendation();
	void similarRecommendation();

	void mixRecommendation();

	void showUserList();
	void showArticleList();
	void WriteResult();
};
