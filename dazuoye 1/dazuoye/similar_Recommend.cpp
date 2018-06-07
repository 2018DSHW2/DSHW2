#include"similar_Recommend.h"
similarReco::similarReco (){}
similarReco::~similarReco(){}

double dotProduct(const vector<double>& v1, const vector<double>& v2)
{
	assert(v1.size() == v2.size());
	double ret = 0.0;
	for (vector<double>::size_type i = 0; i != v1.size(); ++i)
	{
		ret += v1[i] * v2[i];
	}
	return ret;
}

double module(const vector<double>& v)
{
	double ret = 0.0;
	for (vector<double>::size_type i = 0; i != v.size(); ++i)
	{
		ret += v[i] * v[i];
	}
	return sqrt(ret);
}

// 夹角余弦
double cosine(const vector<double>& v1, const vector<double>& v2)
{
	assert(v1.size() == v2.size());
	return dotProduct(v1, v2) / (module(v1) * module(v2));
}

double mean(const vector<double>& v)
{
	assert(v.size() != 0);
	double ret = 0.0;
	for (vector<double>::size_type i = 0; i != v.size(); ++i)
	{
		ret += v[i];
	}
	return ret / v.size();
}

double cov(const vector<double>& v1, const vector<double>& v2)
{
	assert(v1.size() == v2.size() && v1.size() > 1);
	double ret = 0.0;
	double v1a = mean(v1), v2a = mean(v2);

	for (vector<double>::size_type i = 0; i != v1.size(); ++i)
	{
		ret += (v1[i] - v1a) * (v2[i] - v2a);
	}

	return ret / (v1.size() - 1);
}

// 相关系数
double coefficient(const vector<double>& v1, const vector<double>& v2)
{
	assert(v1.size() == v2.size());
	return cov(v1, v2) / sqrt(cov(v1, v1) * cov(v2, v2));
}

// Dice 系数
double dice(const vector<double>& v1, const vector<double>& v2)
{
	assert(v1.size() == v2.size());
	return 2.0 * dotProduct(v1, v2) / (dotProduct(v1, v1) + dotProduct(v2, v2));
}

// Jaccard 系数
double jaccard(const vector<double>& v1, const vector<double>& v2)
{
	assert(v1.size() == v2.size());
	return dotProduct(v1, v2) / (dotProduct(v1, v2) + dotProduct(v2, v2) - dotProduct(v1, v2));
}

double similarReco::paixu(double a, int id){
	double temp;
	int tt;
	if(topp[TOPNUM-1].similarity<a){
		topp[TOPNUM-1].similarity=a;
		topp[TOPNUM-1].id=id;
	}
	for(int i=0;i<TOPNUM-1;i++){
		for(int j=0;j<TOPNUM-1-i;j++){
			if(topp[j].similarity<topp[j+1].similarity){
				temp=topp[j].similarity ;
				topp[j].similarity=topp[j+1].similarity ;
				topp[j+1].similarity=temp;
				tt=topp[j].id;
				topp[j].id=topp[j+1].id;
				topp[j+1].id=tt;
			}
		}
	}
	return 0;
}
double similarReco::in(double a,int id,int reduce){
	double temp;
	int tt;
	int check=0;
	for(int i=0;i<1000;i++){
		if(id==list[i].id){
			list[i].weight=list[i].weight+a;
			check=1;
			break;
		}
	}

	if(check!=1){
		list[reduce].id=id;
		list[reduce].weight=a;
	}
	for(int i=0;i<reduce;i++){
		for(int j=0;j<reduce-i;j++){
			if(list[j].weight<list[j+1].weight){
				temp=list[j].weight ;
				list[j].weight=list[j+1].weight ;
				list[j+1].weight=temp;
				tt=list[j].id;
				list[j].id=list[j+1].id;
				list[j+1].id=tt;
			}
		}
	}
	return 0;
}
void similarReco::getuserList( vector<User*>& userList){
	/*for(int jj=0;jj<NUM_USER-1;jj++){
	cout<<endl << jj+1<<endl;
	for(int i=0;i<userList[jj]->pastArticleList.size();i++){
	cout<<userList[jj]->pastArticleList[i];
	}*/
	ofstream outf;
	outf.open("similar_rusult.txt");
	cout<<"loading userlist..."<<endl;
	for(int i=1;i<NUM_USER-1;i++){
		int tmp=0; 
		for(int j=0;j<17000;j++){
			if(j==userList[i-1]->pastArticleList[tmp]){		
				user_article_list[i].push_back(170000);
				if(tmp<userList[i-1]->pastArticleList.size()-1)
					tmp++;
			}
			else
				user_article_list[i].push_back(1);}
	}


	for(int num=1;num<TRY_TIME+1;num++){
		cout<<"tt";
		int temp;
		for(int i=0;i<TOPNUM;i++){
			topp[i].similarity=0;
			topp[i].id=0; 		
		}
		for(int i=0;i<100;i++){
			list[i].id=0;
			list[i].weight=0;
		}
		cout<<"calculating cosine"; 
		for(int i=1;i<5552;i++){	
			paixu(cosine(user_article_list[num],user_article_list[i]),i);
		}

		int reduce=0;
		for(int i=0;i<TOPNUM;i++){
			/* cout<<topp[i].similarity<<"  ";
			cout<<topp[i].id; 
			cout<<endl;*/
			reduce=reduce+userList[topp[i].id-1]->pastArticleList.size();

		}


		int add;
		for(int i=0;i<TOPNUM;i++){
			for(int j=0;j<userList[topp[i].id]->pastArticleList.size();j++){
				in( topp[i].similarity,userList[topp[i].id]->pastArticleList[j] ,reduce+1);
			}
		}
		cout<<"list list "<<endl;
		int cal=0;
		outf<<num<<",";
		for(int i=0;i<100;i++){
			if(list[i].weight<1){
				cout<<list[i].id<<"  "<<list[i].weight<<endl;

				outf<<list[i].id;
				cal++;

				if(cal>4){
					break;}
				else outf<<";";
			}
		}


		outf<<endl;

	}
	outf.close();
}