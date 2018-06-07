#include "User.h"

User::User():
	id(0)
{
	
}

User::User(int id):
	id(id)
{
	
}


User::~User()
{
}

void User::addPastArticle(int id_a)
{
	pastArticleList.push_back(id_a);
}



