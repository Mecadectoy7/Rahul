#include <iostream> 
#include <string>
#include <vector>
#include "composite.h"

using namespace std;

/* ���ģʽ ��������ϳ����νṹ�Ա�ʾ ����-���� �Ĳ�νṹ ���ģʽʹ���û��Ե����������϶����ʹ�þ���һ����
	(����)Product	��>		(����)Creator(���S�)
			��						��
			|						|
(����)Product�ӿ�n(�����)<--(����)Creator�ӿ�n(���S�)
			��						��
			|						|
	����Product(�����)	<-- ����Creator(���S�)
	��ʵ���Ǵ�һ�������ٴ�������һ���ɶ��ƵĶ��� �Ǵ����û򴫵�ַ ���Ҳ���֪���κδ�����ϸ��
*/

void ConcreteComponent::Operation() 
{
    cout << "�������Ĳ���" << endl;
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
    if (this->component != nullptr)  // ���\��ԭcomponent��operation �ڈ��б�Ĺ��� �ஔ춌�ԭcomponent�M�����b�
        this->component->Operation();
	*addedState = "New State";
	cout << "��������A�Ĳ���" << endl;
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
    if (this->component != nullptr)  // ���\��ԭcomponent��operation �ڈ��б�Ĺ��� �ஔ춌�ԭcomponent�M�����b�
        this->component->Operation();
	AddedBehavior();
	cout << "��������B�Ĳ���" << endl;
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
{  // emplace_back()ִ��Ч�ʱ�push_back()�� ��C++11��׼�����ӵ� �������Ҫ���֮ǰ�İ汾 ����Ӧ��ʹ�� push_back()
	this->components.push_back(c);
}

void Composite::Remove(Component *c)
{
	vector<Component*>::const_iterator c_iter = components.begin();
	while(c_iter != components.end())
	{
		if(*c_iter == c)
		{
			c_iter = components.erase(c_iter);  // ��veci.erase(iter)֮�� iter�ͱ����һ��Ұָ��
		}  // �������ִ���Ҳ�Ǵ���ȱ�ݵ� �������޷�����ɾ������3 ����ǵ�������ָ��vec.end()��ʱ�� �������һ��++ ��ͷ���������Խ�� ��������һ�������޸�
		else  
		{
			c_iter++;  // ��һ��Ұָ����� iter++ �ǿ϶�������
		}
	}
	/*for (vector<Component*>::const_iterator c_iter = components.begin(); c_iter != components.end(); )
	{  // std::remove(first,last,val)�Ƴ�[first, last)��Χ�ڵ���val��Ԫ�� ���������ֻ�ǰ�val�Ƶ�vec��ĩβ ��������ɾ�� ����ɾ������Ҫ����һ��erase����
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
	while(c_iter != components.end())  // ���漰�Ե������������ ������++
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
    cout << this->name << "Ա����Ƹ��ѵ����" << endl;
}

void FinanceDepartment::Display(int depth) 
{
    string  s(depth, '-');
    cout << s << this->name << endl;
}

void FinanceDepartment::LineOfDuty() 
{
	cout << this->name << "��˾������֧����" << endl;
}


// �͑��˴��a
void test1()
{	
	Component *root = new Composite("root"); 
	root->Add(new Leaf("Leaf A"));  
	root->Add(new Leaf("Leaf B"));  

	Component *comp = new Composite("Composite X");  // ���ϳ�����֧Composite X
	comp->Add(new Leaf("Leaf XA"));  
	comp->Add(new Leaf("Leaf XB"));  
	
	root->Add(comp);  

	Component *comp2 = new Composite("Composite XY");  // ���ϳ�����֧Composite X
	comp2->Add(new Leaf("Leaf XYA"));  
	comp2->Add(new Leaf("Leaf XYB"));  
	
	comp->Add(comp2);  

	root->Add(new Leaf("Leaf C")); 

	Component *leafd = new Leaf("Leaf D");
	root->Add(leafd);  
	root->Remove(leafd);

	root->Display(0);  
	cout << "*******" << endl;
	comp->Display(2);  // �ڶ���
	 

	// ��˳���ͷŶ���ָ���ֹ��ָ�� ��ጷ��\��ɆT��ጷŹ��S�
	delete comp2, comp, root;	// ��ጷŮaƷ��� �ɆTָ�Ҳ���Y��(�惦���g��ַ)
	root = comp = comp2 = nullptr;    
}

void test2()
{
	Company* root = new ConcreteCompany("�����ܹ�˾");
    root->Add(new HRDepartment("�ܹ�˾������Դ��"));
    root->Add(new FinanceDepartment("�ܹ�˾����"));

    Company* comp = new ConcreteCompany("�Ϻ������ֹ�˾");
    comp->Add(new HRDepartment("�����ֹ�˾������Դ��"));
    comp->Add(new FinanceDepartment("�����ֹ�˾����"));
    root->Add(comp);

    Company* comp1 = new ConcreteCompany("�Ͼ����´�");
    comp1->Add(new HRDepartment("�Ͼ����´�������Դ��"));
    comp1->Add(new FinanceDepartment("�Ͼ����´�����"));
    comp->Add(comp1);

    Company* comp2 = new ConcreteCompany("���ݰ��´�");
    comp2->Add(new HRDepartment("���ݰ��´�������Դ��"));
    comp2->Add(new FinanceDepartment("���ݰ��´�����"));
    comp->Add(comp2);

    cout << "�ṹͼ: " << endl;
    root->Display(1);

    cout << "\nְ��ͼ: " << endl;
    root->LineOfDuty();

    delete comp2, comp1, comp, root;
	root = comp = comp1 = comp2 = nullptr; 
}

int main() 
{
	test1();	// ���ھֲ�����Ҳ����������ጷ�
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
// �o�Bȫ��׃���������� ����������ጷ�
// �������󴴽���
// �����������٣�
