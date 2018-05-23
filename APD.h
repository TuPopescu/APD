#ifndef APD_h
#define APD_h

#include <vector>
#include <list>
#include <cstring>
#include <stack>
#include <set>
#include <iostream>
using namespace std;

class APD
{
private:
	vector<vector<set<char*>> > tranzitii;
	vector<bool> stari_finale;
	stack<char> stiva;
	int nr_stari;
	int dim_alfabet;
	char *alfabet;
public:
	APD();
	APD(const int nr_stari, const int dim_alfabet);
	~APD();
	bool check_word(char *cuvant);
	friend istream& operator>>(istream& in, APD& apd);
	friend ostream& operator<<(ostream& out, APD& apd);
};
#endif //APD_h