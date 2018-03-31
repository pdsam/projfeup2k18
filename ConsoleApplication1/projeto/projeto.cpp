// projeto.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include<fstream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <cstddef>

using namespace std;

//vetor de teste
string mystrings[] = { "ANA", "BANANA", "ERNESTO", "BANANA", "CARLA","FLAVIO"};
vector<string> words (mystrings,mystrings + 6);


//based on the quick sort algorithm
void sortVecString(vector <string> lista){
	sort(lista.begin(), lista.end());
	for (const auto& str : lista) //cout << str << ' '; //rescreve o vetor
	cout << '\n';

}
//check every if one element of the vector and the one next to it are equal
void removeDuplicates(vector <string> lista) 
//not tested 
{
	int i = 0;
	 while ( i <= lista.size()) {
		if (lista.at(i) == lista.at(i + 1))
		{
			lista.erase(lista.begin()+i);
		}
		else i++;
		
	}


}

bool test1(string line, char &a, double &sum) //validates line
{
	if (line.empty())
		return false;

	for (size_t i = 0; i < line.size(); i++)
	{
		unsigned char letter;
		letter = line[i];
		bool teste;
		teste = !isupper(letter);

		if (!(isupper(letter) || line[i] == '-' || line[i] == ';' || line[i] == ' '))
		{
			return false;
		}

	}

	if (line[0] != a)
	{
		if (line[0] != '-' && line[0] != ';')
		{
			sum = 0;
			a = line[0];
			cout << endl << line[0] << endl;
		}
	}

	return true;
}

void test3(string word, vector<string> &v, double &sum) //validates word
{
	if (word.find(" ") == -1 && word.find('-') == -1)
	{
		v.push_back(word);
		sum++;
		if (sum == 100)
		{
			cout << ".";
			sum = 0;
		}
	}
}


void test2(string line, vector<string> &v, double &sum) //search for ; divides line in to words
{
	while (line.find(';') != -1)
	{
		if (line.find(';') == line.size() - 1)
			break;
		else
			test3(line.substr(0, (line.find(';'))), v, sum); //validates the words;
		line = line.substr(line.find(';') + 2);
	}

	test3(line, v, sum);

}


int main()
{
	sortVecString(words);
	//removeDuplicates(words);
	for (int i = 0; i < words.size(); i++)
	{
		cout << words.at(i) << " ";
	}


	ifstream f;
	f.open("29765-8.txt");
	ofstream final("dicionario_end2.txt");

	//file doesn't exist
	if (!f.is_open())
	{
		cerr << "file not found!" << endl;
		exit(1);
	}

	//vector to accomodate the words for the dictionary 
	vector <string> v;
	//string to accomodate content of line 
	string line;

	double sum, total;
	char a;

	sum = 0;
	total = 0;

	//starting to process the words
	a = 'A';
	cout << a << endl;

	while (getline(f, line, '\n'))
	{
		if (test1(line, a, sum) == true) //search for lowercase letters or numbers; true  = only uppercase letters
		{
			test2(line, v, sum); //searches for the different words in the line	
		}

	}

	//import words from the vector to the file

	for (size_t i = 0; i < v.size(); i++)
	{
		final << v[i] << endl;
		total++;
	}

	cout << total << endl;

	return 0;
}

