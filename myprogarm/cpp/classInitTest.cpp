#include <iostream>

using namespace std;

//---------------------------------------
class CClassroom
{
    private:
           int grade;
           int roomNum;
    public:
           CClassroom();
           ~CClassroom();
}

CClassroom::CClassroom()
{
    cout<<"call CClassroom construction function"<<endl;  
}

CClassroom::~CClassroom()
{
}

//--------------------------------------
class CSchool
{
    public:
         
          int a;
          CSchool();
          ~CSchool();
    private:
          CClassroom classroom;
};

CSchool::CSchool()
{
    cout<<"call CSchool construction function"<<endl;
}

CSchool::~CSchool()
{
}

//----------------------------------------
class CStudent
{
    private:
           
           CSchool ToSchool;
           int num;
    public:
           CStudent();
           ~CStudent();
};

CStudent::CStudent()
{
    cout<<"call CStudent construction funcation"<<endl;
   // num = val;
   // cout<<"set the num as "<<val<<endl;
}

CStudent::~CStudent()
{
}

int main(void)
{
    CStudent st;
    //st.num = 3;
    return 0;
}

