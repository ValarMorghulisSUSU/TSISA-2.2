#pragma once
#include<cstdlib>
#include<ctime>
using namespace System;
using namespace System::IO;

#define  MAX_SIZE 100
ref class myObject {
public:
	array <String^>^ object;
	int count;
	myObject() {
		this->object = gcnew array <String^>(MAX_SIZE);
		this->count = 0;
	}

	//Проверка на пустоту
	bool isEmpty() {
		return this->count == 0;
	}

	//Проверка на заполненность
	bool isFull() {
		return this->count == MAX_SIZE;
	}
	//Добавить
	bool add(String^ pr) {
		if (!isFull())
		{
			this->object[count] = pr;
			this->count++;
			return true;
		}
		else return false;
	}
	//Удалить
	void deleteObject(int index) {
		if (!isEmpty()) {
			for (int i = index; i < this->count - 1; i++) {
				this->object[i] = this->object[i + 1];
			}
			this->count--;
		}
	}
	void deleteObject(String^ pr) {
		if (!isEmpty()) {
			for (int i = 0; i < this->count; i++) {
				if (String::Compare(this->object[i],pr) == 0) {
					for (int k = i; k < this->count; k++) {
						object[k] = object[k + 1];
					}
					this->count--;
				}
			}
		}
	}

	//Сгенерировать рандомный объект
	String^ generateRandObject() {
		srand(time(0));
		int i = 0 + rand() % (this->count);
		return this->object[i];
	}

	//Прочитать файл
	void readFromFile(StreamReader^ SR) {
		String^ str = gcnew String("");
		int i = 0;
		while (str = SR->ReadLine()) {
			this->object[i] = str;
			this->count++;
			i++;
		}
		SR->Close();
	}

	int find(String^ p) {
		for (int i = 0; i < this->count; i++)
		{
			if (this->object[i] == p) return i;
		}
		return -1;
	}

	//Сохранить в файл
	void writeToFile(StreamWriter^ SW) {
		for (int i = 0; i < this->count - 1; i++) {
			String^ Line = gcnew String("");
			Line = this->object[i] + "\n";
			SW->Write(Line);
		}
		String^ Line = this->object[this->count - 1];
		SW->Write(Line);
		SW->Close();
	}

	//Отобразить в ListBox
	void viewLB(System::Windows::Forms::ListBox^ LB) {
		LB->Items->Clear();
		for (int i = 0; i < this->count; i++) {
			LB->Items->Add(this->object[i]);
		}
	}
};


ref class Matrix {
public:
	int** matrix;
	int i;
	int j;
	Matrix(int i, int j) {
		Random^ rand = gcnew Random();
		this->i = i;
		this->j = j;
		this->matrix = new int* [this->i];
		for (int ii = 0; ii < this->i; ii++)
		{
			this->matrix[ii] = new int[j];
		}
		for (int ii = 0; ii < this->i; ii++)
		{
			for (int jj = 0; jj < this->j; jj++)
			{
				Threading::Thread::Sleep(5);
				this->matrix[ii][jj] = rand->Next(0, 2);
			}
		}
	}
	Matrix(Matrix^ ot) {
		Random^ rand = gcnew Random();
		this->i = ot->i;
		this->j = ot->j;
		this->matrix = new int* [this->i];
		for (int ii = 0; ii < this->i; ii++) {
			matrix[ii] = new int[j];
		}
		for (int ii = 0; ii < this->i; ii++) {
			for (int jj = 0; jj < this->j; jj++) {
				Threading::Thread::Sleep(5);
				this->matrix[ii][jj] = ot->matrix[ii][jj];
			}
		}
	}

	void Add_Row() {
		Random^ rand = gcnew Random();
		this->i++;
		this->matrix[this->i - 1] = new int[this->j];

		for (int jj = 0; jj < this->j; jj++)
		{
			Threading::Thread::Sleep(5);
			this->matrix[this->i - 1][jj] = rand->Next(0, 2);
		}
	}
	void Add_Column(Matrix^ ot) {
		Random^ rand = gcnew Random();
		this->i = ot->i + 1;
		this->j = ot->j + 1;
		this->matrix = new int* [this->i];
		for (int a = 0; a < this->i; a++)
		{
			this->matrix[a] = new int[j];
		}
		for (int a = 0; a < ot->i; a++)
		{
			for (int b = 0; b < ot->j; b++)
			{
				this->matrix[a][b] = ot->matrix[a][b];
			}
		}

		for (int b = 0; b < this->i; b++)
		{
			Threading::Thread::Sleep(5);
			this->matrix[b][j - 1] = rand->Next(0, 2);
		}
	}
	void delRow() {
		this->i--;
	}
	void delColumn() {
		this->j--;
	}
};

void lookMatrix(myObject^ o, myObject^ p, Matrix^ m, System::Windows::Forms::DataGridView^ DGV){
	DGV->ColumnCount = p->count + 1;
	DGV->RowCount = o->count + 1;
	DGV->Rows[0]->Cells[0]->Value = "";
	for (int i = 1; i <= o->count; i++) {
		DGV->Rows[i]->Cells[0]->Value = o->object[i - 1];
	}

	for (int i = 1; i <= p->count; i++) {
		DGV->Rows[0]->Cells[i]->Value = p->object[i - 1];
	}

	for (int i = 1; i <= o->count; i++) {
		for (int j = 1; j <= p->count; j++) {
			DGV->Rows[i]->Cells[j]->Value = m->matrix[i - 1][j - 1];
		}
	}

}

String^ randomObject(String^ s, myObject^ o, myObject^ p, Matrix^ m)
{
	myObject^ temp = gcnew myObject();
	int i = p->find(s);
	for (int j = 0; j < o->count; j++)
	{
		if (m->matrix[j][i] == 1)
		{
			temp->add(o->object[j]);
		}
	}
	return temp->generateRandObject();
}

String^ randomProperty(String^ s, myObject^ o, myObject^ p, Matrix^ m)
{
	myObject^ temp = gcnew myObject();
	int j = o->find(s);
	for (int i = 0; i < p->count; i++)
	{
		if (m->matrix[j][i] == 1)
		{
			temp->add(p->object[i]);
		}
	}
	return temp->generateRandObject();
}