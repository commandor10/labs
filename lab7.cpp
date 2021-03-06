#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <time.h>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <utility>

using namespace std;

struct fio
{
	char*	Last_name;
	char*	First_name;
	char*	Patronymic_name;

};

struct Date
{
	int		day;
	char*	month;
	int		year;
	int		delay;

};

struct credit
{
	int  ID;
	fio		FIO;
	double	Summ;
	int     percent;
	Date	date;
};

credit add_credit();
void print_credit(credit* info, int count_p);
void same_percent(credit* info, int count_p, int per);
void count_credit_b_L_N_and_F_N(credit* info, int count_p, char* L_N, char* F_N, char* FF_N);
void count_credit_b_date(credit* info, int count_p, int d, char* m, int y);
credit* del_user(credit* info, int *count_p, int d, char* m, int y);
void destroy(credit* info);
void sort_credit(credit* info, int count_p);
credit* add_user(credit* info, int *count_p);

int main()
{

	int d = 0;
	int y = 0;
	int flag = 9;
	int count_p;
	int saved_count = 0;
	int per = 0;
	int pos = 0;
	char* L_N = new char[256];
	char* F_N = new char[256];
	char* FF_N = new char[256];
	char* m = new char[256];

	FILE *fp;
	char path[] = "text.txt";



	cout << "1------------Add credit" << endl;
	cout << "2------------Print credits" << endl;
	cout << "3------------Count credit by Last and First name, Patronymic_name" << endl;
	cout << "4------------Find person by percent" << endl;
	cout << "5------------Count outdated credit" << endl;
	cout << "6------------del credit" << endl;
	cout << "7------------sort credit by sum" << endl;
	cout << "8------------Add credit v nachale" << endl;
	cout << "0------------Exit" << endl;

	if ((fp = fopen(path, "r")) == NULL)
	{

		cout << "No File" << endl;
		cout << "Input count of people" << endl;
		cin >> count_p;


		credit* info = new credit[count_p];




		//начало заполнение
		for (int i = 0; i < count_p; i++)

		{
			info[i].ID = 0;

			info[i].FIO.Last_name = new char[256];
			info[i].FIO.First_name = new char[256];
			info[i].FIO.Patronymic_name = new char[256];

			info[i].Summ = 0;
			info[i].percent = 0;

			info[i].date.day = 0;
			info[i].date.delay = 0;
			info[i].date.month = new char[256];
			info[i].date.year = 0;

		}


		for (int i = 0; i < count_p; i++)

		{
			cout << "Input ID_" << i << "_" << endl;
			cin >> info[i].ID;




			cout << "Input LastName_" << i << "_" << endl;
			cin >> info[i].FIO.Last_name;

			cout << "Input FirstName_" << i << "_" << endl;
			cin >> info[i].FIO.First_name;

			cout << "Input Patronymic_name_" << i << "_" << endl;
			cin >> info[i].FIO.Patronymic_name;



			cout << "Input SUmm_" << i << "_" << endl;
			cin >> info[i].Summ;

			cout << "Input percent_" << i << "_" << endl;
			cin >> info[i].percent;

			cout << "Input delay_" << i << "_" << endl;
			cin >> info[i].date.delay;

			cout << "Input Date_day_" << i << "_" << endl;
			cin >> info[i].date.day;

			cout << "Input Date_month_" << i << "_" << endl;
			cin >> info[i].date.month;

			cout << "Input Date_year_" << i << "_" << endl;
			cin >> info[i].date.year;

		}
		//конец заполнения




		while (flag != 0)
		{

			cout << "Input flag" << endl;
			cin >> flag;




			switch (flag)
			{
			case 1:



				count_p++;
				info = (credit*)realloc(info, sizeof(credit)*count_p);
				info[count_p - 1] = add_credit();


				break;
			case 2:

				print_credit(info, count_p);

				break;

			case 3:

				cout << "Input Last_name" << endl;
				cin >> L_N;

				cout << "Input First_name" << endl;
				cin >> F_N;

				cout << "Input Patronymic_name" << endl;
				cin >> FF_N;

				count_credit_b_L_N_and_F_N(info, count_p, L_N, F_N, FF_N);


				break;

			case 4:
				cout << "Input percent" << endl;
				cin >> per;

				same_percent(info, count_p, per);


				break;
			case 5:
				cout << "Input Date_day" << endl;
				cin >> d;

				cout << "Input Date_month" << endl;
				cin >> m;

				cout << "Input Date_year" << endl;
				cin >> y;

				count_credit_b_date(info, count_p, d, m, y);

				break;
			case 6:
				cout << "Input Date_day" << endl;
				cin >> d;

				cout << "Input Date_month" << endl;
				cin >> m;

				cout << "Input Date_year" << endl;
				cin >> y;
				info=del_user(info, &count_p, d, m, y);

				break;
			case 7:

				sort_credit(info, count_p);

				break;
			case 8:

				info = add_user(info, &count_p);
				
				break;
			case 0:
				cout << "bb" << endl;
				break;
			}

			//Запись в файл
			int i;

			fp = fopen(path, "w+");

			fprintf(fp, "%d", count_p);
			fprintf(fp, "\n");

			for (i = 0; i < count_p; i++)
			{
				fprintf(fp, "%d %s %s %s %lf %d %d %d %s %d \n", info[i].ID, info[i].FIO.First_name, info[i].FIO.Last_name,
					info[i].FIO.Patronymic_name, info[i].Summ, info[i].percent, info[i].date.delay, info[i].date.day, info[i].date.month, info[i].date.year);
			}
			//Конец записи в файл

		}
	}

	//Заполение если файла есть (считывание с файла)


	else
	{

		//cout << fp << endl;


		cout << "Yes File" << endl;

		string razmer_text;
		credit* info = new credit[1];


		count_p = 0;
		int razmer = 0;
		int i = 0;

		ifstream file("text.txt", ios::in | ios::ate);
		if (file) {

			ifstream::streampos filesize = file.tellg();
			razmer_text.reserve(filesize);
			file.seekg(0);
			razmer = filesize;
			//	cout << "DDDD= " << razmer;
			file.close();
		}
		//опеределение длины текста конец




				//fp = fopen(path, "r");

		fscanf(fp, "%d", &count_p);
		info = (credit*)realloc(info, sizeof(credit)*count_p);
		//cout << count_p << endl;

		for (i = 0; i < count_p; i++)
		{



			info[i].ID = 0;

			info[i].FIO.Last_name = new char[256];
			info[i].FIO.First_name = new char[256];
			info[i].FIO.Patronymic_name = new char[256];

			info[i].Summ = 0;

			info[i].date.day = 0;
			info[i].date.month = new char[256];
			info[i].date.year = 0;



			fscanf(fp, "%d %s %s %s %lf %d %d %d %s %d ", &info[i].ID, info[i].FIO.First_name, info[i].FIO.Last_name,
				info[i].FIO.Patronymic_name, &info[i].Summ, &info[i].percent, &info[i].date.delay, &info[i].date.day, info[i].date.month, &info[i].date.year);
		}




		while (flag != 0)
		{

			cout << "Input flag" << endl;
			cin >> flag;




			switch (flag)
			{
			case 1:



				count_p++;
				info = (credit*)realloc(info, sizeof(credit)*count_p);
				info[count_p - 1] = add_credit();


				break;
			case 2:

				print_credit(info, count_p);

				break;

			case 3:

				cout << "Input Last_name" << endl;
				cin >> L_N;

				cout << "Input First_name" << endl;
				cin >> F_N;

				cout << "Input Patronymic_name" << endl;
				cin >> FF_N;

				count_credit_b_L_N_and_F_N(info, count_p, L_N, F_N, FF_N);


				break;

			case 4:
				cout << "Input percent" << endl;
				cin >> per;

				same_percent(info, count_p, per);


				break;
			case 5:
				cout << "Input Date_day" << endl;
				cin >> d;

				cout << "Input Date_month" << endl;
				cin >> m;

				cout << "Input Date_year" << endl;
				cin >> y;

				count_credit_b_date(info, count_p, d, m, y);

				break;
			case 6:
				cout << "Input Date_day" << endl;
				cin >> d;

				cout << "Input Date_month" << endl;
				cin >> m;

				cout << "Input Date_year" << endl;
				cin >> y;
				info = del_user(info, &count_p, d, m, y);
				break;
			case 7:

				sort_credit(info, count_p);

				break;
			case 8:



				
				info=add_user(info, &count_p);
				

				break;

			case 0:
				cout << "bb" << endl;
				break;
			}

		}



		//Запись в файл


		fp = fopen(path, "w+");

		fprintf(fp, "%d", count_p);
		fprintf(fp, "\n");

		for (i = 0; i < count_p; i++)
		{
			fprintf(fp, "%d %s %s %s %lf %d %d %d %s %d \n", info[i].ID, info[i].FIO.First_name, info[i].FIO.Last_name,
				info[i].FIO.Patronymic_name, info[i].Summ, info[i].percent, info[i].date.delay, info[i].date.day, info[i].date.month, info[i].date.year);
		}
		//Конец записи в файл




	}
	//конец заполнения



	system("pause>>0");
	return 0;
}






