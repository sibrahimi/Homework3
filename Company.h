//Ben Sipes
//bss5h4
//CS201 MWF Spatz
#include "Employee.h"
using namespace std;
class Company
{
private:
	string CompanyName;
	list<Employee> Employees;
public:
	Company(string NewCompanyName); //default constructor
	string getCompanyName() const {return CompanyName;} //getter
	list<Employee> getEmployees() const {return Employees;} //getter
void setCompanyName(string NewCompanyName); //setter
void setNewEmployee(Employee NewEmployee); //setter
}; //end class Company------------------------------------------------
ostream& operator << (ostream& out, const Company& cmp);
istream& operator >> (istream& in, const Company& cmp);