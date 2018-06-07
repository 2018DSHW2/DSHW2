#pragma once

#include "define.h"
using namespace std;
class User
{
public:
	int id;
	vector<int> pastArticleList; //int equals WeightArticle but weight = 1 or 0
	
public:
	User();
	User(int id);
	~User();

	//operator method
	void addPastArticle(int id_a);
	void addAlternative(int id_a);

	
};
