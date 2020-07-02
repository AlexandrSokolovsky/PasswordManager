#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <time.h> 
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm>

using namespace std;

#include "PasswordEnDecoder.h"
#include "PasswordGenerator.h"


bool check_file(char* path, FILE* fp);
void del_clones(vector<PasswordGenerator>& v);
void sort_by_alph(vector<PasswordGenerator>& v);
void append_password(vector<PasswordGenerator>& v);
void del_pass_by_number(vector<PasswordGenerator>& v);
void open_all_passwords(vector<PasswordGenerator>& v, string m_p);
void open_num_password(vector<PasswordGenerator>& v, string m_p);
bool input_main_pass(string m_p, string main_pass);
void passwords(vector<PasswordGenerator>& v);
char* scan_from_file(vector<PasswordGenerator>& v, char* path, FILE* fp);
void copy_to_file(vector<PasswordGenerator>& v, char* path, FILE* fp,string m_p);
int choise(vector<PasswordGenerator>& v, string main_pass);


int main()
{
	srand(time(NULL));
	vector<PasswordGenerator> test_v;    
	int flag1 = 7;
	bool flag = 0;	
	bool f = 0;
	
	FILE *fp = 0;
	char path[] = "EPasswords.txt";

	
	string main_pass;				//main password for decrypt passwords and scan from file

	

	

	f = check_file(path, fp);

	system("cls");
	if (f)
	{
		system("cls");

		cout << "0...............Create new PasswordManager" << endl;
		cout << "1...............Scan from File" << endl;

		cin >> flag;
		if (flag)
		{
			main_pass=string(scan_from_file(test_v, path, fp));
			do {				
				flag1=choise(test_v, main_pass);
			} while (flag1 != 0);
		}
		else
		{
			cout << "Input main pass:" << endl;
			cin >> main_pass;
			do {
				flag1 = choise(test_v, main_pass);
			} while (flag1 != 0);
		}
	}
	else
	{
		cout << "Input main pass:" << endl;
		cin >> main_pass;
		do {		
			flag1=choise(test_v,main_pass);
		} while (flag1 != 0);
	}



	copy_to_file(test_v, path, fp,main_pass);

	system("pause");
	return 0;
}





bool check_file(char* path, FILE* fp)
{
	if ((fp = fopen(path, "r")) != NULL)
	{
		cout << "You can read data from File";
		return 1;
	}

	return 0;
}


void passwords(vector<PasswordGenerator>& v)
{

	
		cout << "|----| |--------------------------------| |--------------------| |--------| |----Key----|" << endl;		
		cout << "|-ID-| |--------------Name--------------| |---------Pass-------| |-Length-| |A-Z|a-z|0-9|" << endl;
		cout << "|----| |--------------------------------| |--------------------| |--------| |-----------|" << endl;
		for (int i = 0; i < v.size(); i++)
		{
			cout << "|";
			cout << setw(4) << left << i;
			cout << "|";

			cout << " |";
			cout << setw(32) << left << v[i].getAllData().pass_name;
			cout << "|";

			cout << " |";
			cout << setw(20) << left << v[i].getAllData().epass;
			cout << "|";

			cout << " |";
			cout << setw(4) << left << v[i].getAllData().length<<"/ 20"<< setw(1);
			cout << "|";

			cout << " |";
			cout << setw(3) << left << v[i].getAllData().cap_letter<<"|" << setw(3) << v[i].getAllData().low_letter << "|" << setw(3) << v[i].getAllData().numbers;
			cout << "|";

			cout << "\n|----| |--------------------------------| |--------------------| |--------| |-----------|" << endl;


		}


}

void del_clones(vector<PasswordGenerator>& v)		
{



	for (int i = 0; i < v.size(); i++)
	{
		for (int j = 0; j < v.size(); j++)
		{
			if ((v[i].getAllData().pass_name == v[j].getAllData().pass_name)&&(i!=j))
				v.erase(v.begin() + i);
			

		}
	}
}

void sort_by_alph(vector<PasswordGenerator>& v)
{
		
	for (int i = 0; i < v.size(); i++)
	{
		for (int j = 0; j < v.size(); j++)
		{
			if (v[i].getAllData().pass_name < v[j].getAllData().pass_name)			
				swap(v[i], v[j]);
			
		}
	}

}

void append_password(vector<PasswordGenerator>& v)
{
	string name;
	int  length = 0;
	bool numb = 0;
	bool cap = 0;
	bool low = 0;

	cout << "Input length and  keys 1 or 0 for: length numb cap_letters low_letters" << endl;
	cin >> length >> numb >> cap >> low;
	
	PasswordGenerator help(length, numb, cap, low);
	
	v.push_back(help);	
}

void del_pass_by_number(vector<PasswordGenerator>& v)
{
	int number = 0;

	cout << "Input number:";
	cin >> number;
	v.erase(v.begin() + number);

}

void open_all_passwords(vector<PasswordGenerator>& v, string m_p)
{
	string main_pass;

	cout << "Input main pass:" << endl;
	cin >> main_pass;

	string help;

	if (input_main_pass(m_p,main_pass))
	{
		for (int i = 0; i < v.size(); ++i)
		{			
			if (v[i].getAllData().real == 0)
			{
				v[i].change_en_de();
			}
			else
			{
				cout << "Password number: "<<i<<" has already been decrypted " << endl;
			}
		}
	}
	else
	{
		cout << "Wrong main password" << endl;
	}
}

