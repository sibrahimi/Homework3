//Ben Sipes
//bss5h4
//CS201 MWF Spatz
#include "Company.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
void Company::setCompanyName(string NewCompanyName)
	{CompanyName = NewCompanyName;}
void Company::setNewEmployee(Employee NewEmployee)
	{getEmployees().push_back(NewEmployee);}
Company::Company(string NewCompanyName):CompanyName(NewCompanyName){};
ostream& operator << (ostream& out, const vector<Company>& vec)
{
	for (unsigned i=0;i<vec.size();i++)
	{
		out << vec[i].getCompanyName() << endl;
	}//end for
	return out;
}//end overload << vector<Company>
int main()
{
	list<Employee> Unemployed;
	vector<Company> CompanyVector;
//start reading in text from Company file
	ifstream infile;
	ofstream fout;
	infile.open("company.txt");
	while (!infile.eof())
	{
		string NewCompanyName;
		infile >> NewCompanyName; //read in the company name
		Company temp(NewCompanyName);//create company object
		cout << temp.getCompanyName();
		CompanyVector.push_back(temp);//put company object into CompanyVector
	}//end while
	infile.close();
//	fout.open("out.dat");
//	fout.flush();
//	fout.close();
//	for (unsigned i=0; i<CompanyVector.size();++i)
//	{
//		cout << CompanyVector[i].getCompanyName();
//	}
	cout << CompanyVector;
}
/*
PROGRAM REQUIREMENTS
Your program must define the following classes:
    A company class
    Minimal Operations:
        add an employee to the list of employees for the company
        remove an employee who quits the company
        calculate the employees' salary
        find an employee
        pay the salaries of the employees
        print all employees
    You should determine how to implement the unemployed persons list.
*/