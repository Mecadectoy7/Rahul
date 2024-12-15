#include <iostream>
#include "factory_method.h"

using namespace std;


AbstractOperation::AbstractOperation()
{
	cout << "AbstractOperation Construct!" << endl;
}

AbstractOperation::~AbstractOperation()
{
	cout << "AbstractOperation Destruct!" << endl;
}

OperationAdd::OperationAdd()
{
	cout << "OperationAdd Construct!" << endl;
}

OperationAdd::~OperationAdd()
{
	cout << "OperationAdd Destruct!" << endl;
}

OperationSub::OperationSub()
{
	cout << "OperationSub Construct!" << endl;
}

OperationSub::~OperationSub()
{
	cout << "OperationSub Destruct!" << endl;
}

OperationMul::OperationMul()
{
	cout << "OperationMul Construct!" << endl;
}

OperationMul::~OperationMul()
{
	cout << "OperationMul Destruct!" << endl;
}

OperationDiv::OperationDiv()
{
	cout << "OperationDiv Construct!" << endl;
}

OperationDiv::~OperationDiv()
{
	cout << "OperationDiv Destruct!" << endl;
}

OperationMod::OperationMod()
{
	cout << "OperationMod Construct!" << endl;
}

OperationMod::~OperationMod()
{
	cout << "OperationMod Destruct!" << endl;
}

void LeiFeng::Wash() {
  cout << "Wash" << endl;
}

void LeiFeng::Sweep() {
  cout << "Sweep" << endl;
}

void LeiFeng::BuyRice() {
  cout << "BuyRice" << endl;
}

LeiFeng::LeiFeng()
{
	cout << "LeiFeng Construct!" << endl;
}

LeiFeng::~LeiFeng()
{
	cout << "LeiFeng Destruct!" << endl;
}

Undergraduate::Undergraduate()
{
	cout << "Undergraduate Construct!" << endl;
}

Undergraduate::~Undergraduate()
{
	cout << "Undergraduate Destruct!" << endl;
}

Volunteer::Volunteer()
{
	cout << "Volunteer Construct!" << endl;
}

Volunteer::~Volunteer()
{
	cout << "Volunteer Destruct!" << endl;
}

LeiFeng * SimpleLeiFengFactory::createLeiFeng(string type)
{
	LeiFeng *lf = nullptr;	
	if (type == "Undergraduate") {
		lf = new Undergraduate();
	}
	else if (type == "Volunteer") {
		lf = new Volunteer();
	}
	return lf;
}

void test1() {
	AbstractOperationFactory* divfac = new DivFactory();	
	AbstractOperationFactory* modfac = new ModFactory();
	AbstractOperation* div = divfac->createOperator();	
	AbstractOperation* oprmod = modfac->createOperator();
	try {
		oprmod->SetNum(5, 6);
		cout << "5 % 6 = " << oprmod->GetResult() << endl;
		div->SetNum(6, 7);
		cout << "6 / 7 = " << div->GetResult() << endl;
		div->SetNum(3.5, 0.0);
		cout << "3.5 / 0.0 = " << div->GetResult() << endl;
	}
	catch (const char* err) { 
		cout << err << endl;
	}
	catch (...) {
		cout << "This is a exception without handling.\n";
	}
	delete div;	
	div = nullptr;
	delete divfac;
	divfac = nullptr;
	delete oprmod;
	oprmod = nullptr;
	delete modfac;
	modfac = nullptr;
}

void test2() {
	string s = "Undergraduate";
	SimpleLeiFengFactory *simlffac = new SimpleLeiFengFactory();
	LeiFeng *simlf = simlffac->createLeiFeng(s);
	simlf->Sweep();
	delete(simlf);
	simlf = nullptr;
	delete(simlffac);
	simlffac = nullptr;
	IFactory *lffac = new UndergraduateFactory();	
	LeiFeng *stu = lffac->createLeiFeng();
	stu->BuyRice();
	delete stu;
	stu = nullptr;
	delete lffac;
	lffac = nullptr; 
}

int main()
{
	system("chcp 65001");   
	test1();
	test2();

	getchar();	
	return 0;
}