#include <iostream>
#include "abstract_factory.h"
#include <string>

using namespace std;


AbstractUser* SqlserverFactory::CreateUser()
{
	return new SqlserverUser();
}

AbstractDepartment* SqlserverFactory::CreateDepartment()
{
	return new SqlserverDepartment();
}

AbstractUser* AccessFactory::CreateUser()
{
	return new AccessUser();
}

AbstractDepartment* AccessFactory::CreateDepartment()
{
	return new AccessDepartment();
}


void SqlserverUser::Insert(AbstractUser* user)
{
	cout << "Insert!" << endl;
}

AbstractUser* SqlserverUser::GetUser(int id) 
{
    cout << "SQL ID:" << id << "User!" << endl;
    return nullptr;
}

void AccessUser::Insert(AbstractUser* user)
{
	cout << "Insert!" << endl;
}

AbstractUser* AccessUser::GetUser(int id) {
    cout << "Access ID:" << id << "User!" << endl;
    return nullptr;
}


void SqlserverDepartment::Insert(AbstractDepartment* department)
{
	cout << "SQL Department Insert!" << endl;
}

AbstractDepartment* SqlserverDepartment::GetDepartment(int id) 
{
    cout << "SQL ID:" << id << "Department!" << endl;
    return nullptr;
}

void AccessDepartment::Insert(AbstractDepartment* department)
{
	cout << "Access Department Insert!" << endl;
}

AbstractDepartment* AccessDepartment::GetDepartment(int id) 
{
    cout << "Access ID:" << id << "Department!" << endl;
    return nullptr;
}


class DataAccess {
private:
	static string db;
	//string db = "access";
public:
	static AbstractUser *CreateUser()  
	{
		if (db == "access")  
		{
			return new AccessUser();
		}
		else if (db == "sql")
		{
			return new SqlserverUser();
		}
	}
	static AbstractDepartment *CreateDepartment()
	{
		if (db == "access")
		{
			return new AccessDepartment();
		}
		else if (db == "sql")
		{
			return new SqlserverDepartment();
		}	
	}
};

string DataAccess::db = "sql";


void test1()
{	
	//AbstractFactory* ifactory = new SqlserverFactory();  
	AbstractFactory* ifactory = new AccessFactory();  

	AbstractUser* iuser = ifactory->CreateUser();	
	iuser->Insert(iuser);
	iuser->GetUser(0);

	AbstractDepartment* idepartment = ifactory->CreateDepartment(); 
    idepartment->Insert(idepartment);
    idepartment->GetDepartment(0);

	delete iuser;	
	iuser = nullptr;
    delete idepartment;
	idepartment = nullptr;
    delete ifactory;
    ifactory = nullptr; 

}

int main() 
{
	test1();	

	getchar();	
	return 0;
}
