#include <iostream>
#include "prototype.h"
#include <string>

using namespace std;

WorkExperience::WorkExperience(const WorkExperience& work)  
{
    this->workDate = work.workDate;	
    this->company = work.company;  
}

string WorkExperience::GetWorkDate()
{
    return this->workDate;
}

void WorkExperience::SetWorkDate(string workDate)
{
    this->workDate = workDate;
}

string WorkExperience::GetCompany()
{
    return this->company;
}

void WorkExperience::SetCompany(string company)
{
    this->company = company;
}  

WorkExperience* WorkExperience::Clone()  
{
    return new WorkExperience(*this);  
}


Resume::Resume(string name)  
{
    this->name = name;
    this->work = new WorkExperience();
}

Resume::~Resume() 
{	
    if (this->work != nullptr)
	{
        delete this->work;
		this->work = nullptr;
	}
}

Resume::Resume(WorkExperience* work)  
{
    this->work = work->Clone();  
}

void Resume::SetPersonalInfo(string sex, string age) 
{
    this->sex = sex;
    this->age = age;
}

void Resume::SetWorkExperience(string workDate, string company)  
{
    this->work->SetCompany(company);  
    this->work->SetWorkDate(workDate);  
}

void Resume::Display() 
{
    cout << name << "  " << age << " " << sex << "  " << endl;
    cout << "WorkExperience  " << this->work->GetWorkDate() << "  " << this->work->GetCompany() << endl;
}

Prototype* Resume::Clone() 
{
    Resume* new_resume = new Resume(this->work);
    new_resume->name = this->name;
    new_resume->sex = this->sex;
    return new_resume;  
}


void test1()
{	
	Resume* a = new Resume("A");
    a->SetPersonalInfo("male", "29");
    a->SetWorkExperience("1998-2000", "baidu");

    Resume* b = (Resume*)a->Clone();  
    b->SetWorkExperience("2000-2008", "google");

    Resume* c = (Resume*)a->Clone();
    c->SetPersonalInfo("male", "24");
    c->SetWorkExperience("2000-2008", "apple");

    a->Display();
    b->Display();
    c->Display();

	delete a, b, c;	
	a = b = c = nullptr;    
}

int main() 
{
	test1();	

	getchar();	
	return 0;
}
