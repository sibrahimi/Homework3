//Ben Sipes
//bss5h4
//CS201 MWF Spatz
#include "Employee.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
using namespace std;
class Company
{
private:
	string CompanyName;
	list<Employee> Employees;
public:
	//Company();
	Company(string NewCompanyName);
	string getCompanyName() const {return CompanyName;}
	list<Employee> getEmployees() const {return Employees;}
void setCompanyName(string NewCompanyName);
void setNewEmployee(Employee NewEmployee);
}; //end class Company------------------------------------------------
ostream& operator << (ostream& out, const Company& cmp);
istream& operator >> (istream& in, Company& cmp);
ifstream& operator >> (istream& fin, const Company& cmp);