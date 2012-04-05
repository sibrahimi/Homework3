//Ben Sipes
//bss5h4
//CS201 MWF Spatz
#include "Employee.h"
using namespace std;
class Company
{
private:
	string CompanyName;
	int TotalSalariesPaid;
public:
	list<Employee> Employees;
	Company(string NewCompanyName); //default constructor
	string getCompanyName() const {return CompanyName;} //getter
void setCompanyName(string NewCompanyName); //setter
void setTotalSalariesPaid(int Payday); //setter
}; //end class Company------------------------------------------------
ostream& operator << (ostream& out, const Company& cmp);
ostream& operator << (ostream& out, Employee& emp);
istream& operator >> (istream& in, const Company& cmp);