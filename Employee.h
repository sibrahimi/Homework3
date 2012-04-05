//Ben Sipes
//bss5h4
//CS201 MWF Spatz
#include "../../std_lib_facilities.h"
using namespace std;
struct Employee
{
	string EmployeeName;
	int TotalSalary;
	string LastCompany;
	int CompanyRank;
Employee FindEmployee(list<Employee> Employees, string EmployeeToFind);
Employee FindEmployee(vector<Employee> Employees, string EmployeeToFind);
};//end struct Employee