template<typename T>   

class CSingleton
{
public:
static T& Instance()
    {
	static T me;
	return me;
    }
};  

class MyClass: public CSingleton<MyClass>
{
public:
	MyClass(){};
	~MyClass(){};
	void Print() { printf("testing %d\n",val); }
	int val;
};  

int main(void)
{
   MyClass::Instance().val=7;
   MyClass::Instance().Print();   

   return 0;
} 


----------------------------------------------------------------------------------

class CSingleton  
{  
private:  
    CSingleton()   //????????  
    {  
    }  
    static CSingleton *m_pInstance;  
public:  
    static CSingleton * GetInstance()  
    {  
        if(m_pInstance == NULL)  //?????????  
            m_pInstance = new CSingleton();  
        return m_pInstance;  
    }  
};



-----------------------------------------------------------------------------------
class CSingleton  
{  
private:  
    CSingleton()   //????????  
    {  
    }  
    CSingleton(const CSingleton &);  
    CSingleton & operator = (const CSingleton &);  
public:  
    static CSingleton & GetInstance()  
    {  
        static CSingleton instance;   //??????  
        return instance;  
    }  
};