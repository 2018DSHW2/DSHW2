#pragma once

#include "define.h"
using namespace std;

class Article
{
public:
	int id;
	string title;
	string abstra;
	vector<int> users;
//	hash_map<string, double> keyWords;
	int keyRepeatMax;

public:
	Article();
	Article(int id);
	~Article();

	//debug method
	void showArticle();
};

