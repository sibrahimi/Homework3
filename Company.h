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
	list<Employee> getEmployees() {return Employees;} //getter
void setCompanyName(string NewCompanyName); //setter
void setNewEmployee(Employee NewEmployee); //setter
void removeEmployee(Employee ToBeRemoved); //remover
}; //end class Company------------------------------------------------
ostream& operator << (ostream& out, const Company& cmp);
ostream& operator << (ostream& out, Employee& emp);
istream& operator >> (istream& in, const Company& cmp);