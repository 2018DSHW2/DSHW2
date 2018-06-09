#pragma once

#include"article_load.h"

Articlesystem::Articlesystem()
{
	getStopWord();
}

Articlesystem::~Articlesystem()
{
}
void Articlesystem::loadUserTrain(string route ){
	ifstream file(route);

	if (!file.is_open())
	{
		cout << "Load " << route << " failed." << endl;
		return ;
	}
	
	int id_count = 0;
	
	User *p_user;
	while (!file.eof())
	{
		int id_s, article_s;
		string temp; 
		
		getline(file, temp, ',');
		id_s = stoi(temp);
		getline(file, temp);
		article_s = stoi(temp);
		
		if (id_s != id_count)
		{   
			id_count = id_s;
			p_user = new User(id_count);
			userList.push_back(p_user);
			p_user->addPastArticle(article_s);
		}
		else
		{
			p_user->addPastArticle(article_s);
		}
	} 
	/*for(int i=0;i<userList[0]->pastArticleList.size();i++)
	cout<<userList[0]->pastArticleList[i]<<endl;*/
	file.close();
	cout << "Load " << route << " succesfully." << endl;
	getsimilarReco();
	return ;
}

/*
bool loadArticle(string route ){
return 0;}
=======
>>>>>>> 08559581f033cbb8c7b530b3ca07af5ba271187f

//load "raw-data"
bool Articlesystem::loadArticle(string route )
{
	ifstream file(route);

	if (!file.is_open())
	{
		cout << "Load " << route << " failed." << endl;
		return false;
	}
	int id_count = 0;

	Article *p_article;
	while (!file.eof())
	{
		string temp;

		getline(file, temp, ',');
		p_article->id = stoi(temp);
		getline(file, temp, '"');
		getline(file, temp, '"');
		p_article->title = temp;
		getline(file, temp, '"');
		getline(file, temp, '"');
		p_article->abstra = temp;
		while (p_article->abstra[p_article->abstra.length() - 1] != '"')
		{
			getline(file, temp, '"');
			p_article->abstra += temp;
		}
		articleList.push_back(p_article);
	}
	file.close();
	cout << "Load " << route << " succesfully." << endl;
	return true;
}

/*
	
	void IndividualRecommendation(){}
	void ItemRecommendation(){}
	void similarRecommendation(){}

	void mixRecommendation(){}

	void showUserList(){}
	void showArticleList(){}
	void WriteResult(){}*/

void Articlesystem::getsimilarReco()
{
	//SocialRecommendSolution *s = new SocialRecommendSolution(userList, articleList.size());
	similarReco *s = new similarReco();
	//s->loadAnswerFromFile("TestData\\answer1.txt");
	s->getuserList(userList);
}

void Articlesystem::updateArticle(Article* input)
{
	vector<string> word = divideWords(input->abstra);
	vector<string> temp = divideWords(input->title);
	word.insert(word.end(),temp.begin(),temp.end());
	vector<string>::iterator itr;
	for (itr = word.begin(); itr !=  word.end(); itr++)
	{
		if (stopWord.find(*itr) != stopWord.end())
		{
			itr = word.erase(itr);
		}
		else
		{
			continue;
		}
	}//È¥³ýÍ£ÓÃ´Ê
	input->wordsNum = word.size();
	input->keyWords = countWords(word);
	
}

unordered_map<string, int>Articlesystem::countWords(const vector<string> input)
{
	unordered_map<string, int> output;
	for (int i = 0; i < input.size(); i++)
	{

		if (output.find(input[i]) == output.end())
		{
			output.insert(pair<string,int>(input[i], 1));
		}
		else
		{
			output[input[i]] += 1;
		}
	}
	return output;
}

void Articlesystem::getStopWord()
{
	stopWord.clear();
	string a;
	ifstream file(STOPWORD_PATH);
	while (!file.eof())
	{
		file >> a;
		stopWord.insert(a);
	}
	return;

}

string Articlesystem::getStem(string  input)
{
	return stemword(input);
}

//0609update
vector<string> Articlesystem::divideWords(string input)
{
	vector<string> output;
	string delimiters = " ,.;''""\n\r~!1234567890?@#$%^&*()_+|`-=/{}[]:/'<>";//分隔符
	string temp;
	int i = 0, j = 0;
	while (i < input.length())
	{
		while (input[i] != delimiters[j])
		{
			if (j == delimiters.length() - 1)
				break;
			j++;
		}
		if (input[i] != delimiters[j])//input[i]不是分隔符
		{
			temp = +input[i];
			j = 0;
			i++;
		}
		else
		{
			if (temp.length() != 0)
			{
				output.push_back(temp);
				temp = "";
			}
			j = 0;
			i++;
		}
		
	}
	
}

void Articlesystem::countAll()
{
	dict.clear();
	unordered_map<string, int>::iterator itr;
	for (int i = 0; i < articleList.size(); i++)
	{
		unordered_map<string, int> temp = articleList.at(i)->keyWords;
		for (itr = temp.begin(); itr != temp.end(); itr++)
		{
			if (dict.find(itr->first) == dict.end())
			{
				dict.insert(pair<string, int>(itr->first, itr->second));
			}
			else
			{
				dict[itr->first] += 1;
			}
		}
	}
}
/////////////////////

double Articlesystem::getSimiliarity(Article* input1, Article* input2)
{
	unordered_map<string, double> tf1,tf2;
	tf1 = getTFIDF(input1);
	tf2 = getTFIDF(input2);
	unordered_map<string, double>::iterator itr;
	double res  = 0;
	for (itr = tf1.begin(); itr != tf1.end(); itr++)
	{
		if (tf2.find(itr->first) != tf2.end())
		{
			res += (itr->second * tf2.find(itr->first)->second);
		}
		else
		{
			continue;
		}
	}
	return res / getModulus(tf1) / getModulus(tf2);
}

unordered_map<string, double> Articlesystem::getTFIDF(Article *input)
{
	unordered_map<string, double> output;
	unordered_map<string, int>::iterator itr;
	for (itr = input->keyWords.begin(); itr != input->keyWords.end(); itr++)
	{
		double temp = double(itr->second) / double(input->wordsNum) * log(double(articleList.size()) / double(dict.find(itr->first)->second + 1));//TF*IDF
		output.insert(pair<string,double>(itr->first,temp));
	}
	return output;
}

double Articlesystem::getModulus(unordered_map<string, double>& input)
{
	double res = 0.0;
	unordered_map<string, double>::iterator itr;
	for (itr = input.begin(); itr != input.end(); itr++)
	{
		res += (itr->second * itr->second);
	}
	return sqrt(res);
}
