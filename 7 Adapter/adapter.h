#ifndef ADAPTER_H
#define ADAPTER_H

#include <string>

using namespace std;  


class Adaptee {
public:
	virtual void SpecialRequest();
};

class Target {
public:
	virtual void Request()=0;  
	virtual ~Target(){};  
};

class Adapter : public Target {
private:
	Adaptee* adaptee;  
public:
	Adapter();  
    ~Adapter();  
	void Request();  
};

class Player {
protected:
    string name;
public:
    Player(string name):name(name){};  
    virtual void Attack() = 0;  
    virtual void Defense() = 0;  
    virtual ~Player(){};  
};

class Forwards : public Player {
public:
    Forwards(string name):Player(name){};  
    void Attack();  
    void Defense();  
};

class Center : public Player
{
public:
    Center(string name):Player(name){};  
    void Attack();  
    void Defense();  
};

class Guards : public Player {
public:
    Guards(string name):Player(name){};  
    void Attack();  
    void Defense();  
};

class ForeignCenter {
private:
	string name;  
public:
	void SetName(string);
    string GetName();
    void ForeignAttack();
    void ForeignDefense();
};

class Translator : public Player { 
private:
    ForeignCenter* yaoming; 
public:
    Translator(string name) : Player(name)
	{
		this->yaoming = new ForeignCenter();  
		this->yaoming->SetName(name);  
	}
    ~Translator();  
    void Attack();  
    void Defense();  
};

#endif