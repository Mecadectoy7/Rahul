#include <iostream>
#include <math.h>
#include <cstdio>
using namespace std;


class AbstractOperation {
public:
	double GetNumA() {	
        return NumA;
    }

	double GetNumB() {	
        return NumB;
    }

	virtual double GetResult() = 0;	

	void SetNum(double _NumA, double _NumB){
		this->NumA = _NumA;
		this->NumB = _NumB;
	}
	AbstractOperation();	
	virtual ~AbstractOperation();	

private:	
	double NumA;	
	double NumB;	
};

AbstractOperation::AbstractOperation()
{
	cout << "AbstractOperation Construct!" << endl;
}

AbstractOperation::~AbstractOperation()
{
	cout << "AbstractOperation Destruct!" << endl;
}

class OperationAdd : public AbstractOperation {
public:
	virtual double GetResult() {
		return GetNumA() + GetNumB();
	}
	OperationAdd();	
	virtual ~OperationAdd();	
};

OperationAdd::OperationAdd()
{
	cout << "OperationAdd Construct!" << endl;
}

OperationAdd::~OperationAdd()
{
	cout << "OperationAdd Destruct!" << endl;
}

class OperationSub : public AbstractOperation {
public:
	virtual double GetResult() {
		return GetNumA() - GetNumB();
	}
	OperationSub();	
	virtual ~OperationSub();	
};

OperationSub::OperationSub()
{
	cout << "OperationSub Construct!" << endl;
}

OperationSub::~OperationSub()
{
	cout << "OperationSub Destruct!" << endl;
}

class OperationMul : public AbstractOperation {
public:
	virtual double GetResult() {
		return GetNumA() * GetNumB();
	}
	OperationMul();	
	virtual ~OperationMul();	
};

OperationMul::OperationMul()
{
	cout << "OperationMul Construct!" << endl;
}

OperationMul::~OperationMul()
{
	cout << "OperationMul Destruct!" << endl;
}

class OperationDiv : public AbstractOperation {
public:
	virtual double GetResult() {
		if (fabs(GetNumB()) < 1e-15)	
			throw "The divisor cannot be 0!\n";	
		return GetNumA() / GetNumB();
	}
	OperationDiv();	
	virtual ~OperationDiv();	
};

OperationDiv::OperationDiv()
{
	cout << "OperationDiv Construct!" << endl;
}

OperationDiv::~OperationDiv()
{
	cout << "OperationDiv Destruct!" << endl;
}


class OperationFactory {
public:	
	static AbstractOperation* createOperator(char sOperator) {   
		switch (sOperator)  
		{
		case '+':
			return new OperationAdd();	
		case '-':
			return new OperationSub();
		case '*': 
			return new OperationMul();
		case '/':
			return new OperationDiv();
		default:
			throw "Error input operator!\n";
			break;
		}
	}
};

void test1() {
	OperationFactory* factory = new OperationFactory;
	AbstractOperation* operate = factory->createOperator('/');  
	try {
		operate->SetNum(6, 7);
		cout << operate->GetResult() << endl;
		operate->SetNum(3.5, 0.0);
		cout << operate->GetResult() << endl;
	}
	catch (const char* err) { 
		cout << err << endl;
	}
	catch (...) {
		cout << "This is a exception without handling.\n";
	}
	delete operate;
	delete factory;
}

int main(void)
{
	FILE *fp = NULL;
	double ticker = 0, acc = 0, curvel = 0;
	fp = fopen("./test.txt", "r");    
    if (fp == NULL) {
        printf("error: file not found");
    }
	else {
		fscanf(fp, "%.3f", &ticker);
	}
	printf("ticker=%.3f\n", ticker);
	fclose(fp);

	system("pause");
	return 0;
}


