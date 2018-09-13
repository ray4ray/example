//#include <iostream>

class _string
{

public: 
   _string();
   _string(char *a);
   _string(char *a, int n);
   _string(string & a);
   ~_string();
   int size()const{return length;}
   _string operator+(const _string &a) const;
   _string operator+=(const _string &a);
   _string operator=(const _string &a);
   char & operator[](int a) const;
   _string substr(int pos, int n) const;
   _string substr(int pos) const;
   char* C_str() const;
prative:
   char *b;
   int length;

};


