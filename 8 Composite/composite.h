#ifndef COMPOSITE_H
#define COMPOSITE_H

#include <vector>
#include <string>
using namespace std;

// ComponentΪ����еĶ��������ӿ� ���ʵ������ ʵ�������๲�нӿڵ�Ĭ����Ϊ ����һ���ӿ����ڷ��ʺ͹���Component���Ӳ���
class Component
{
public:
	string name;
	Component(string );
	virtual void Add(Component *) = 0;  // ͨ������Add Remove�������ṩ���ӻ��Ƴ���Ҷ����֦
	virtual void Remove(Component *) = 0;
	virtual void Display(int) = 0;
};

// ������б�ʾҶ�ڵ���� Ҷ�ڵ�û���ӽڵ�
class Leaf:public Component
{
public:
	Leaf(string name):Component(name) {}   
	void Add(Component *);  // ����Ҷ��û�������ӷ�֧����Ҷ ����ʵ��Add Removeû���� ������������Ҷ�ڵ��֦�ڵ�����ڳ����ε����� ������ȫһ�µĽӿ�
	void Remove(Component *);
	void Display(int );
};

// ������֦�ڵ���Ϊ �����洢�Ӳ��� �ڽӿ���ʵ�����Ӳ����йز��� ��Add Remove
class Composite:public Component
{
private:
	vector<Component*> components;  // �Ӷ��󼯺����ڴ洢��������֦�ڵ��Ҷ�ڵ�
public:
	Composite(string name):Component(name) {}
	void Add(Component *);
	void Remove(Component *);
	void Display(int );
};

// ��˾��... ������߽ӿ�
class Company {
public:
    Company(string name) 
	{
        this->name = name;
    }
    virtual void Add(Company* c) = 0;  // ����
    virtual void Remove(Company* c) = 0;  // �Ƴ�
    virtual void Display(int) = 0;  // ��ʾ
    virtual void LineOfDuty() = 0;  // ����ְ��...��ͬ�������е�ְ��һ��
protected:
    string name;  
};

// ���幫˾�� ��֦�ڵ� ʵ�ֽӿ�
class ConcreteCompany : public Company {
public:
    ConcreteCompany(string name):Company(name) {}

    void Add(Company* c) 
	{
        children.push_back(c);
    }
    void Remove(Company* c) 
	{
        vector<Company*>::const_iterator c_iter = children.begin();
		while(c_iter != children.end())
		{
			if(*c_iter == c)
			{
				c_iter = children.erase(c_iter);  // ��veci.erase(iter)֮�� iter�ͱ����һ��Ұָ��
			}  // �������ִ���Ҳ�Ǵ���ȱ�ݵ� �������޷�����ɾ������3 ����ǵ�������ָ��vec.end()��ʱ�� �������һ��++ ��ͷ���������Խ�� ��������һ�������޸�
			else  
			{
				c_iter++;  // ��һ��Ұָ����� iter++ �ǿ϶�������
			}
		}
    }
    void Display(int depth) 
	{
        string str(depth, '-');
		str += this->name;
		cout << str << endl;

		vector<Company*>::const_iterator c_iter = children.begin();
		while(c_iter != children.end())  // ���漰�Ե������������ ������++
		{
			(*c_iter)->Display(depth+2);  // �]һ�����ɂ�--
			c_iter++;
		}
    }
    void LineOfDuty() 
	{
        for (vector<Company*>::const_iterator c_iter = children.begin(); c_iter != children.end(); c_iter++) 
		{
            (*c_iter)->LineOfDuty();
        }
    } 
private:
    vector<Company*> children;
};

// Ҷ�ӽڵ� ������Դ�� 
class HRDepartment : public Company {
public:  
    HRDepartment(string name):Company(name) {}
	// �~���cʵ��Add Removeû���� ������������Ҷ�ڵ��֦�ڵ�����ڳ����ε����� ������ȫһ�µĽӿ�
    void Add(Company* ) {}
    void Remove(Company* ) {}
    void Display(int );
    void LineOfDuty();
};

// Ҷ�ӽڵ� ������
class FinanceDepartment : public Company {
public:
    FinanceDepartment(string name):Company(name) {}

    void Add(Company* ) {}
    void Remove(Company* ) {}
    void Display(int );
    void LineOfDuty();
};
  

#endif