credit add_credit()
{

	credit info;

	info.ID = 0;
	cout << "Input ID_" << endl;
	cin >> info.ID;



	info.FIO.Last_name = new char[256];
	cout << "Input LastName_" << endl;
	cin >> info.FIO.Last_name;

	info.FIO.First_name = new char[256];
	cout << "Input FirstName_" << endl;
	cin >> info.FIO.First_name;

	info.FIO.Patronymic_name = new char[256];
	cout << "Input Patronymic_name_" << endl;
	cin >> info.FIO.Patronymic_name;



	info.Summ = 0;
	cout << "Input SUmm_" << endl;
	cin >> info.Summ;

	info.percent = 0;
	cout << "Input percent_" << endl;
	cin >> info.percent;

	info.date.delay = 0;
	cout << "Input delay_" << endl;
	cin >> info.date.delay;

	info.date.day = 0;
	cout << "Input Day_" << endl;
	cin >> info.date.day;

	info.date.month = new char[256];
	cout << "Input Month_" << endl;
	cin >> info.date.month;

	info.date.year = 0;
	cout << "Input Year_" << endl;
	cin >> info.date.year;


	return info;
}

void print_credit(credit* info, int count_p)
{
	cout << "|------| |-------------------------------| |--------------| |-------| |-----| |---------------------|" << endl;
	cout << "|--ID--| |----------------FIO------------| |-----Summ-----| |percent| |delay| |--------Date---------|" << endl;
	cout << "|------| |-------------------------------| |--------------| |-------| |-----| |---------------------|" << endl;
	for (int i = 0; i < count_p; i++)
	{

		cout << "|";
		cout << setw(6) << left << info[i].ID;
		cout << "|";

		cout << " |";
		cout << setw(10) << left << info[i].FIO.Last_name;
		cout << "|";


		cout << setw(10) << left << info[i].FIO.First_name;
		cout << "|";

		cout << setw(9) << left << info[i].FIO.Patronymic_name;
		cout << "| ";

		cout << "|";
		cout << setw(14) << left << info[i].Summ;
		cout << "|";

		cout << " |";
		cout << setw(7) << left << info[i].percent;
		cout << "|";

		cout << " |";
		cout << setw(5) << left << info[i].date.delay;
		cout << "|";

		cout << " |";
		cout << setw(5) << left << info[i].date.day;
		cout << "|";


		cout << setw(8) << left << info[i].date.month;
		cout << "|";


		cout << setw(6) << left << info[i].date.year;
		cout << "|" << endl;

		cout << "|------| |-------------------------------| |--------------| |-------| |-----| |---------------------|" << endl;



	}


}

