
#include "stem.h"
#include"article_load.h"

Articlesystem::Articlesystem()
{
	getStopWord();
	userList.clear();
}

Articlesystem::~Articlesystem()
{
}

void Articlesystem::outputTFIDFresult()
{
	vector<User*>::iterator it1;
	int i = 1;
	ofstream outFile("item_result.txt");
	for (auto it1:  userList)
	{
		outFile << i << ',';
		i++;
		vector<User*>::iterator it2;
		for (auto it2 : it1->recomment)
			outFile << it2 << ';';
		outFile << endl;
	}
	outFile.close();
	cout << "get TFIDF Results succesfully." << endl;
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
		if (temp == "")
		{
			break;
		}
		id_s = stoi(temp);
		getline(file, temp);
		article_s = stoi(temp);
		
		if (id_s != id_count)
		{   
			p_user = new User();
			id_count = id_s;
			p_user->id = id_count;
			userList.push_back(p_user);
			p_user->pastArticleList.push_back(article_s);
			AddUserArticle(p_user->id, article_s);
		}
		else
		{
			p_user->pastArticleList.push_back(article_s);
			AddUserArticle(p_user->id, article_s);
		}		
	} 
	/*for(int i=0;i<userList[0]->pastArticleList.size();i++)
	cout<<userList[0]->pastArticleList[i]<<endl;*/
	file.close();
	cout << "Load " << route << " succesfully." << endl;
//	getsimilarReco();
	return ;
}

void Articlesystem::AddUserArticle(const int userid,const int articleid)
{
	articleList[articleid - 1]->users.insert(userid);
}


bool Articlesystem::loadArticle(string route )
{
	getStopWord();
	ifstream file(route);

	if (!file.is_open())
	{
		cout << "Load " << route << " failed." << endl;
		return false;
	}

	Article *p_article;
	while (!file.eof())
	{

		p_article=new Article;
		string temp;

		getline(file, temp, ',');
		if (temp == "")
		{
			break;
		}
		p_article->id = stoi(temp);
		getline(file, temp, '"');
		getline(file, temp, '"');
		p_article->title = temp;
		
		getline(file, temp, '"');
		getline(file, temp, '"');
		p_article->abstra = temp;
		
		articleList.push_back(p_article);
		
		cout<<p_article->id <<endl;
		updateArticle(p_article);
		//p_article->abstra.clear();
		//p_article->title.clear();
		
	}
	countAll();
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
	for (itr = word.begin(); itr !=  word.end(); )
	{
		if (stopWord.find(*itr) != stopWord.end())
		{
			itr = word.erase(itr);
		}
		else
		{
			itr++;
			continue;
		}
	}//去除停用词
	temp.clear();
	for (int i = 0; i < word.size(); i++)
	{
		temp.push_back(stemword(word[i]));
	}
	input->wordsNum = temp.size();
	input->keyWords = countWords(temp);
	

}

void Articlesystem::updateAllArticle()
{
	for (int i = 0; i < articleList.size(); i++)
	{
		updateArticle(articleList[i]);
	}
	countAll();
	return;
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

//0609update
vector<string> Articlesystem::divideWords(string input)
{
	vector<string> output;
	string delimiters = " ,.;''""\n\\\r~!\1234567890?@#$%^&*()_+|`=/{}[]:/<>";//分隔符
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
			if (input[i] >= 'A' && input[i] <= 'Z')
			{
				temp += (input[i] - 'A' + 'a');

			}
			else
			{
				temp += input[i];
			}
			
			j = 0;
			i++;
		}
		else
		{
			if (temp.length() >=1)//只分出长度大于1的词
			{
				output.push_back(temp);
				temp = "";
			}
			j = 0;
			i++;
		}
		
	}
	return output;

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
	}//构建词典

	for (int i = 0; i < articleList.size(); i++)
	{
		articleList[i]->TFIDF = getTFIDF(articleList[i]);
		articleList[i]->Modulus = getModulus(articleList[i]->TFIDF);
	}
	//计算TFIDF值
}
/////////////////////

double Articlesystem::getSimiliarity(Article* input1, Article* input2)
{
	unordered_map<string, double>::iterator itr;
	double res  = 0;
	for (itr = input1->TFIDF.begin(); itr != input1->TFIDF.end(); itr++)
	{
		if (input2->TFIDF.find(itr->first) != input2->TFIDF.end())
		{
			res += (itr->second * input2->TFIDF.find(itr->first)->second);
		}
		else
		{
			continue;
		}
	}
	return res / input1->Modulus / input2->Modulus;
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

Article* Articlesystem::Combine(vector<int> input)
{
	Article* output = new Article;
	output->TFIDF.clear();
	for (int i = 0; i < input.size(); i++)
	{
		unordered_map<string, double>::iterator itr,itr2;
		for (itr = articleList[input[i] - 1]->TFIDF.begin();itr != articleList[input[i] - 1]->TFIDF.end();itr++)
		{
			itr2 = (output->TFIDF).find(itr->first);
			if (itr2 == output->TFIDF.end())
			{
				output->TFIDF.insert(pair<string, double>(itr->first, itr->second));
			}
			else
			{
				itr2->second += itr->second;
			}
		}
		
	}
	output->Modulus = getModulus(output->TFIDF);
	return output;
}

void Articlesystem::updateUserSimiliar()
{
	for (int i = 0;i < userList.size();i++)
	{
		Article* com = Combine(userList[i]->pastArticleList);
		int temp1[MAX_CB_NUM] = { -1 },min_id = 0;
		double temp2[MAX_CB_NUM] = { -1 },min = -1,t;
		for (int j = 0; j < articleList.size(); j++)
		{
			if(articleList[j]->users.find(userList[i]->id ) == articleList[j]->users.end())//不是用户已有的
			{
				t = getSimiliarity(com, articleList[j]);//相似度
				if (t > min)//需要进行插入
				{
					temp1[min_id] = j;
					temp2[min_id] = t;					
					min = temp2[0];
					for (int p = 1; p < MAX_CB_NUM; p++)
					{
						if (temp2[p] < min)
						{
							min = temp2[p];
							min_id = p;
						}
					}
				}
			}
			else
			{
				continue;
			}
		}
		userList[i]->recomment.clear();
		delete(com);
		for (int j = 0; j < MAX_CB_NUM; j++)
		{
			if (temp1[j] != -1)
			{
				userList[i]->recomment.push_back(temp1[j] + 1);
			}			
		}//加入推荐文章
	}
}
