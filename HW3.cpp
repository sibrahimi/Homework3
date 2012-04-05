//Ben Sipes
//bss5h4
//CS201 MWF Spatz
#include "Company.h"
#include <iterator>
using namespace std;
Company::Company(string NewCompanyName):CompanyName(NewCompanyName){}; //constructor
void Company::setCompanyName(string NewCompanyName)	{CompanyName = NewCompanyName;} //setter
void Company::setTotalSalariesPaid(int Payday) {TotalSalariesPaid += Payday;} //setter
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
		infile >> TransCommand >> Trans1st >> Trans2nd;
		cout << TransCommand << " " << Trans1st << " " << Trans2nd << endl; //delete me when finished testing///////////////////////////////////////
		switch (TransCommand) 
		{
		case 'J': //JOIN J <Person> <Company>
		{
			Company c = FindCompany(CompanyVector, Trans2nd);//find the labeled company (Trans2nd)
			Employee e = FindEmployee(EmployeeVector, Trans1st);//find/create the employee (Trans1st)
			c.Employees.push_back(e); //add employee to new company
			RemoveEmployeeFromList(Unemployed,Trans1st); //if employee with name Trans1st exists in unemployed list, removes them
			e.LastCompany = ""; //should ONLY be set if they are unemployed
			e.CompanyRank = 0; //Reset to 0, next for loop will increase this to the proper 1 while also increasing everyone above.
			for (list<Employee>::iterator l = c.Employees.begin();l!=c.Employees.end();++l)
			{l->CompanyRank += 1;}//end for
			break;
		}//end CASE J
		case 'Q': //QUIT Q <Person>
		{
			//putback Trans2nd
//remove employee from company list
			Employee e = FindEmployee(EmployeeVector, Trans1st);
			for (unsigned i=0;i<CompanyVector.size();++i)
			{for (list<Employee>::iterator l = CompanyVector[i].Employees.begin();l!=CompanyVector[i].Employees.end();++l)
				{if (l->EmployeeName == Trans1st)
				{
					l->LastCompany = CompanyVector[i].getCompanyName();
					RemoveEmployeeFromList(CompanyVector[i].Employees, Trans1st);
				}
				for (list<Employee>::iterator l = CompanyVector[i].Employees.begin();l!=CompanyVector[i].Employees.end();++l)
				{if (l->CompanyRank >= e.CompanyRank)
				{l->CompanyRank -= 1;}//end if
				}//end for
				}//end for
			}//end for
			Unemployed.push_back(e); //add employee to unemployed list
			break;
		}//end case Q
		case 'C': //CHANGE C <Person> <Company>
		{
//C is essentially a combination of Q followed by J, but without the Unemployment inbetween.
//Employee quits his old job
			Employee e = FindEmployee(EmployeeVector, Trans1st);
			for (unsigned i=0;i<CompanyVector.size();++i)
			{for (list<Employee>::iterator l = CompanyVector[i].Employees.begin();l!=CompanyVector[i].Employees.end();++l)
				{if (l->EmployeeName == Trans1st)
				{
					l->LastCompany = CompanyVector[i].getCompanyName();
					RemoveEmployeeFromList(CompanyVector[i].Employees, Trans1st);
				}
				for (list<Employee>::iterator l = CompanyVector[i].Employees.begin();l!=CompanyVector[i].Employees.end();++l)
				{if (l->CompanyRank >= e.CompanyRank)
				{l->CompanyRank -= 1;}//end if
				}//end for
				}//end for
			}//end for
//Employee Starts his new job
			Company c = FindCompany(CompanyVector, Trans2nd);//find the labeled company (Trans2nd)
			c.Employees.push_back(e); //add employee to new company
			e.CompanyRank = 0; //Reset to 0, next for loop will increase this to the proper 1 while also increasing everyone above.
			for (list<Employee>::iterator l = c.Employees.begin();l!=c.Employees.end();++l)
			{l->CompanyRank += 1;}//end for
			break;
		} //end case C
		case 'S': //SALARY IS PAID
		{
			//putback Trans1st Trans2nd
			for (unsigned i=0;i<CompanyVector.size();++i) //For each company in company vector
			{
				for (list<Employee>::iterator l = CompanyVector[i].Employees.begin();l!=CompanyVector[i].Employees.end();++l)
				{
					l->TotalSalary += l->CompanyRank*1000; //increase Employee.TotalSalary by CompanyRank*$1000
					CompanyVector[i].setTotalSalariesPaid(l->CompanyRank*1000); //increase Company.TotalSalariesPaid by Employee.CompanyRank*$1000
				}//end for 
			}//end for
			for (list<Employee>::iterator l = Unemployed.begin();l!=Unemployed.end();++l)
			{
				l->TotalSalary += 50;//Pay $50 to everyone on Unemployed list
			}
			break;
		}//end case S
		case 'E': //EMPLOYEES E <Company>
		{
			//putback Trans2nd
			cout << "Employee list for " << Trans1st << endl; //prints a header with the company name (Trans1st)
			for (list<Employee>::iterator l = Unemployed.begin();l!=Unemployed.end();++l)
			{
				cout << l->CompanyRank << ": " << l->EmployeeName << " currently makes " << l->CompanyRank*1000 << " with a total earned of " << l->TotalSalary << endl;
			}//end for
			//then the current list of employees for the specified <Company>.
			//The employees must be printed in order of rank; either top to bottom or bottom to top is appropriate.
			//Also print the employee's current salary and salary-to-date.
			break;
		}//end case E
		case 'U': //UNEMPLOYED LIST
		{
			//putback Trans1st Trans2nd
			cout << "Currently Unemployment list" << endl;
			for (list<Employee>::iterator l = Unemployed.begin();l!=Unemployed.end();++l)
			{
				cout << l->EmployeeName << " was last employed at " << l->LastCompany << endl;
			}//end for
			break;
		}//end case U
		case 'D': //DUMP
		{
			//putback Trans1st Trans2nd
			cout << "Current list of active employees for each company." << endl;
			//a copy of the information in E basically goes here 
			cout << "Currently Unemployment list" << endl;
			for (list<Employee>::iterator l = Unemployed.begin();l!=Unemployed.end();++l)
			{
				cout << l->EmployeeName << " was last employed at " << l->LastCompany << endl;
			}//end for
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