void same_percent(credit* info, int count_p, int per)
{

	cout << "|------| |-------------------------------| |--------------| |-------| |-----| |---------------------|" << endl;
	cout << "|--ID--| |----------------FIO------------| |-----Summ-----| |percent| |delay| |--------Date---------|" << endl;
	cout << "|------| |-------------------------------| |--------------| |-------| |-----| |---------------------|" << endl;
	for (int i = 0; i < count_p; i++)
	{
		if (info[i].percent == per)
		{

			cout << "|";
			cout << setw(6) << left << info[i].ID;
			cout << "|";

			cout << " |";
			cout << setw(10) << left << info[i].FIO.Last_name;
			cout << "|";


			cout << setw(10) << left << info[i].FIO.First_name;
			cout << "|";

			cout << setw(9) << left << info[i].FIO.Patronymic_name;
			cout << "| ";

			cout << "|";
			cout << setw(14) << left << info[i].Summ;
			cout << "|";

			cout << " |";
			cout << setw(7) << left << info[i].percent;
			cout << "|";

			cout << " |";
			cout << setw(5) << left << info[i].date.delay;
			cout << "|";

			cout << " |";
			cout << setw(5) << left << info[i].date.day;
			cout << "|";


			cout << setw(8) << left << info[i].date.month;
			cout << "|";


			cout << setw(6) << left << info[i].date.year;
			cout << "|" << endl;

			cout << "|------| |-------------------------------| |--------------| |-------| |-----| |---------------------|" << endl;



		}
	}

}




