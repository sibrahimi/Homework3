//Ben Sipes
//bss5h4
//CS201 MWF Spatz
#include "Company.h"
#include <iterator>
using namespace std;
Company::Company(string NewCompanyName):CompanyName(NewCompanyName){}; //constructor
void Company::setCompanyName(string NewCompanyName)	{CompanyName = NewCompanyName;} //setter
ostream& operator << (ostream& out, const vector<Company>& vec)
{
	for (unsigned i=0;i<vec.size();i++)
	{out << vec[i].getCompanyName() << endl;}//end for
	return out;
}//end overload << vector<Company>
ostream& operator << (ostream& out, list<Employee>& lst)
{
	for (list<Employee>::iterator l = lst.begin();l!=lst.end();++l)
	{out << *l << endl;}//end for
	return out;
}//end overload << list<Employee>
ostream& operator << (ostream& out, Employee& emp)
{
	//vector<string> Employ;
	//Employ.push_back(emp.EmployeeName);
	//Employ.push_back(emp.TotalSalary);
	//Employ.push_back(emp.CompanyRank);
	//Employ.push_back(emp.LastCompany);
	out << emp.EmployeeName << emp.TotalSalary << emp.LastCompany << emp.CompanyRank << endl;
	return out;
}
Company FindCompany(vector<Company> CompanyVector, string CompanyToFind)
{
	for (unsigned i=0;i<CompanyVector.size();++i)
	{if (CompanyVector[i].getCompanyName() == CompanyToFind)
	{return CompanyVector[i];}}//end if //end for
}//end FindCompany
Employee FindEmployee(list<Employee> Employees, string EmployeeToFind)
{
	for (list<Employee>::iterator l = Employees.begin();l!=Employees.end();++l)
	{if (l->EmployeeName == EmployeeToFind)
	{return *l;}}//end if //end for
//if the employee doesn't exist yet, make him, then return him
	Employee temp;
	temp.EmployeeName = EmployeeToFind;
	return temp;
}//end FindEmployee in list
Employee FindEmployee(vector<Employee> Employees, string EmployeeToFind)
{
	for (unsigned i=0;i<Employees.size();++i)
	{if (Employees[i].EmployeeName == EmployeeToFind)
	{return Employees[i];}} //end if //end for
//if the employee doesn't exist yet, make him, then return him
	Employee temp;
	temp.EmployeeName = EmployeeToFind;
	return temp;
}//end FindEmployee in vector
void RemoveEmployeeFromList(list<Employee> Container, string EmployeeToRemove)
{
	for (list<Employee>::iterator l = Container.begin();l!=Container.end();++l)
	{
		if (l->EmployeeName == EmployeeToRemove)
		{Container.erase(l);} //REMOVES PERSON FROM LIST
	}//end for
}//end RemoveFromUnemployed
int main()
{
	list<Employee> Unemployed;
	vector<Company> CompanyVector;
	vector<Employee> EmployeeVector;
//start reading in text from Company.txt
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
//finish reading in text from Company.txt
	cout << CompanyVector; //delete me when finished testing///////////////////////////////////////
//start reading in text from trans_file.dat
	infile.open("trans_file.dat"); //opens a new file this time
	while (!infile.eof())
	{
		char TransCommand;
		string Trans1st;
		string Trans2nd;
		infile >> TransCommand >> Trans1st >> Trans2nd; //read in the Command, Employee, CompanyName
		cout << TransCommand << " " << Trans1st << " " << Trans2nd << endl;
		switch (TransCommand) 
		{
		case 'J': //JOIN J <Person> <Company>
		{
			Company c = FindCompany(CompanyVector, Trans2nd);//find the labeled company (Trans2nd)
			Employee e = FindEmployee(EmployeeVector, Trans1st);//find/create the employee (Trans1st)
			c.Employees.push_back(e); //add employee to new company
			RemoveEmployeeFromList(Unemployed,Trans1st); //if employee with name Trans1st exists in unemployed list, removes them
			e.CompanyRank = 0; //Reset to 0, next for loop will increase this to the proper 1 while also increasing everyone above.
			for (list<Employee>::iterator l = c.Employees.begin();l!=c.Employees.end();++l)
			{l->CompanyRank += 1;}//end for
			break;
		}//end CASE J
		case 'Q': //QUIT Q <Person>
		{
			//putback Trans2nd
//remove employee from company list
			for (unsigned i=0;i<CompanyVector.size();++i)
			{RemoveEmployeeFromList(CompanyVector[i].Employees, Trans1st);}//end for
		//No 2 employees have the same name. If the employee doesn't exist in this company's list, no harm done.
		//Probably not the most precise way to do this, especially once you start having employees with the same name
		//who work for different companies, but it will suffice for now.
			Employee e = FindEmployee(EmployeeVector, Trans1st);
			Unemployed.push_back(e); //add employee to unemployed list
			break;
		}//end case Q
		case 'C': //CHANGE C <Person> <Company>
		{
			//add employee to new company
			//figure out where that employee was already employed
			//set Employee.LastCompany
			//delete employee from old company
			break;
		case 'S': //SALARY IS PAID
//			for (unsigned i=0;i<Trans2nd.size();++i) {cout << i; infile.putback(i);}
			//putback Trans1st Trans2nd
			//For each company in company vector,
			//for each employee in Company.Employees,
			//increase Employee.TotalSalary by Rank*$1000
//Pay $50 to everyone on Unemployed list
			for (list<Employee>::iterator l = Unemployed.begin();l!=Unemployed.end();++l)
			{
				l->TotalSalary += 50;
			}
			break;
		}//end case C
		case 'E': //EMPLOYEES E <Company>
		{
			//putback Trans2nd
			//prints a header with the company name (Trans1st),
			//then the current list of employees for the specified <Company>.
			//The employees must be printed in order of rank; either top to bottom or bottom to top is appropriate.
			//Also print the employee's current salary and salary-to-date.
			break;
		}//end case E
		case 'U': //UNEMPLOYED LIST
		{
			//putback Trans1st Trans2nd
			//the list of unemployed people should be printed.
			//Include the name of the last company the unemployed person worked for.
			break;
		}//end case U
		case 'D': //DUMP
		{
			//putback Trans1st Trans2nd
			//Header, then E, then Header, then U
			break;
		}//end case D
		case 'F': //FINISH 
		{
			//putback Trans1st Trans2nd
			//"prints the message "End of Program"
			cout << endl << "END OF PROGRAM";
			break;
		}//end case F
		}//end switch Command
	}//end while READING FILE
	infile.close();
//	ofstream fout;
//	fout.open("out.dat");
//	fout.flush();
//	fout.close();
	keep_window_open();
}//end main
/*
PROGRAM REQUIREMENTS
Your program must define the following classes:
    A company class
    Minimal Operations:
        calculate the employees' salary
        pay the salaries of the employees
        print all employees
    You should determine how to implement the unemployed persons list.
*/