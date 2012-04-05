//Ben Sipes
//bss5h4
//CS201 MWF Spatz
#include "Company.h"
#include <iterator>
using namespace std;
Company::Company(string NewCompanyName):CompanyName(NewCompanyName){}; //constructor
void Company::setCompanyName(string NewCompanyName)	{CompanyName = NewCompanyName;} //setter
void Company::setNewEmployee(Employee NewEmployee)	{getEmployees().push_back(NewEmployee);} //setter
ostream& operator << (ostream& out, const vector<Company>& vec)
{
	for (unsigned i=0;i<vec.size();i++)
	{
		out << vec[i].getCompanyName() << endl;
	}//end for
	return out;
}//end overload << vector<Company>
ostream& operator << (ostream& out, list<Employee>& lst)
{
	for (list<Employee>::iterator l = lst.begin();l!=lst.end();++l)
	{
		out << *l << endl;
	}//end for
	return out;
}//end overload << list<Employee>
ostream& operator << (ostream& out, Employee& emp)
{
	out << emp.EmployeeName << emp.TotalSalary << emp.CompanyRank << emp.LastCompany << endl;
	return out;
}
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
	cout << CompanyVector;
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
		//find the labeled company (Trans2nd)
		//search for whether or not the employee (Trans1st) already exists
		//add employee to new company
			for (unsigned i=0;i<CompanyVector.size();++i)
			{
				if (CompanyVector[i].getCompanyName() == Trans2nd)
				{ //Found the correct Company object to enroll the Employee
					for (unsigned j=0;j<EmployeeVector.size();++j)
					{
						if (EmployeeVector[j].EmployeeName == Trans1st)
						{ //if the employee already exists, must currently be unemployed, else "C" for CHANGE would be used
							CompanyVector[i].setNewEmployee(EmployeeVector[j]); //add the employee to the company payroll
//TODO: FIND THE EMPLOYEE IN THE UNEMPLOYED LIST AND REMOVE THEM!!!!!!!!!!!!!!!!!!!!!!!!!
						}//end if
						else //if the employee object doesn't currently exist, it needs to be created and then added.
						{
							Employee temp; //creates new employee object
							temp.EmployeeName = Trans1st; //sets their name
							EmployeeVector.push_back(temp); //adds employee to the EmployeeVector
							CompanyVector[j].setNewEmployee(temp); //add the new employee object to the company payroll
						}//end else
					}//end for
				}//end if
			}//end CASE J for loop
			break;
		case 'Q': //QUIT Q <Person>
			//remove employee from company list
			//add employee to unemployed list
			break;
		case 'C': //CHANGE C <Person> <Company>
			//add employee to new company
			//figure out where that employee was already employed
			//set Employee.LastCompany
			//delete employee from old company
			break;
		case 'S': //SALARY IS PAID
			//For each company in company vector,
			//for each employee in Company.Employees,
			//increase Employee.TotalSalary by Rank*$1000
			/*Pay $50 to everyone on Unemployed list
			for (list<Employee>::iterator l = Unemployed.begin();l!=Unemployed.end();++l)
			{
				*l.TotalSalary += 50;
			}
			*/
			break;
		case 'E': //EMPLOYEES E <Company>
			//prints a header with the company name,
			//then the current list of employees for the specified <Company>.
			//The employees must be printed in order of rank; either top to bottom or bottom to top is appropriate.
			//Also print the employee's current salary and salary-to-date.
			break;
		case 'U': //UNEMPLOYED LIST
			//the list of unemployed people should be printed.
			//Include the name of the last company the unemployed person worked for.
			break;
		case 'D': //DUMP 
			//Header, then E, then Header, then U
			break;
		case 'F': //FINISH 
		//"prints the message "End of Program"
			break;
		}//end switch Command
	}//end while
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
        remove an employee who quits the company
        calculate the employees' salary
        find an employee
        pay the salaries of the employees
        print all employees
    You should determine how to implement the unemployed persons list.

COMMANDS CHEATSHEET:
    J for JOIN, for example: J <Person> <Company>, means that the <Person> joins the specified <Company>. This may be the first reference to this person, or he or she may be unemployed. The person does not currently belong to another company. Remember that when a person joins a company, he or she always starts at the bottom. 
    Q for QUIT, for example: Q <Person>, means that the <Person> quits his or her job and becomes unemployed. You may assume that the person is currently employed.
    C for CHANGE, for example: C <Person> <Company>, means that the <Person> quits his or her job and joins the specified new <Company>. You may assume that the person is currently employed. Note that this command does not tell you the person's current employer; you have to search the data structure to find the person.
    S for SALARY, for example: S, means each person is paid his or her salary as specified in the Problem Statement. (You must keep track of the amount each person has earned from the start of the program.)
    E for EMPLOYEES, for example: E <Company>, prints a header with the company name, then the current list of employees for the specified <Company>. The employees must be printed in order of rank; either top to bottom or bottom to top is appropriate. Also print the employee's current salary and salary-to-date.
    U for UNEMPLOYED, for example: U, means the list of unemployed people should be printed. Include the name of the last company the unemployed person worked for.
    D for DUMP, for example: D, prints the employees in each company, as specified under the EMPLOYEES command above, then print the unemployed people as specified under the UNEMPLOYED command above. Label the output appropriately.
    F for FINISH, for example: F, prints the message "End of Program".
*/