void count_credit_b_L_N_and_F_N(credit* info, int count_p, char* L_N, char* F_N, char* FF_N)
{
	cout << "|------| |-------------------------------| |--------------| |-------| |-----| |---------------------|" << endl;
	cout << "|--ID--| |----------------FIO------------| |-----Summ-----| |percent| |delay| |--------Date---------|" << endl;
	cout << "|------| |-------------------------------| |--------------| |-------| |-----| |---------------------|" << endl;
	for (int i = 0; i < count_p; i++)
	{
		if ((strcmp(info[i].FIO.Last_name, L_N) && strcmp(info[i].FIO.First_name, F_N) && strcmp(info[i].FIO.Patronymic_name, FF_N)) == 0)
		{
			cout << "|";
			cout << setw(6) << left << info[i].ID;
			cout << "|";

			cout << " |";
			cout << setw(10) << left << info[i].FIO.Last_name;
			cout << "|";


			cout << setw(10) << left << info[i].FIO.First_name;
			cout << "|";

			cout << setw(9) << left << info[i].FIO.Patronymic_name;
			cout << "| ";

			cout << "|";
			cout << setw(14) << left << info[i].Summ;
			cout << "|";

			cout << " |";
			cout << setw(7) << left << info[i].percent;
			cout << "|";

			cout << " |";
			cout << setw(5) << left << info[i].date.delay;
			cout << "|";

			cout << " |";
			cout << setw(5) << left << info[i].date.day;
			cout << "|";


			cout << setw(8) << left << info[i].date.month;
			cout << "|";


			cout << setw(6) << left << info[i].date.year;
			cout << "|" << endl;

			cout << "|------| |-------------------------------| |--------------| |-------| |-----| |---------------------|" << endl;




		}
	}

}

void count_credit_b_date(credit* info, int count_p, int d, char* m, int y)
{
	cout << "|------| |-------------------------------| |--------------| |-------| |-----| |---------------------|" << endl;
	cout << "|--ID--| |----------------FIO------------| |-----Summ-----| |percent| |delay| |--------Date---------|" << endl;
	cout << "|------| |-------------------------------| |--------------| |-------| |-----| |---------------------|" << endl;
	for (int i = 0; i < count_p; i++)
	{
		int cur = 0;
		int date = 0;
		int m_in = 0;
		int m_was = 0;


		if (strcmp(info[i].date.month, "January") == 0)
			m_was = 1;
		if (strcmp(info[i].date.month, "February") == 0)
			m_was = 2;
		if (strcmp(info[i].date.month, "March") == 0)
			m_was = 3;
		if (strcmp(info[i].date.month, "April") == 0)
			m_was = 4;
		if (strcmp(info[i].date.month, "May") == 0)
			m_was = 5;
		if (strcmp(info[i].date.month, "June") == 0)
			m_was = 6;
		if (strcmp(info[i].date.month, "July") == 0)
			m_was = 7;
		if (strcmp(info[i].date.month, "August") == 0)
			m_was = 8;
		if (strcmp(info[i].date.month, "September") == 0)
			m_was = 9;
		if (strcmp(info[i].date.month, "October") == 0)
			m_was = 10;
		if (strcmp(info[i].date.month, "November") == 0)
			m_was = 11;
		if (strcmp(info[i].date.month, "December") == 0)
			m_was = 12;

		if (strcmp(m, "January") == 0)
			m_in = 1;
		if (strcmp(m, "February") == 0)
			m_in = 2;
		if (strcmp(m, "March") == 0)
			m_in = 3;
		if (strcmp(m, "April") == 0)
			m_in = 4;
		if (strcmp(m, "May") == 0)
			m_in = 5;
		if (strcmp(m, "June") == 0)
			m_in = 6;
		if (strcmp(m, "July") == 0)
			m_in = 7;
		if (strcmp(m, "August") == 0)
			m_in = 8;
		if (strcmp(m, "September") == 0)
			m_in = 9;
		if (strcmp(m, "October") == 0)
			m_in = 10;
		if (strcmp(m, "November") == 0)
			m_in = 11;
		if (strcmp(m, "December") == 0)
			m_in = 12;


		cur = y * 12 + m_in;
		date = info[i].date.year * 12 + m_was;
		//	cout << endl << "cur = " << m_in << "date= " << m_was << endl;

		if (cur - date >= info[i].date.delay)
		{


			cout << "|";
			cout << setw(6) << left << info[i].ID;
			cout << "|";

			cout << " |";
			cout << setw(10) << left << info[i].FIO.Last_name;
			cout << "|";


			cout << setw(10) << left << info[i].FIO.First_name;
			cout << "|";

			cout << setw(9) << left << info[i].FIO.Patronymic_name;
			cout << "| ";

			cout << "|";
			cout << setw(14) << left << info[i].Summ;
			cout << "|";

			cout << " |";
			cout << setw(7) << left << info[i].percent;
			cout << "|";

			cout << " |";
			cout << setw(5) << left << info[i].date.delay;
			cout << "|";

			cout << " |";
			cout << setw(5) << left << info[i].date.day;
			cout << "|";


			cout << setw(8) << left << info[i].date.month;
			cout << "|";

			cout << setw(6) << left << info[i].date.year;
			cout << "|" << endl;



		}

	}
	cout << "|------| |-------------------------------| |--------------| |-------| |-----| |---------------------|" << endl;
}