void open_num_password(vector<PasswordGenerator>& v, string m_p)
{
	
	int num=0;
	cout << "Input number:" << endl;
	cin >> num;

	if (v[num].getAllData().real == 0)
	{
		string main_pass;
		string help;

		cout << "Input main pass:" << endl;
		cin >> main_pass;

		if (input_main_pass(m_p, main_pass))
		{
			v[num].change_en_de();
		}
		else
		{
			cout << "Wrong main password" << endl;
		}
	}
	else
	{
		cout << "Password has already been decrypted " << endl;
	}
	
}

bool input_main_pass(string m_p, string main_pass)
{

	return(main_pass == m_p);
		
}


char* scan_from_file(vector<PasswordGenerator>& v, char* path, FILE* fp)
{
	int count_passwords=0;	
	char* mp = new  char[255];
	fopen(path, "r");
	fp = fopen(path, "r");

	fscanf(fp, "%d", &count_passwords);
	fscanf(fp, "%s", mp);

	string m_p = "";
	cout << "Input main password:";
	cin >> m_p;

	while (mp != m_p)
	{
		cout << "Wrong main password!" << endl;
		cout << "Input main password:";
		cin >> m_p;
		cout << "" << endl;
		system("cls");		
	}	

	for (int i = 0; i < count_passwords; ++i)		
	{
		PasswordGenerator help(10, 1, 0, 0, "help");

		int cl = 0;
		int ll = 0;
		int nm = 0;
		
		char* dp = new  char[255];	
		char* ep = new  char[255];
		int rl = 0;
	
		char* pn = new  char[255];
		int len = 0;

		char* mp = new  char[255];


			fscanf(fp, "%d", &cl);
			fscanf(fp, "%d", &ll);
			fscanf(fp, "%d", &nm);


			fscanf(fp, "%s", ep);
			fscanf(fp, "%s", dp);
			fscanf(fp, "%d", &rl);
			fscanf(fp, "%s", pn);
			fscanf(fp, "%d", &len);
			
			help.setDate_fromfile(cl, ll, nm, ep, dp, rl, pn, len);
			v.push_back(help);

	}
		
	fclose(fp);
	return mp;
}


void copy_to_file(vector<PasswordGenerator>& v, char* path, FILE* fp, string m_p)
{
	int count_passwords = v.size();
	fopen(path, "w+");
	fp = fopen(path, "w+");


	string mp = m_p;
	char * mp1 = new char[mp.size() + 1];
	copy(mp.begin(), mp.end(), mp1);
	mp1[mp.size()] = '\0';


	fprintf(fp, "%d", count_passwords);
	fprintf(fp, " ");
	fprintf(fp, "%s", mp1);	
	fprintf(fp, "\n");


	for (int i = 0; i < count_passwords; i++)
	{

		string pn = v[i].getAllData().pass_name;
		char * pn1 = new char[pn.size() + 1];
		copy(pn.begin(), pn.end(), pn1);
		pn1[pn.size()] = '\0';

		string dp = v[i].getAllData().depass;
		char * dp1 = new char[dp.size() + 1];
		copy(dp.begin(), dp.end(), dp1);
		dp1[dp.size()] = '\0';

		string ep = v[i].getAllData().epass;
		char * ep1 = new char[ep.size() + 1];
		copy(ep.begin(), ep.end(), ep1);
		ep1[ep.size()] = '\0';

		

	

		fprintf(fp, "%d", v[i].getAllData().cap_letter);
		fprintf(fp, " ");
		fprintf(fp, "%d",v[i].getAllData().low_letter);
		fprintf(fp, " ");
		fprintf(fp, "%d", v[i].getAllData().numbers);
		fprintf(fp, " ");

		fprintf(fp, "%s", ep1);
		fprintf(fp, " ");
		fprintf(fp, "%s", dp1);
		fprintf(fp, " ");
		fprintf(fp, "%d", v[i].getAllData().real);
		fprintf(fp, " ");

		fprintf(fp, "%s", pn1);
		fprintf(fp, " ");
		fprintf(fp, "%d", v[i].getAllData().length);
		fprintf(fp, " ");

		fprintf(fp, "\n");
	}
	fclose(fp);

}



int choise(vector<PasswordGenerator>& v, string m_p)
{
	

	cout << "+0...............Exit" << endl;
	cout << "+1...............Del_clones" << endl;			
	cout << "+2...............Sort_by_alph" << endl;
	cout << "+3...............Append_password" << endl;
	cout << "+4...............Del_pass_by_number" << endl;
	cout << "+5...............Open_all_passwords" << endl;
	cout << "+6...............Open_num_password" << endl;
	cout << "+7...............Passwords" << endl;

	int flag = 0;
	cout << "Input flag:";
	cin >> flag;

	system("cls");
	switch (flag)
	{
		
		case 1:
		{
			del_clones(v);
		}break;

		case 2:
		{
			sort_by_alph(v);
		}break;

		case 3:
		{
			append_password(v);
		}break;

		case 4:
		{
			del_pass_by_number(v);
		}break;

		case 5:
		{
			open_all_passwords(v,m_p);
		}break;

		case 6:
		{
			open_num_password(v,m_p);
		}break;

		case 7:
		{
			passwords(v);
		}break;

	}

	return flag;
}
