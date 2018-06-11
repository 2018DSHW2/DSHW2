#include "mix_Recommend.h"

mixReco::mixReco()
{
	string fileName1 = "similar_result.txt";
	string fileName2 = "item_result.txt";
	ifstream inFile1(fileName1);
	if (!inFile1.is_open())
	{
		cout << "Load " << fileName1 << " failed." << endl;
	}
	ifstream inFile2(fileName2);
	if (!inFile2.is_open())
	{
		cout << "Load " << fileName2 << " failed." << endl;
	}
	ofstream outFile("result.txt");
	while (!inFile1.eof())
	{
		string temp;
		getline(inFile1, temp, ',');
		getline(inFile2, temp, ',');
		outFile << temp << ',';
		string article[5];
		getline(inFile1, article[0], ';');
		getline(inFile1, article[1], ';');
		outFile << article[0] << ';';
		outFile << article[1] << ';';
		getline(inFile2, article[2], ';');
		getline(inFile2, article[3], ';');
		getline(inFile2, article[4],';');
		outFile << article[2] << ';';
		outFile << article[3] << ';';
		outFile << article[4] << endl;
		getline(inFile1, article[1]);
		getline(inFile2, article[1]);
	}
	inFile1.close();
	inFile2.close();
	cout << "Mix Results succesfully." << endl;
}

mixReco::~mixReco()
{
}