credit* del_user(credit* info, int *count_p, int d, char* m, int y)
{
	int *ptrarray = new int[*count_p - 1];
	int dd = 0;

	for (int i = 0; i < *count_p; i++)
	{

		if (d == info[i].date.day && y == info[i].date.year)
			if (strcmp(info[i].date.month, m) == 0)
			{
				ptrarray[dd] = i;
			//	cout << endl << " " << ptrarray[dd] << " " << dd << endl;
				dd++;
			}
			
	}
	
	for (int i = dd-1; i >= 0; i--)
	{
		credit* temp = new credit[*count_p - 1];

		for (int j = 0; j < ptrarray[i]; ++j)
		{
	//		cout << " " << ptrarray[i] << endl;
			temp[j] = info[j];
		}
				for (int j = ptrarray[i]; j < (*count_p) - 1; ++j)
				{
			//		cout << " " << ptrarray[i] << endl;
					temp[j] = info[j + 1];
				}
		destroy(info);
		(*count_p)--;
		info = new credit[(*count_p) + 1];
		for (int j = 0; j < *count_p; j++)
			info[j] = temp[j];
		destroy(temp);
	}
	return info;
}

void destroy(credit* info)
{
	delete [] info;
}

void sort_credit(credit* info, int count_p)
{
	for (int i = 1; i < count_p; i++)
		for (int j = 0; j < count_p - 1; j++)
			if (info[j].Summ > info[j+1].Summ) {
				swap(info[j].Summ, info[j + 1].Summ);
				swap(info[j].ID, info[j + 1].ID);
				swap(info[j].FIO.Last_name, info[j + 1].FIO.Last_name);
				swap(info[j].FIO.First_name, info[j + 1].FIO.First_name);
				swap(info[j].FIO.Patronymic_name, info[j + 1].FIO.Patronymic_name);
				swap(info[j].percent, info[j + 1].percent);
				swap(info[j].date.day, info[j + 1].date.day);
				swap(info[j].date.month, info[j + 1].date.month);
				swap(info[j].date.year, info[j + 1].date.year);
				swap(info[j].date.delay, info[j + 1].date.delay);
				
			}

}

credit* add_user(credit* info, int *count_p)
{
	credit front = add_credit();
	credit* info_copy = new credit[*count_p];
	for (int i = 0; i < *count_p; i++)
		info_copy[i] = info[i];
	destroy(info);
	(*count_p)++;
	info = new credit[*count_p];
	info[0] = front;
	for (int i = 1; i < *count_p; i++)
		info[i] = info_copy[i-1];
	return info;
}
