#include<iostream>
#include<iomanip>
#include<fstream>
#include<stdio.h>
#include<string>
using namespace std;

void file_txt_write() {
	//ofstream fout("hakuna.txt");
	ofstream fout("hakuna.txt", ios::app);
	if (!fout) throw "File not found";
	if (fout.is_open())
	{
		fout << "Hello world" << endl;
	}
	else
	{
		throw "File not open exception";
	}
	fout.close();
}

void file_txt_read() {
	ifstream fin("hakuna.txt");
	if (!fin) throw "File not found";
	if (fin.is_open())
	{
		string value;
		while (!fin.eof())
		{
			getline(fin, value);
			cout << value << endl;

		}
	}
	else
	{
		throw "File not open exception";
	}
	fin.close();
}

void file_binary_write() {
	ofstream fout("arr.bin", ios::binary);
	int arr[5]{ 1,2,3,4,5 };
	if (!fout) throw "File not found";
	if (fout.is_open()) {
		fout.write((char*)arr, sizeof(int) * 5);
	}
	else
	{
		throw "File not open exception";
	}
	fout.close();
}

void file_binary_read() {
	ifstream fin("arr.bin");
	int arr[5]{};
	if (!fin) throw "File not found";
	if (fin.is_open())
	{
		fin.read((char*)arr, sizeof(int) * 5);
	}
	else
	{
		throw "File not open exception";
	}

	for (size_t i = 0; i < 5; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
	fin.close();
}

class Contact {
public:
	string name;
	string surname;
	string number;

	Contact() = default;
	Contact(const string& name, const string& surname, const string& number)
	{
		this->name = name;
		this->surname = surname;
		this->number = number;
	}
};

void file_txt_write_object() {
	Contact c("Kenan", "Idayatov", "10");
	ofstream fout("contact.txt", ios::app);
	fout.setf(ios::left);
	if (!fout) throw "File not found";
	if (fout.is_open())
	{
		fout << setw(20) << c.name << " "
			<< setw(20) << c.surname << " "
			<< setw(20) << c.number << endl;
	}
	else
	{
		throw "File not open exception";
	}

	fout.close();
}

void file_txt_read_object() {
	Contact c;
	ifstream fin("contact.txt");
	if (!fin) throw "File not found";
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			fin >> c.name;
			fin >> c.surname;
			fin >> c.number;

			if (c.name != " ") {
				cout << c.name << endl;
				cout << c.surname << endl;
				cout << c.number << endl;
				cout << endl;
			}
			c.name = " ";
		}
	}
	else
	{
		throw "File not open exception";
	}


	fin.close();
}

bool find(const string& name) {
	Contact c;
	ifstream fin("contact.txt");
	if (!fin) throw "File not found";
	if (fin.is_open())
	{
		bool isFind = false;
		while (!fin.eof())
		{
			fin >> c.name;
			fin >> c.surname;
			fin >> c.number;

			if (c.name == name)
			{
				isFind = true;
				return true;
				break;
			}
		}
		if (!isFind) return false;
	}
	else
	{
		throw "File not open exception";
	}
	fin.close();
}

void deleteContact(const string& name) {
	if (find(name) == 0) throw "Name not found";
	else
	{
		Contact c;

		ifstream fin("contact.txt");
		ofstream fout("newContact.txt");
		if (!fin) throw "File not found";
		if (!fout) throw "File not found";
		if (fin.is_open()) {
			while (!fin.eof())
			{
				fin >> c.name;
				fin >> c.surname;
				fin >> c.number;

				fout.setf(ios::left);
				if (c.name == name) continue;

				if (c.name != " ") fout << setw(20) << c.name << " "
					<< setw(20) << c.surname << " "
					<< setw(20) << c.number << endl;
				c.name = " ";

			}
		}
		else
		{
			throw "File not open exception";
		}
		fin.close();
		fout.close();
		remove("contact.txt");
		if (rename("newContact.txt", "contact.txt") == 0) cout << "File succesfully renamed";
		else throw "Error renaming file";
	}
}

int main() {
	try
	{
		//file_txt_write();
		//file_txt_read();
		//file_binary_write();
		//file_binary_read();
		//file_txt_write_object();
		//file_txt_read_object();
		deleteContact("Kenan");
	}
	catch (const char* ex)
	{
		cout << "Exception occured !" << endl;
		cout << "Exception: " << ex << endl;
		cout << "Exception Line: " << __LINE__ << endl;
	}
	return 0;
}