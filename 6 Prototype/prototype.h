#ifndef PROTOTYPE_H
#define PROTOTYPE_H

#include <string>

using namespace std;


class WorkExperience  {  
private:
    string workDate, company;
public:
	WorkExperience(){};
    ~WorkExperience(){};
	WorkExperience(const WorkExperience&);  
    string GetWorkDate();   
    void SetWorkDate(string);  
    string GetCompany();
    void SetCompany(string);  
    WorkExperience* Clone();  
};

class Prototype {
protected:
    string name, sex, age, timeArea, company;
public:
    virtual void SetPersonalInfo(string, string) = 0;
    virtual void Display() = 0;
    virtual Prototype* Clone() = 0;
};

class Resume :public Prototype {  
private:
    WorkExperience* work;
public:
    Resume(string);  
    ~Resume();    
    Resume(WorkExperience*);  
    void SetPersonalInfo(string, string);  
    void SetWorkExperience(string, string);   

    void Display();   
    Prototype* Clone();  
};

#endif