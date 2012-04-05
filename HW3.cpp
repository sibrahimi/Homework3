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
	//causes a warning, since if the company name isn't found, nothing will be returned.
	//in our setting, this will never happen.
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
	for (list<Employee>::iterator a = Container.begin();a!=Container.end();++a)
	{
		if (a->EmployeeName == EmployeeToRemove)
		{Container.erase(a);} //REMOVES EMPLOYEE FROM LIST
		break;
	}//end for
}//end RemoveEmployeeFromList
int main()
{
	list<Employee> Unemployed;
	vector<Company> CompanyVector;
	vector<Employee> EmployeeVector;
//start reading in text from Company.txt
	ifstream infile;
	infile.open("company.txt");
	ofstream fout;
	fout.open("out.dat");
	cout << "Loading company list..." << endl;
	fout << "Loading company list..." << endl;
	while (!infile.eof())
	{
		string NewCompanyName;
		infile >> NewCompanyName; //read in the company name
		if (NewCompanyName.length()>0) //avoids creating company objects out of empty lines
		{
			Company temp(NewCompanyName);//create company object
			CompanyVector.push_back(temp);//put company object into CompanyVector
		} //end if
	}//end while
	infile.close();
//finish reading in text from Company.txt
//start reading in text from trans_file.dat
	infile.open("trans_file.dat"); //opens a new file this time
	cout << "Begin processing transactions..." << endl;
	fout << "Begin processing transactions..." << endl;
	char TransCommand;
	while (!infile.eof())
	{
		string Trans1st;
		string Trans2nd;
		infile >> TransCommand;
		switch (TransCommand) 
		{
		case 'J': //JOIN J <Person> <Company>
		{
			infile >> Trans1st >> Trans2nd;
			cout << "JOIN " << Trans1st<< " to " << Trans2nd << endl;
			fout << "JOIN " << Trans1st<< " to " << Trans2nd << endl;
			Company c = FindCompany(CompanyVector, Trans2nd);//find the labeled company (Trans2nd)
			Employee e = FindEmployee(EmployeeVector, Trans1st);//find/create the employee (Trans1st)
			c.Employees.push_back(e); //add employee to new company
			RemoveEmployeeFromList(Unemployed,Trans1st); //if employee with name Trans1st exists in unemployed list, removes them
			e.LastCompany = ""; //should ONLY be set if they are unemployed
			e.CompanyRank = 0; //Reset to 0, next for loop will increase this to the proper 1 while also increasing everyone above.
			for (list<Employee>::iterator l = c.Employees.begin();l!=c.Employees.end();++l)
			{l->CompanyRank += 1;}//end for
			for (unsigned i=0;i<CompanyVector.size();++i) //Update the company in the CompanyVector
			{if (CompanyVector[i].getCompanyName() == Trans2nd)
			{CompanyVector[i] = c;}}//end if //end for
			break;
		}//end CASE J
		case 'Q': //QUIT Q <Person>
		{
			infile >> Trans1st;
			cout << "QUIT: " << Trans1st << endl;
			fout << "QUIT: " << Trans1st << endl;
//remove employee from company list
			Employee e = FindEmployee(EmployeeVector, Trans1st);
			for (unsigned i=0;i<CompanyVector.size();++i) //find the company the employee worked for
			{
				for (list<Employee>::iterator l = CompanyVector[i].Employees.begin();l!=CompanyVector[i].Employees.end();++l)
				{ //check every employee of this company
					if (l->EmployeeName == Trans1st) //if this company has the employee that is quitting
					{
						e.LastCompany = CompanyVector[i].getCompanyName(); //set their LastCompany, as they are now Unemployed.
						RemoveEmployeeFromList(CompanyVector[i].Employees, Trans1st);
					}//end if
				for (list<Employee>::iterator l = CompanyVector[i].Employees.begin();l!=CompanyVector[i].Employees.end();++l)
				{if (l->CompanyRank >= e.CompanyRank) //reduce the rank of everyone above the quitter by 1
				{l->CompanyRank -= 1;}//end if
				}//end for
				}//end for
			}//end for
			Unemployed.push_back(e); //add employee to unemployed list
			break;
		}//end case Q
		case 'C': //CHANGE C <Person> <Company>
		{
			infile >> Trans1st >> Trans2nd;
			cout << "CHANGE " << Trans1st << " to " << Trans2nd << endl;
			fout << "CHANGE " << Trans1st << " to " << Trans2nd << endl;
//C is essentially a combination of Q followed by J, but without the Unemployment inbetween.
//Employee quits his old job
			Employee e = FindEmployee(EmployeeVector, Trans1st);
			for (unsigned i=0;i<CompanyVector.size();++i)
			{
				for (list<Employee>::iterator l = CompanyVector[i].Employees.begin();l!=CompanyVector[i].Employees.end();++l)
				{
					if (l->EmployeeName == Trans1st)
					{
						l->LastCompany = CompanyVector[i].getCompanyName();
						RemoveEmployeeFromList(CompanyVector[i].Employees, Trans1st);
						for (list<Employee>::iterator k = CompanyVector[i].Employees.begin();k!=CompanyVector[i].Employees.end();++k)
						{
							if (k->CompanyRank >= e.CompanyRank)
							{
								k->CompanyRank -= 1;
							}//end if
						}//end for
					}//end if
				}//end for
			}//end outer-most for (companyvector.size)
//Employee Starts his new job
			Company c = FindCompany(CompanyVector, Trans2nd);//find the labeled company (Trans2nd)
			c.Employees.push_back(e); //add employee to new company
			e.CompanyRank = 0; //Reset to 0, next for loop will increase this to the proper 1 while also increasing everyone above.
			for (list<Employee>::iterator j = c.Employees.begin();j!=c.Employees.end();++j)
			{j->CompanyRank += 1;}//end for
			for (unsigned i=0;i<CompanyVector.size();++i) //Update the company in the CompanyVector
			{if (CompanyVector[i].getCompanyName() == Trans2nd)
			{CompanyVector[i] = c;}}//end if //end for
			break;
		} //end case C
		case 'S': //SALARY IS PAID
		{
			cout << endl << "Paying salaries..." << endl << endl;
			fout << endl << "Paying salaries..." << endl << endl;
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
			infile >> Trans1st;
			Company c = FindCompany(CompanyVector, Trans1st);//find the labeled company (Trans1st)
			cout << "Employee list for " << c.getCompanyName() << endl; //prints a header with the company name (Trans1st)
			fout << "Employee list for " << Trans1st << endl;
			for (list<Employee>::iterator b = c.Employees.begin();b!=c.Employees.end();++b)
			{
				cout << b->CompanyRank << ": " << b->EmployeeName << " currently makes " << b->CompanyRank*1000 << " with a total earned of " << b->TotalSalary << endl;
				fout << b->CompanyRank << ": " << b->EmployeeName << " currently makes " << b->CompanyRank*1000 << " with a total earned of " << b->TotalSalary << endl;
			}//end for
			cout << endl << endl;
			fout << endl << endl;
			break;
		}//end case E
		case 'U': //UNEMPLOYED LIST
		{
			cout << "UNEMPLOYED: " << endl;
			fout << "UNEMPLOYED: " << endl;
			for (list<Employee>::iterator l = Unemployed.begin();l!=Unemployed.end();++l)
			{
				cout << l->EmployeeName << " was last employed at " << l->LastCompany << endl;
				fout << l->EmployeeName << " was last employed at " << l->LastCompany << endl;
			}//end for
			break;
		}//end case U
		case 'D': //DUMP
		{
			cout << endl << "Current list of active employees for each company." << endl;
			fout << endl << "Current list of active employees for each company." << endl;
//a copy of the information in E basically goes here/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
			cout << "Current Unemployment list" << endl;
			fout << "Current Unemployment list" << endl;
			for (list<Employee>::iterator l = Unemployed.begin();l!=Unemployed.end();++l)
			{
				cout << l->EmployeeName << " was last employed at " << l->LastCompany << endl;
				fout << l->EmployeeName << " was last employed at " << l->LastCompany << endl;
			}//end for
			break;
		}//end case D
		case 'F': //FINISH 
		{
			//"prints the message "End of Program"
			cout << "FINISH:" << endl << "End of Transactions" <<endl;
			fout << "FINISH:" << endl << "End of Transactions" <<endl;
			cout << "ACCUMULATED SALARIES - EMPLOYED AND UNEMPLOYED" << endl;
			fout << "ACCUMULATED SALARIES - EMPLOYED AND UNEMPLOYED" << endl;
			for (unsigned i=0;i<EmployeeVector.size();++i)
			{
				cout << EmployeeVector[i].EmployeeName << "\t" << EmployeeVector[i].TotalSalary << endl;
				fout << EmployeeVector[i].EmployeeName << "\t" << EmployeeVector[i].TotalSalary << endl;
			}//end for
			break;
		}//end case F
		}//end switch Command
	}//end while READING FILE
	infile.close();
	fout.flush();
	fout.close();
	keep_window_open();
}//end main