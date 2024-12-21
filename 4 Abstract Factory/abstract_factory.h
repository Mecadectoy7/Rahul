#ifndef ABSTRACT_FACTORY_H
#define ABSTRACT_FACTORY_H

class AbstractUser { 
public:
    virtual void Insert(AbstractUser*) = 0;
    virtual AbstractUser* GetUser(int) = 0;
};

class SqlserverUser : public AbstractUser {
public:
    void Insert(AbstractUser* user);  
    AbstractUser* GetUser(int id);
};

class AccessUser : public AbstractUser {
public:
    void Insert(AbstractUser* user);  
    AbstractUser* GetUser(int id);
};

class AbstractDepartment   
{
public:
    virtual void Insert(AbstractDepartment*) = 0;
    virtual AbstractDepartment* GetDepartment(int) = 0;
};

class SqlserverDepartment : public AbstractDepartment {
public:
    void Insert(AbstractDepartment* department);  
    AbstractDepartment* GetDepartment(int id);
};

class AccessDepartment : public AbstractDepartment {
public:
    void Insert(AbstractDepartment* department);  
    AbstractDepartment* GetDepartment(int id);
};


class AbstractFactory {	
public:	
	virtual AbstractUser* CreateUser() = 0;	
	virtual AbstractDepartment* CreateDepartment() = 0;	
};	

class SqlserverFactory: public AbstractFactory {
public:
    AbstractUser* CreateUser();	
    AbstractDepartment* CreateDepartment();
};

class AccessFactory : public AbstractFactory {
public:
    AbstractUser* CreateUser();	
    AbstractDepartment* CreateDepartment();
};

#endif 