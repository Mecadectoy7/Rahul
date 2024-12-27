#ifndef BUILDER_H
#define BUILDER_H

#include <vector>  
#include <string>

using namespace std;

class Product
{
private:
	vector<string> parts;
public:
	void Add(string part);
	void Show();
};


class Builder   
{
public:
    virtual void BuildPartA() = 0;  
    virtual void BuildPartB() = 0;  
	virtual void BuildPartC() = 0;  
	virtual Product* GetResult() = 0;  
};


class ConcreteBuilder1 : public Builder {
private:  
    Product* product;  
public:
	ConcreteBuilder1()
	{
		product = new Product;
	};
    void BuildPartA(); 
    void BuildPartB(); 
	void BuildPartC();  
    Product* GetResult();  
};


class ConcreteBuilder2 : public Builder {
private:
    Product* product;
public:
	ConcreteBuilder2()
	{
		product = new Product;
	};
    void BuildPartA(); 
    void BuildPartB(); 
	void BuildPartC(); 
    Product* GetResult();  
};


class Director 
{
public:
    void Construct(Builder* const b);
};

#endif 