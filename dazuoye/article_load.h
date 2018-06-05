#pragma once
#include<vector>
#include <map>
#include<string>
#include <hash_map>
#include <unordered_map>
using namespace std;
#define NUM_OF_USER 5552//����û�����
#define ARTICLE_LIST_NUM 160000//

typedef struct ArticleNode
{
	int id;

	map<string,int> divde;//�ִʽ��,û���ʳ��ִ���
	string content;//�ı�����
}ArticleNode;

typedef struct WordNode
{
	string content;
	map<int,int> info;//�ĵ�id,���ִ���

}WordNode;

class Article
{
public:
	 int USERLIST[NUM_OF_USER];
	 int ARTICLELIST [ARTICLE_LIST_NUM];


public:
	Article();
	~Article();

	vector<ArticleNode> my_article;//�ĵ��ִʽ��
	unordered_map<string, WordNode*> my_word;//�����ĵ�

	bool loadUserTrain(string route);//�û�ƫ��

	bool loadArticle(string route);//�����ı�

	


	
	void IndividualRecommendation();
	void ItemRecommendation();
	void similarRecommendation();

	void mixRecommendation();

	void showUserList();
	void showArticleList();
	void WriteResult();
};
