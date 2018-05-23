#include "APD.h"

APD::APD()
{
	nr_stari = 0;
	dim_alfabet = 0;
	tranzitii.resize(nr_stari);
	stari_finale.resize(nr_stari);
	alfabet = new char[dim_alfabet];
}

APD::APD(const int nr_stari, const int dim_alfabet)
{
	this->nr_stari = nr_stari;
	this->dim_alfabet = dim_alfabet;
	tranzitii.resize(nr_stari);
	stari_finale.resize(nr_stari);
	for (int i = 0; i < nr_stari; i++)
	{
		tranzitii[i].resize(nr_stari);
		stari_finale[i] = false;
	}
	stiva.push('Z');
	alfabet = new char[dim_alfabet + 1];
}

APD::~APD()
{
	for (int i = 0; i < nr_stari; i++)
	{
		for (int j = 0; j < nr_stari; j++)
		{
			tranzitii[i][j].clear();
		}
	}
	tranzitii.clear();
	stari_finale.clear();
	delete[] alfabet;
}

bool APD::check_word(char *cuvant)
{
	char *x;
	if (strlen(cuvant) == 0)
	{
		for (int i = 0; i < nr_stari; i++)
		{
			set<char*>::iterator k = tranzitii[0][i].begin();
			while (k != tranzitii[0][i].end())
			{
				x = *k;
				if (x[0] == 'e' && stiva.top() == 'Z')
				{
					cout << "Cuvantul vid apartine APD-ului dat.\n";
					return true;
				}
				k++;
			}
		}
	}
	else
	{
		for (unsigned int i = 0; i < strlen(cuvant); i++)
		{
			if (!strchr(alfabet, cuvant[i]))
			{
				cout << "Cuvantul " << cuvant << " nu apartine alfabetului dat.\n";
				return false;
			}
		}
		int l = 0;
		char litera = cuvant[l];
		char vs = stiva.top();
		for (int i = 0; i < nr_stari; i++)
		{
			for (int j = 0; j < nr_stari; j++)
			{
				set<char*>::iterator k = tranzitii[i][j].begin();
				while (k != tranzitii[i][j].end())
				{
					x = *k;
					if (x[0] == litera && vs == x[2])
					{
						if (strlen(x) == 5)
						{
							if (x[4] != 'E')
							{
								litera = cuvant[++l];
								k = tranzitii[i][j].begin();
							}
							else
							{
								litera = cuvant[++l];
								k = tranzitii[i][j].begin();
								stiva.pop();
								vs = stiva.top();
							}
						}
						else
						{
							for (unsigned int d = 4; d < strlen(x) - 1; d++)
							{
								stiva.push(x[d]);
							}
							litera = cuvant[++l];
							k = tranzitii[i][j].begin();
							vs = stiva.top();
						}
					}
					else
					{
						k++;
					}
					if (x[0] == 'e' && stiva.top() == 'Z')
					{
						cout << "Cuvantul " << cuvant << " apartine APD-ului dat.\n";
						return true;
					}
				}
			}
		}
	}
	cout << "Cuvantul vid nu apartine APD-ului dat.\n";
	return false;
}

istream& operator>>(istream& in, APD& apd)
{
	bool x;
	in >> apd.alfabet;
	for (int i = 0; i < apd.nr_stari; i++)
	{
		in >> x;
		apd.stari_finale[i] = x;
	}
	int nr_tranzitii;
	in >> nr_tranzitii;
	int	starea_actuala, starea_urmatoare;
	char* tranzitie;
	for (int i = 0; i < nr_tranzitii; i++)
	{
		tranzitie = new char[7];
		in >> starea_actuala >> starea_urmatoare;
		in >> tranzitie;
		apd.tranzitii[starea_actuala][starea_urmatoare].insert(tranzitie);
	}
	return in;
}

std::ostream& operator<<(ostream& out, APD& apd)
{
	out << "                    PDA\nNr. stari: " << apd.nr_stari;
	out << "\nAlfabetul de intrare: " << apd.alfabet;
	out << "\nMatricea de tranzitie: \n";
	for (int i = 0; i < apd.nr_stari; i++)
	{
		for (int j = 0; j < apd.nr_stari; j++)
		{
			if (apd.tranzitii[i][j].empty())
			{
				out << "-";
			}		
			else
			{
				out << "{ ";
				for (set<char*>::iterator k = apd.tranzitii[i][j].begin(); k != apd.tranzitii[i][j].end(); k++)
				{
					out << *k;
					if (k != apd.tranzitii[i][j].end())
					{
						out << " ";
					}
					
				}	
				out << "}";
			}
			out << "   ";
		}
		out << "\n";
	}
	out << "Starile finale: ";
	for (int i = 0; i < apd.nr_stari; i++)
	{
		if (apd.stari_finale[i])
		{
			out << i << " ";
		}		
	}
	out << "\n\n";
	return out;
}
