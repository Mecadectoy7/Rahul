#include <iostream>
#include "adapter.h"
#include <string>

using namespace std;


void Adaptee::SpecialRequest()
{
	cout << "Request" << endl;
}

void Adapter::Request()
{
	this->adaptee->SpecialRequest();
}

Adapter::Adapter()
{
	this->adaptee = new Adaptee();
}

Adapter::~Adapter() 
{
	if (this->adaptee != nullptr) 
	{ 
		delete this->adaptee;
		this->adaptee = nullptr;
	}
}

void Forwards::Attack() 
{  
    cout << "Forwards" << name << "Attack" << endl;
}

void Forwards::Defense() 
{     
    cout << "Forwards" << name << "Defense" << endl;
}

void Center::Attack() 
{    
    cout << "Center" << name << "Attack" << endl;
}

void Center::Defense() 
{     
    cout << "Center" << name << "Defense" << endl;
} 

void Guards::Attack() 
{    
    cout << "Guards" << name << "Attack" << endl;
}

void Guards::Defense() 
{     
    cout << "Guards" << name << "Defense" << endl;
} 

void ForeignCenter::SetName(string name) 
{
    this->name = name;  
}

string ForeignCenter::GetName() 
{
    return this->name;  
}

void ForeignCenter::ForeignAttack() 
{  
    cout << "ForeignCenter" << this->name << "Attack" << endl;
}

void ForeignCenter::ForeignDefense() 
{
    cout << "ForeignCenter" << this->name << "Defense" << endl;
}

Translator::~Translator()
{
    if (this->yaoming != nullptr) 
	{ 
		delete this->yaoming;
		this->yaoming = nullptr;
	}
}

void Translator::Attack() 
{   
    this->yaoming->ForeignAttack();
}

void Translator::Defense() 
{
    this->yaoming->ForeignDefense(); 
} 


void test1()
{	
	Target *adapter = new Adapter();  
	adapter->Request();  
	delete adapter;	 
	adapter = nullptr;  

	Player* b = new Forwards("Batell");
    b->Attack();
    Player* c = new Guards("Michael");
    c->Attack();
    Player* ym  = new Translator("yaoming");  
    ym->Attack();  
    ym->Defense();  

	delete b, c, ym;	
	ym = b = c = nullptr;    
}

int main() 
{
	test1();	

	getchar();	
	return 0;
}
