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
	double Modulus;//tfidf����
	int wordsNum;
	int keyRepeatMax;
}Article;


class Articlesystem
{
public:
    
	vector<Article*> articleList;
	vector<User*> userList;
	unordered_set<string> stopWord;//ͣ�ô�
	unordered_map<string, int> dict;//�ʵ䣬�������������г��ֵ��ʳ��ֵ��ĵ���Ŀ

public:
	Articlesystem();
	~Articlesystem();

	void outputTFIDFresult();//输出TFIDF的推荐结�?
	void loadUserTrain(string route );
	void getsimilarReco();

	void getStopWord();//��ȡ��Ƶ�ʱ���һ��txtȻ��ȥ��
	vector<string> divideWords(string input);//�ִ�
	unordered_map<string, int> countWords(const vector<string> input);//���㵥������,ȥ��ͣ�ô�

	void AddUserArticle(const int ,const int);//��article��user
	void updateArticle(Article *input);//����Article����ɷִʵ�
	void countAll();//�����ĵ����е��ʳ������
	double getSimiliarity(Article*,Article*);//���������ĵ����ƶ�
	unordered_map<string, double> getTFIDF(Article*);//����ÿ���ı�TF-IDF����
	double getModulus(unordered_map<string, double>&);//��������������
//	bool loadArticle(string route );
	void updateAllArticle();
	bool loadArticle(string route );

	void  loadUserTest(string route);

	Article* Combine(vector<int>);//��һ���û��������ۺϳ�һƬ

	void updateUserSimiliar();//���������û����Ƽ����£���������


		
	/*void IndividualRecommendation();
	void ItemRecommendation();
	void similarRecommendation();
	void mixRecommendation();
	void showUserList();
	void showArticleList();
	void WriteResult();*/
};


