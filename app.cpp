#include	<iostream>
#include	<fstream>
#include	<cstdlib>
#include	<cstdio>
#include	<ctime>
#include	"BST.h"
#include    "Student.h"
#include	<string>

using namespace std;

bool readFile(const char* , BST*);
int menu();

int main() 
{
	BST studentBst;
	BST* subtree;
	const char* filename = "student.txt";
	int choice;
	int order, source;
	type stud;
	do
	{
		choice = menu();
		cout << endl;
		switch (choice)
		{
		case 1:
		{
			cout << "Read data to BST " << endl;
			cout << endl;
			if (!readFile(filename, &studentBst))
			{
				cout << "Unable to open the file.\n";
			}
			system("pause");
			system("cls");
			break;
		}

		case 2:
		{
			cout << "The deepest node(s): ";
			if (studentBst.deepestNodes())
				cout << "\nSuccessfully Displayed!\n";

			else
				cout << "Empty Tree!" << endl;
			cout << endl;
			system("pause");
			system("cls");
			break;
		}

		case 3:
		{
			cout << "\nIn what order do you wish to display? (1 / 2)\n";
			cout << "1. Ascending\n2. Descending\n";
			cout << "Order number: ";
			cin >> order;
			cout << endl;
			cout << "Where do you want to display? (1 / 2)\n";
			cout << "1. On the screen\n";
			cout << "2. In the file student-info.txt\n";
			cout << "Source number: ";
			cin >> source;

			if (!studentBst.display(order, source)) {
				cout << "\nEmpty Tree!" << endl;
			}
			cout << endl;
			system("pause");
			system("cls");
			break;
		}

		case 4:
		{
			subtree = new BST;
			cout << "Please enter student id: ";
			cin >> stud.id;
			if (studentBst.empty())
			{
				cout << "Tree is empty!" << endl;
			}
			if (subtree->CloneSubtree(studentBst, stud))
			{
				cout << endl;
				cout << "Subtree clonned sucessfully!" << endl;
				cout << "Print the original tree with the preOrderPrint(): " << endl;
				studentBst.preOrderPrint();
				cout << "Print the subtree with the preOrderPrint(): " << endl;
				subtree->preOrderPrint();
			}
			else
				cout << "Cannot clone subtree." << endl;
			delete subtree;
			cout << endl;
			system("pause");
			system("cls");
			break;
		}

		case 5:
		{
			if (studentBst.empty())
				cout << "Tree is empty!" << endl;
			else
				studentBst.printLevelNodes();
			cout << endl;
			system("pause");
			system("cls");
			break;
		}

		case 6:
		{
			if (studentBst.empty())
				cout << "Tree is empty!" << endl;
			else
				studentBst.printPath();
			cout << endl;
			system("pause");
			system("cls");
			break;
		}

		case 7:
		{
			cout << "Have a nice day!" << endl;
			break;
		}

		default:
			if (cin.fail()) // check if the user enter the correct input
			{
				// If the user enter the alphabet
				cout << "Invalid input. Please enter the numbers from 1-9 ONLY." << endl;
				cout << endl;
				cin.clear();
				cin.ignore();
				system("pause");
				system("cls");
				continue;
			}
			else
				// If the user enter the integer out of 1-9
				cout << "Please enter a valid integer." << endl;
			system("pause");
			system("cls");
		}

	} while (choice != 7);
	
	system("pause");
	return 0;
}

int menu()
{
	int choice = 0;
	cout << "(1) Read data to BST" << endl;
	cout << "(2) Print deepest nodes" << endl;
	cout << "(3) Display student" << endl;
	cout << "(4) Clone Subtree" << endl;
	cout << "(5) Print Level Nodes" << endl;
	cout << "(6) Print Path" << endl;
	cout << "(7) Exit" << endl;
	cout << "Please enter your option: ";
	cin >> choice;
	return choice;
}

bool readFile(const char* filename, BST* t1) 
{
	ifstream inFile(filename);
	if (!inFile.is_open()) 
	{
		return false; // Failed to open the file
	}

	string x;
	char temp[100];
	Student student;
	BST studentBst;
	int duplicate = 0;
	int count = 0;

	while (inFile >> x >> x >> x >> student.id) // use x to read and cancel labels or separators from file
	{
		inFile.ignore();
		inFile >> x >> x >> student.name;
		inFile.getline(temp, 30);
		strcat(student.name, temp);

		inFile >> x >> x >> student.address;
		inFile.getline(temp, 100);
		strcat(student.address, temp);

		inFile >> x >> x >> student.DOB;
		inFile.ignore();
		inFile >> x >> x >> x >> student.phone_no;
		inFile.ignore();
		inFile >> x >> x >> student.course;
		inFile.ignore();
		inFile >> x >> x >> student.cgpa;
		inFile.ignore();

		if (studentBst.hasDuplicates(t1, student.id)) //check duplicate number
		{
			duplicate++;
			continue;
		}

		t1->insert(student);
		count++;
	}
	if (duplicate != 0)
		cout << duplicate << " duplicate records has been found! Ignored the insertion!" << endl;
	cout << count << " students records had been succesfully read.\n" << endl;
	inFile.close();
	return true; // File read and students inserted into BST successfully
}