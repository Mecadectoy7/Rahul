#ifndef COMPOSITE_H
#define COMPOSITE_H

#include <vector>
#include <string>
using namespace std;

// Component为组合中的对象声明接口 在适当情况下 实现所有类共有接口的默认行为 声明一个接口用于访问和管理Component的子部件
class Component
{
public:
	string name;
	Component(string );
	virtual void Add(Component *) = 0;  // 通常都用Add Remove方法来提供增加或移除树叶或树枝
	virtual void Remove(Component *) = 0;
	virtual void Display(int) = 0;
};

// 在组合中表示叶节点对象 叶节点没有子节点
class Leaf:public Component
{
public:
	Leaf(string name):Component(name) {}   
	void Add(Component *);  // 由于叶子没有再增加分支和树叶 所以实现Add Remove没意义 但这样可消除叶节点和枝节点对象在抽象层次的区别 保持完全一致的接口
	void Remove(Component *);
	void Display(int );
};

// 定义有枝节点行为 用来存储子部件 在接口中实现与子部件有关操作 如Add Remove
class Composite:public Component
{
private:
	vector<Component*> components;  // 子对象集合用于存储其下属的枝节点和叶节点
public:
	Composite(string name):Component(name) {}
	void Add(Component *);
	void Remove(Component *);
	void Display(int );
};

// 公司类... 抽象或者接口
class Company {
public:
    Company(string name) 
	{
        this->name = name;
    }
    virtual void Add(Company* c) = 0;  // 增加
    virtual void Remove(Company* c) = 0;  // 移除
    virtual void Display(int) = 0;  // 显示
    virtual void LineOfDuty() = 0;  // 履行职责...不同部分履行的职责不一样
protected:
    string name;  
};

// 具体公司类 树枝节点 实现接口
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
				c_iter = children.erase(c_iter);  // 当veci.erase(iter)之后 iter就变成了一个野指针
			}  // 但是这种代码也是存在缺陷的 首先是无法连续删除数字3 其次是迭代器在指向vec.end()的时候 还会进行一次++ 这就发生了数组越界 所以我们一概这样修改
			else  
			{
				c_iter++;  // 对一个野指针进行 iter++ 是肯定会出错的
			}
		}
    }
    void Display(int depth) 
	{
        string str(depth, '-');
		str += this->name;
		cout << str << endl;

		vector<Company*>::const_iterator c_iter = children.begin();
		while(c_iter != children.end())  // 不涉及对迭代器本身操作 可正常++
		{
			(*c_iter)->Display(depth+2);  // 沒一級多兩個--
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

// 叶子节点 人力资源部 
class HRDepartment : public Company {
public:  
    HRDepartment(string name):Company(name) {}
	// 葉節點实现Add Remove没意义 但这样可消除叶节点和枝节点对象在抽象层次的区别 保持完全一致的接口
    void Add(Company* ) {}
    void Remove(Company* ) {}
    void Display(int );
    void LineOfDuty();
};

// 叶子节点 财务部类
class FinanceDepartment : public Company {
public:
    FinanceDepartment(string name):Company(name) {}

    void Add(Company* ) {}
    void Remove(Company* ) {}
    void Display(int );
    void LineOfDuty();
};
  

#endif