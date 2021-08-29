#include <iostream>
#include <vector>
using namespace std;

//Для работы с файлами
#include <fstream>


class Stroka {
public:
	vector <char*> lister;
	char* input;

	//конструктор вектора строк из файла
	Stroka(vector<char*> other) {
		for (vector<char*>::iterator i = other.begin(); i < other.end(); i++)
		{
			lister.push_back(*i);
		}
	}

	Stroka operator = (Stroka& other) {
		for (vector<char*>::iterator i = other.lister.begin(); i < other.lister.end(); i++)
		{
			lister.push_back(*i);
		}
	}	

	//Отобразить список строк
	void print() {
		int num = 1;
		for (vector<char*>::iterator i = lister.begin(); i < lister.end(); i++)
		{
			cout << "Строка: " << num++ << " = " << *i << endl;
			/*cout << "This: " << this << endl;*/
		}
	}

	//Метод сортировки
	void strokaSort() {

		bool sorted = false;
		int maxSize = lister.size();
		int countOfSort = 0;
		int process = 0;
		while (!sorted) {
			sorted = true;
			countOfSort++;					
			if (countOfSort % 10 == 0) {
				system("cls");
				process = (countOfSort * 1.0 / maxSize * 1.0) * 100;
				cout << "process: " << process << "%" << endl;
			}
			for (int i = 0; i < (maxSize - countOfSort); i++)
			{
				int j = 0;
				while (lister.at(i)[j] != '\0' || lister.at(i+1)[j] != '\0') {
					if (tolower(lister.at(i)[j]) < tolower(lister.at(i + 1)[j])) {
						swap(lister.at(i), lister.at(i + 1));
						sorted = false;
						break;
					}
					else if (tolower(lister.at(i)[j]) == tolower(lister.at(i + 1)[j])) j++;
					else if (tolower(lister.at(i)[j]) > tolower(lister.at(i + 1)[j])) break;
					else cout << "Не работает\n";
				}						
			}
		}
	}

	~Stroka() {
		delete[] input;
		vector<char*>().swap(lister);
		print();
	}


private:		
	int countStr = 0;
};

int countLinesInFile(char* filename) {
	ifstream F(filename, ios::in);
	if (!F) { return -1; }
	int count = 0;
	char buffer[1000];

	while (!F.eof()) {
		count++;
		F.getline(buffer, 1000);
	}
	F.close();
	return count;
}

int getCharStringsFromFile(char* filename, char*** _lines = nullptr) {
	char** lines;
	int n = countLinesInFile(filename);
	if (n == -1) return -1; 
	ifstream F(filename);
	if (!F) return -1;
	try
	{
		lines = new char* [n];
	}
	catch (bad_alloc e)
	{
		cout << e.what() << endl;
		F.close();
		return -1;
	}

	int len;
	char buffer[1000];

	for (int i = 0; i < n; i++)
	{
		//Строка из файла
		F.getline(buffer, 1000);

		//Длина прочитанной строки
		for (len = 0; buffer[len] != '\0'; len++);

		lines[i] = new char[len + 1];
		for (int j = 0; j < len; j++)
		{
			lines[i][j] = buffer[j];

		}
		lines[i][len] = '\0';
	}
		F.close();
		*_lines = lines;
		return n;	
}


int main() {
	setlocale(LC_ALL, "Russian");
	system("chcp 1251");

	//Объявление переменных
	int count;
	char** lines = nullptr;
	vector <char*> fromFile;

	//Получить количество и список строк типа char**
	count = getCharStringsFromFile((char*)"Files/forSort.txt", &lines);
	
	if (count < 0) {
		cout << "Ошибка открытия файла" << endl;
		return -1;
	}

	for (int i = 0; i < count; i++)
	{
		char * toList = lines[i];
		fromFile.push_back(toList);
	}	
	
	Stroka forSort(fromFile);
	
	forSort.strokaSort();
	forSort.print();

	//очистка памяти
	for (int i = 0; i < count; i++)
	{
		if (lines[i] != nullptr) {
			delete[] lines[i];
		}
	}
	if (lines != nullptr) delete[]lines;

	system("PAUSE");
	return 0;
}