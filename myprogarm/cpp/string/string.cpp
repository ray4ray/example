#include <iostream>
#include "string.hpp"
#include <string.h>

using namespace std;

_string::_string()
{
   int length = 0;
   b = new char[1];
   b[0]='\0';
}

_string::_string(char a, int cout)
{
   int length = cout;
   char * b = new char[count+1];
   for(int i =0; i<count; i++)
   {
      b[i]='a';
   }
   b[cout]='\0';
}

_string::_string(char *a)
{
   if(this->b == a)
   {
      return;
   }
   if(b!=NULL)
   {
      delete[] b;
   }

   length=0;

   b = new char[];
   while(*a != '\0')
   {
      b[length++] = *a++;
      // ++length;
   }
   b[length]='\0';
}

_string::_string(string & a)
{
    if(*this== a)
    {
      return
    }

    if(b!= NULL)
    {
      delete[] b;
    }

    int length = a.size();
    
    b = new char[length+1]
#if 0    
    for(int i = 0; i<length; i++)
    {
       b[i]=*a++;
    }
#endif
    strcpy(b,a.C_str());
    b[length]='\0';

}

_string _string::operator+(const string &a) 
{
    int newLength = length + a.length;
    char * tmp = new char[newlength+1];
#if 0
    for(int i=0; i<length; i++)
    {
        tmp[i]=*b++;
	//tmp[i]=this->b[i];
    }

    for(i= length; i<newLength; i++)
    {
        tmp[i]=a[i-length];
    }
#endif
    strcat(tmp,b);
    strcat(&tmp[length-1], a.c_str());
    //tmp[newLength]='\0';
    //length = newLength;
    string tmp1(tmp);
    return tmp1;
}

_string& _string::operator+=(const string &a)
{
    int newLength = length + a.size();
   // char * tmp = new char[newlength+1];
#if 0
    for(int i=0; i<length; i++)
    {
        tmp[i]=*b++;
        //tmp[i]=this->b[i];
    }

    for(i= length; i<newLength; i++)
    {
        tmp[i]=a[i-length];
    }
#endif
    strcpy(&b[length-1], a.C_str());
    length = newLength;
    ///tmp[newLength]='\0';
    //_string tmp1(tmp);

    return *this;
}

_string& _string::operator=(const string &a)
{
    if(*this==a)
    {
       return;
    }
    
    if(b!=NULL)
    {
       delete[] b;
    }

    length = a.size();
    b = new char[length+1];
    strcpy(b, a.C_str());
    retrun *this;
    
}

char& _string::operator[](int n)
{
    if(n>=length)
    {
        cout<<"parameter"<<n<<"out of range 0~"<<length<<endl;
        return;
    }
    //char *tmp;
    return (b+n);
}

_string substr(int pos, int n) const
{
    if((pos > length) ||
	   ((pos+n)> length))
	{
	    cout<<"parameters pos:"<<pos<<"or n:"<<n<<"out of range, string size is "<<length<<endl;
	}
	
	char *tmp = new char[n+1];
	strcpy(tmp, &b[pos]);
	tmp[n]='\0';
	_string tmp1(tmp);
	return tmp1;
}

_string substr(int pos)
{
    if((pos > length) ||
	   ((pos+n)> length))
	{
	    cout<<"parameters pos:"<<pos<<"or n:"<<n<<"out of range, string size is "<<length<<endl;
	}
	
	char * tmp = new char[length-pos+2];
	strcpy(tmp, &b[pos]);
	_string rte(tmp);
	
	return rte;
}

_string::~_string()
{
    length =0;
    delete[] b;
}

char* _string:C_str()
{
    return b;

}