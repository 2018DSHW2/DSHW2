#pragma once

#include "define.h"
//#include"User.h"
#include"similar_Recommend.h"
#include "stem.h"
using namespace std;

typedef struct User
{
	int id;
	vector<int> past;
	vector<int> recomment;
};

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
	unordered_set<string> stopWord;//ͣ�ô�
	unordered_map<string, int> dict;//�ʵ䣬�������������г��ֵ��ʳ��ֵ��ĵ���Ŀ


public:
	Articlesystem();
	~Articlesystem();


	void loadUserTrain(string route );
	void getsimilarReco();

	void getStopWord();//��ȡ��Ƶ�ʱ���һ��txtȻ��ȥ��
	vector<string> divideWords(string input);//�ִ�
	unordered_map<string, int> countWords(const vector<string> input);//���㵥������,ȥ��ͣ�ô�
	string getStem(string input);//��ȡ�ʸ�

	void updateArticle(Article *input);//����Article����ɷִʵ�
	void countAll();//�����ĵ����е��ʳ������
	double getSimiliarity(Article*,Article*);//���������ĵ����ƶ�
	double getSimiliarity(int,int);//���������ĵ����ƶ�
	double getSimiliarity(vector<int>, int);//����һ���ĵ���һϵ���ĵ����ƶ����ƶ�
	unordered_map<string, double> getTFIDF(Article*);//����ÿ���ı�TF-IDF����
	double getModulus(unordered_map<string, double>&);//��������������
//	bool loadArticle(string route );
	void getStopWord();//��ȡͣ�ôʱ�
	vector<string> divideWords(string input);//�ִ�
	unordered_map<string, int> countWords(const vector<string> input);//����ÿ�������������ĵ��г��ֵĴ���
	string getStem(string input);//��ȡ�ʸ�

	void updateArticle(Article *input);//��article���зִʴʸ���ȡ�Ȳ���
	bool loadArticle(string route );

	void updateUserSimiliar();//���������û����Ƽ����£���������

		
	/*void IndividualRecommendation();
	void ItemRecommendation();
	void similarRecommendation();
	void mixRecommendation();
	void showUserList();
	void showArticleList();
	void WriteResult();*/
};
