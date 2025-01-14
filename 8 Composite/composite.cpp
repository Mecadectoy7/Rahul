#include <iostream> 
#include <string>
#include <vector>
#include "composite.h"

using namespace std;

/* 组合模式 将对象组合成树形结构以表示 部分-整体 的层次结构 组合模式使得用户对单个对象和组合对象的使用具有一致性
	(抽象)Product	—>		(抽象)Creator(工廠類)
			△						△
			|						|
(抽象)Product接口n(运算類)<--(抽象)Creator接口n(工廠類)
			△						△
			|						|
	具体Product(运算類)	<-- 具体Creator(工廠類)
	其实就是从一个对象再创建另外一个可定制的对象 非传引用或传地址 而且不需知道任何创建的细节
*/

void ConcreteComponent::Operation() 
{
    cout << "具体对象的操作" << endl;
}  

void Decorator::SetComponent(Component *c)
{
    this->component = c;
}

void Decorator::Operation()
{
    if (this->component != nullptr)
        this->component->Operation();
}

Decorator::~Decorator()
{
	if (this->component != nullptr)
	{
		delete this->component;
		this->component = nullptr;
	}
}  

void ConcreteDecoratorA::Operation()  
{
    if (this->component != nullptr)  // 先運行原component的operation 在執行本類的功能 相當於對原component進行了裝飾
        this->component->Operation();
	*addedState = "New State";
	cout << "具体服飾對象A的操作" << endl;
}

ConcreteDecoratorA::~ConcreteDecoratorA()
{
	if (this->addedState != nullptr)
	{
		delete this->addedState;
		this->addedState = nullptr;
	}
}

void ConcreteDecoratorB::Operation()  
{
    if (this->component != nullptr)  // 先運行原component的operation 在執行本類的功能 相當於對原component進行了裝飾
        this->component->Operation();
	AddedBehavior();
	cout << "具体服飾對象B的操作" << endl;
}

void ConcreteDecoratorB::AddedBehavior()
{

}

void Leaf::Remove(Component *c)  
{
	cout << "Leaf cannot remove" << endl;
}

void Leaf::Display(int depth)  
{
	string str(depth, '-');  
	str += this->name;  
	cout<< str <<endl;  
}

void Composite::Add(Component *c)
{  // emplace_back()执行效率比push_back()高 是C++11标准新增加的 如果程序要兼顾之前的版本 还是应该使用 push_back()
	this->components.push_back(c);
}

void Composite::Remove(Component *c)
{
	vector<Component*>::const_iterator c_iter = components.begin();
	while(c_iter != components.end())
	{
		if(*c_iter == c)
		{
			c_iter = components.erase(c_iter);  // 当veci.erase(iter)之后 iter就变成了一个野指针
		}  // 但是这种代码也是存在缺陷的 首先是无法连续删除数字3 其次是迭代器在指向vec.end()的时候 还会进行一次++ 这就发生了数组越界 所以我们一概这样修改
		else  
		{
			c_iter++;  // 对一个野指针进行 iter++ 是肯定会出错的
		}
	}
	/*for (vector<Component*>::const_iterator c_iter = components.begin(); c_iter != components.end(); )
	{  // std::remove(first,last,val)移除[first, last)范围内等于val的元素 但这个函数只是把val移到vec的末尾 并不真正删除 真正删除还是要调用一次erase函数
		if(*iter == c)
		{
			iter = components.erase(iter);
			// break;
		}
		else
		{
			c_iter++
		}
	}*/
}

void Composite::Display(int depth)
{
	string str(depth, '-');
	str += this->name;
	cout<< str <<endl;

	vector<Component*>::const_iterator c_iter = components.begin();
	while(c_iter != components.end())  // 不涉及对迭代器本身操作 可正常++
	{
		(*c_iter)->Display(depth+2);
		c_iter++;
	}
}

void HRDepartment::Display(int depth) 
{
    string s(depth, '-');
    cout << s << this->name << endl;  
}

void HRDepartment::LineOfDuty() 
{
    cout << this->name << "员工招聘培训管理" << endl;
}

void FinanceDepartment::Display(int depth) 
{
    string  s(depth, '-');
    cout << s << this->name << endl;
}

void FinanceDepartment::LineOfDuty() 
{
	cout << this->name << "公司财务收支管理" << endl;
}


// 客戶端代碼
void test1()
{	
	Component *root = new Composite("root"); 
	root->Add(new Leaf("Leaf A"));  
	root->Add(new Leaf("Leaf B"));  

	Component *comp = new Composite("Composite X");  // 根上长出分支Composite X
	comp->Add(new Leaf("Leaf XA"));  
	comp->Add(new Leaf("Leaf XB"));  
	
	root->Add(comp);  

	Component *comp2 = new Composite("Composite XY");  // 根上长出分支Composite X
	comp2->Add(new Leaf("Leaf XYA"));  
	comp2->Add(new Leaf("Leaf XYB"));  
	
	comp->Add(comp2);  

	root->Add(new Leaf("Leaf C")); 

	Component *leafd = new Leaf("Leaf D");
	root->Add(leafd);  
	root->Remove(leafd);

	root->Display(0);  
	cout << "*******" << endl;
	comp->Display(2);  // 第二級
	 

	// 按顺序释放对象指针防止空指针 先釋放運算類成員再釋放工廠類
	delete comp2, comp, root;	// 先釋放產品類對象 成員指針也在裏面(存儲空間地址)
	root = comp = comp2 = nullptr;    
}

void test2()
{
	Company* root = new ConcreteCompany("北京总公司");
    root->Add(new HRDepartment("总公司人力资源部"));
    root->Add(new FinanceDepartment("总公司财务部"));

    Company* comp = new ConcreteCompany("上海华东分公司");
    comp->Add(new HRDepartment("华东分公司人力资源部"));
    comp->Add(new FinanceDepartment("华东分公司财务部"));
    root->Add(comp);

    Company* comp1 = new ConcreteCompany("南京办事处");
    comp1->Add(new HRDepartment("南京办事处人力资源部"));
    comp1->Add(new FinanceDepartment("南京办事处财务部"));
    comp->Add(comp1);

    Company* comp2 = new ConcreteCompany("杭州办事处");
    comp2->Add(new HRDepartment("杭州办事处人力资源部"));
    comp2->Add(new FinanceDepartment("杭州办事处财务部"));
    comp->Add(comp2);

    cout << "结构图: " << endl;
    root->Display(1);

    cout << "\n职责图: " << endl;
    root->LineOfDuty();

    delete comp2, comp1, comp, root;
	root = comp = comp1 = comp2 = nullptr; 
}

int main() 
{
	test1();	// 寫在局部函數也看不到析構釋放
	test2();
	/*user=DataAccess::createUser();
	department=DataAccess::createDepartment();

	user->getUser();
	user->setUser();
	department->getDepartment();
	department->setDepartment();*/

	getchar();	// system("pause")	waitKey(0);
	return 0;
}
// 靜態全局變量生存周期 看不到析構釋放
// 单例对象创建！
// 单例对象销毁！
