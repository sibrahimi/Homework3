//Ben Sipes
//bss5h4
//CS201 MWF Spatz
#include "Company.h"
void Company::setCompanyName(string NewCompanyName)
	{CompanyName = NewCompanyName;} //setter
void Company::setNewEmployee(Employee NewEmployee)
	{getEmployees().push_back(NewEmployee);} //setter
Company::Company(string NewCompanyName):CompanyName(NewCompanyName){}; //constructor
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
	infile.open("company.txt");
	while (!infile.eof())
	{
		string NewCompanyName;
		infile >> NewCompanyName; //read in the company name
		Company temp(NewCompanyName);//create company object
		CompanyVector.push_back(temp);//put company object into CompanyVector
	}//end while
	infile.close();
//	ofstream fout;
//	fout.open("out.dat");
//	fout.flush();
//	fout.close();
	cout << CompanyVector;
	keep_window_open();
}//end main
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