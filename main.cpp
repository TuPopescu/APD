#include <iostream>
#include <fstream>
#include "APD.h"
using namespace std;

int main()
{
	int x, y;
	char *cuvant;
	bool gata = false;
	ifstream fin("APD.txt");
	if (!fin.is_open())
	{
		cout << "Nu s-a putut deschide fisierul.";
	}
	else
	{
		fin >> x >> y;
		APD apd(x, y);
		fin >> apd;
		cout << apd;
		while (!gata)
		{
			cuvant = new char[100];
			fin >> cuvant;
			apd.check_word(cuvant);
			cout << "1 - am terminat\n0 - mai citesc un cuvant\n";
			cin >> gata;
		}
		fin.close();
	}
	

	cout << endl;
	system("pause");
	return 0;
}