#include "BigInt.h"
#include <string>
#include <sstream>
using namespace std;
BigInt::BigInt()
{
    Num = "0";
}

BigInt::BigInt(string n)
{
    Num = n;
}

BigInt::~BigInt()
{
    //dtor
}

BigInt::BigInt(const BigInt& other)
{
    Num = other.Num;
}

BigInt& BigInt::operator=(const BigInt& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    Num = rhs.Num;
    return *this;
}
BigInt& BigInt::operator+(const BigInt& rhs)
{
    BigInt temp;
    temp.Num = operatorCoordinator(Num,rhs.Num,"+");
    return temp;
}
BigInt& BigInt::operator-(const BigInt& rhs)
{
    BigInt temp;
    temp.Num = operatorCoordinator(Num,rhs.Num,"-");
    return temp;
}
BigInt& BigInt::operator*(const BigInt& rhs)
{
    BigInt temp;
    temp.Num = operatorCoordinator(Num,rhs.Num,"*");
    return temp;
}
BigInt& BigInt::operator/(const BigInt& rhs)
{
    BigInt temp;
    temp.Num = operatorCoordinator(Num,rhs.Num,"/");
    return temp;
}
BigInt& BigInt::operator%(const BigInt& rhs)
{
    BigInt temp;
    temp.Num = operatorCoordinator(Num,rhs.Num,"%");
    return temp;
}
BigInt& BigInt::operator+=(const BigInt& rhs)
{
    Num = operatorCoordinator(Num,rhs.Num,"+=");
    return *this;
}
BigInt& BigInt::operator-=(const BigInt& rhs)
{
    Num = operatorCoordinator(Num,rhs.Num,"-=");
    return *this;
}
BigInt& BigInt::operator*=(const BigInt& rhs)
{
    Num = operatorCoordinator(Num,rhs.Num,"*=");
    return *this;
}
BigInt& BigInt::operator/=(const BigInt& rhs)
{
    Num = operatorCoordinator(Num,rhs.Num,"/=");
    return *this;
}
BigInt& BigInt::operator%=(const BigInt& rhs)
{
    Num = operatorCoordinator(Num,rhs.Num,"%=");
    return *this;
}
BigInt BigInt::operator++(int x)
{
    Num = operatorCoordinator(Num,"1","+");
    return *this;
}
BigInt BigInt::operator--(int x)
{
    Num = operatorCoordinator(Num,"1","-");
    return *this;
}
BigInt& BigInt::operator++()
{
    Num = operatorCoordinator(Num,"1","+");
    return *this;
}
BigInt& BigInt::operator--()
{
    Num = operatorCoordinator(Num,"1","-");
    return *this;
}
inline string BigInt:: toStr(long long int x)
{
    string h;
    stringstream kk;
    kk<<x;
    kk>>h;
    return h;
}
inline long long int BigInt::toLong(string x)
{
    long long int h;
    stringstream kk;
    kk<<x;
    kk>>h;
    return h;
}
string BigInt::sum (string a1, string a2 = "1")
{
    string sum,temp;
    char re = '0';
    unsigned int len = ( a1.size() >= a2.size() ? a1.size() : a2.size());
    while (len % 18)
        len++;
    while (a2.size() != len)
        a2 = '0' + a2;
    while (a1.size() != len)
        a1 = '0' + a1;
    for (int i = ( len / 18 ) ; i >= 1  ; i--)
    {
        temp = toStr( toLong(a1.substr(i*18-18,18)) + toLong(a2.substr(i*18-18,18)) + ( re - 48 ) ) ;
        re = '0' ;
        if (temp.size() == 19 && i != 1)
        {
            sum = temp.substr(1,temp.size()-1) + sum ;
            re = '1';
        }
        else
            sum = temp + sum ;
    }
    return sum;
}
string BigInt::complement10s (string num)
{
    for (int i=0; i<num.size(); i++)
        num[i] = ('9' - num[i]) + 48;
    num = sum(num);
    return num;
}
string BigInt::subtraction (string a1,string a2 = "1")
{
    a1 = ZeroRemover(a1);
    a2 = ZeroRemover(a2);
    if (Equal(a2,"0"))
        return a1;
    else if (Equal(a1,"0"))
        return '-' + a2;
    string res , a210 = complement10s(a2);
    res = sum(a1,a210);
    if (Compa(a2,a1))
    {
        res = complement10s(res);
        res = '-' + res;
    }
    else
    {
        for ( int i = res.size() - (a210.size()+1) ; i>=0 ; i--)
        {
            res[i]--;
            if (sum(res,a2) == a1)
                break;
            else
                res[i]++;
        }
    }
    return ZeroRemover(res) ;
}
/** compare greather than which (a1 > a2) this true*/
bool BigInt::Compa (string a1,string a2)
{
    if (a1==a2)
        return false;
    else if (a1.size()>a2.size())
        return true;
    else if (a1.size() == a2.size())
    {
        for (int i = 0 ; i < a1.size() ; i++)
            if (a1[i] < a2[i])
                return false;
            else if (a1[i] > a2[i])
                return true;
    }
    else if (a1.size()<a2.size())
        return false;
}
string BigInt::multiplay (string a1, string a2)
{
    string res , tempRes ;
    int numOfZero;
    for (int i = a2.length()-1 ; i>=0 ; i-- )
    {
        tempRes = "0";
        for (int j = '0' ; j < a2[i] ; j++)
            tempRes = sum(tempRes,a1);
        numOfZero = a2.size() -i -1;
        if (a2[i] != '0')
            for(int j = 0 ; j < numOfZero ; j++)
                tempRes += '0';
        res = sum(res,tempRes);
    }
    return res;
}
string BigInt::reminder (string a1, string a2)
{
    if (a2=="0")
        return "Error";
    else if (a1== "0")
        return "0";
    return subtraction(a1,multiplay(a2,division(a1,a2)));
}
bool BigInt::Equal (string a1, string a2)
{
    if (a1==a2)
        return true;
    else
        return false;
}
string BigInt::tempDivision (string a1, string a2)
{
    a1 = ZeroRemover(a1);
    a2 = ZeroRemover(a2);

    string res = "1";
    while (Compa(a1,multiplay(res,a2)))
    {

        res = sum(res);
        // cout<<"**"<<res<<' '<<a1<<' '<<multiplay(res,a2)<<' '<<Compa(a1,multiplay(res,a2))<<endl;
    }
    // subtraction(res);
    return ( Equal(a1,multiplay(res,a2)) ? res : subtraction(res) );
}
string BigInt::division (string a1, string a2)
{
    string Result ,tempRes, temp;
    if(Compa(a2,a1))
        return "0";
    else if (Equal(a1,a2))
        return "1";
    for (int i = 0 ;i <a1.size() ; i++)
    {
        temp += a1[i];
        tempRes = tempDivision(temp,a2);
        Result += tempRes ;
        temp = subtraction(temp,multiplay(tempRes,a2));
    }

    return ZeroRemover(Result);
}
string BigInt::ZeroRemover (string num)
{
    string ans;
    for (int i = 0 , o = 0; i < (num.size()%18 ? num.size()/18 + 1 : num.size() / 18) ; i++ , o += 18)
        ans += toStr(toLong(num.substr(o,18)));
    return ans;
}
string BigInt::operatorCoordinator(string a1, string a2 , string op)
{
    a1 = ZeroRemover(a1);
    a2 = ZeroRemover(a2);
    if (op == "+")
    {
        if (a1[0]>='0'&&a2[0]>='0')
            return sum(a1,a2);
        else if (a1[0]>='0'&&a2[0]=='-')
            return subtraction(a1,a2.substr(1,a2.size()-1));
        else if (a1[0]=='-'&&a2[0]>='0')
            return subtraction(a2,a1.substr(1,a1.size()-1));
        else
            return '-' + sum(a1.substr(1,a1.size()-1),a2.substr(1,a2.size()-1));
    }
    else if (op == "-")
    {
        if (a1[0]>='0'&&a2[0]>='0')
            return subtraction(a1,a2);
        else if (a1[0]>='0'&&a2[0]=='-')
            return sum(a1,a2.substr(1,a2.size()-1));
        else if (a1[0]=='-'&&a2[0]>='0')
            return '-' + sum(a2,a1.substr(1,a1.size()-1));
        else
            return subtraction(a2.substr(1,a2.size()-1),a1.substr(1,a1.size()-1));
    }
    else if (op == "*")
    {
        if (a1[0]>='0'&&a2[0]>='0')
            return multiplay(a1,a2);
        else if (a1[0]>='0'&&a2[0]=='-')
            return '-' + multiplay(a1,a2.substr(1,a2.size()-1));
        else if (a1[0]=='-'&&a2[0]>='0')
            return '-' + multiplay(a2,a1.substr(1,a1.size()-1));
        else
            return multiplay(a2.substr(1,a2.size()-1),a1.substr(1,a1.size()-1));
    }
    else if (op == "/")
    {
        if (a1[0]>='0'&&a2[0]>='0')
            return division(a1,a2);
        else if (a1[0]>='0'&&a2[0]=='-')
            return '-' + division(a1,a2.substr(1,a2.size()-1));
        else if (a1[0]=='-'&&a2[0]>='0')
            return '-' + division(a1.substr(1,a1.size()-1),a2);
        else
            return division(a1.substr(1,a1.size()-1),a2.substr(1,a2.size()-1));
    }
    else if (op == "%")
    {
        if (a1[0]>='0'&&a2[0]>='0')
            return reminder(a1,a2);
        else if (a1[0]>='0'&&a2[0]=='-')
            return reminder(a1,a2.substr(1,a2.size()-1));
        else if (a1[0]=='-'&&a2[0]>='0')
            return '-' + reminder(a1.substr(1,a1.size()-1),a2);
        else
            return '-' + reminder(a1.substr(1,a1.size()-1),a2.substr(1,a2.size()-1));
    }
    else if (op == "+=")
        return operatorCoordinator(a1,a2,"+");
    else if (op == "-=")
        return operatorCoordinator(a1,a2,"-");
    else if (op == "*=")
        return operatorCoordinator(a1,a2,"*");
    else if (op == "/=")
        return operatorCoordinator(a1,a2,"/");
    else if (op == "%=")
        return operatorCoordinator(a1,a2,"%");
    else if (op == "++")
        return operatorCoordinator(a1,a2,"+");
    else if (op == "--")
        return operatorCoordinator(a1,a2,"-");

}


