#pragma once

#include "define.h"
using namespace std;
class User
{
public:
	int id;
	vector<int> pastArticleList;
	vector<int> recomment;
	
public:
	User();
	User(int id);
	~User();

	//operator method
	void addPastArticle(int id_a);
	void addAlternative(int id_a);

	
};
