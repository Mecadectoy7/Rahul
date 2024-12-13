#include <iostream> 
#include <windows.h>

using namespace std;


class Singleton_lazy {
private:
	Singleton_lazy()  
	{ 
		cout << "Construct！\n"; 
	}
	Singleton_lazy(const Singleton_lazy&);  
	~Singleton_lazy()
	{ 
		cout << "Destruct！\n";
		WaitForSingleObject(mutex, INFINITE);
		delete pInstance;
		pInstance = nullptr;
		ReleaseMutex(mutex);
		CloseHandle(mutex);
	}	 
	static Singleton_lazy* pInstance;  
	static HANDLE mutex;

public:	
	static Singleton_lazy* GetInstance() {
		if (pInstance == nullptr)	
		{	
			WaitForSingleObject(mutex, INFINITE); 
			if (pInstance == nullptr)  
			{	
				pInstance = new Singleton_lazy();
			}
			ReleaseMutex(mutex);
		}
		return pInstance;
	}
};

Singleton_lazy* Singleton_lazy::pInstance = nullptr;	
HANDLE Singleton_lazy::mutex = CreateMutex(NULL, FALSE, NULL);	

class Singleton_hungry {
private:
	Singleton_hungry() 
	{ 
		cout << "Construct！" << endl; 
	}
	Singleton_hungry(const Singleton_hungry&);	
	~Singleton_hungry()
	{ 
		cout << "Destruct！\n";
		delete pInstance;
		pInstance = nullptr;
	}
	static Singleton_hungry* pInstance;

public:
	static Singleton_hungry* GetInstance() {
		return pInstance;
	}
};

Singleton_hungry* Singleton_hungry::pInstance = new Singleton_hungry;


void test1()
{	
}
int main() 
{
	{	
		Singleton_lazy* s1 = Singleton_lazy::GetInstance();	
		Singleton_lazy* s2 = Singleton_lazy::GetInstance();
		if (s1 == s2)
		{
			cout << (void *)s1 << '\t' << (void *)s2 << '\t' << (s1 == s2) << "\n";
		}	
		Singleton_hungry* s3 = Singleton_hungry::GetInstance();	
		Singleton_hungry* s4 = Singleton_hungry::GetInstance();
		if (s3 == s4)
		{
			cout << (void *)s3 << '\t' << (void *)s4 << '\t' <<  (s3 == s4) << "\n";
		}
	}
	system("pause");
	return 0;
}
