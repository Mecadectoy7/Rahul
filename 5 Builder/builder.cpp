#include "builder.h"
#include <iostream>
#include <string>

using namespace std;


void Product::Add(string part)
{
	parts.push_back(part);
}

void Product::Show()
{
	cout << "product  creat" << endl;
	for (vector<string>::const_iterator c_iter = parts.begin(); c_iter != parts.end(); c_iter++)
	{
		cout << *c_iter << endl;
	}  
}

void ConcreteBuilder1::BuildPartA() 
{
    product->Add("PartA");
}

void ConcreteBuilder1::BuildPartB() 
{
    product->Add("PartB");
}

void ConcreteBuilder1::BuildPartC() 
{
    product->Add("PartC");
}


Product* ConcreteBuilder1::GetResult()  
{
    return product;
}

void ConcreteBuilder2::BuildPartA()  
{
    product->Add("PartX");
}

void ConcreteBuilder2::BuildPartB()  
{
    product->Add("PartY");
}

void ConcreteBuilder2::BuildPartC()  
{
    product->Add("PartZ");
}


Product* ConcreteBuilder2::GetResult()  
{
    return product;
}

void Director::Construct(Builder* const b)
{
    b->BuildPartA();
    b->BuildPartB();
	b->BuildPartC();
}


int main()
{
    Director* director = new Director;
    Builder* b1 = new ConcreteBuilder1;
    Builder* b2 = new ConcreteBuilder2;

    cout << "ConcreteBuilder1:" << endl;
    director->Construct(b1);
    Product* p1 = b1->GetResult();
    p1->Show();  

    cout << "ConcreteBuilder2:" << endl;
    director->Construct(b2);
    Product* p2 = b2->GetResult();
    p2->Show();  

	delete director;	
    delete p2, p1; 
    delete b1, b2;
	director = nullptr;
    p2 = p1 = nullptr;
    b1 = b2 = nullptr;
    
	getchar();	
	return 0;
}