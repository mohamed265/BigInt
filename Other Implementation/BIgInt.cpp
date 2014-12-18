#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <vector>
#include <time.h>
using namespace std;
//7 for int
//18 for long long int
string sum (string a1, string a2);
inline string toStr(long long int x);
inline long long int toLong(string x);
string subtraction (string a1,string a2);
bool Compa (string a1,string a2);
string multiplay (string a1, string a2);
bool Equal (string a1, string a2);
string reminder (string a1, string a2);
string tempDivision (string a1, string a2);
string division (string a1, string a2);
string ZeroRemover (string  num);
string reminder (string a1, string a2);
inline string toStr(long long int x)
{
    string h;
    stringstream kk;
    kk<<x;
    kk>>h;
    return h;
}
inline long long int toLong(string x)
{
    long long int h;
    stringstream kk;
    kk<<x;
    kk>>h;
    return h;
}
int main()
{
   string a1="47863784364786347364437463666666666666666666667888888888888837436487348376434624732463746346346374637464372388888888888888888888888888888888888888888888747377737373773737739723872893238273823928382372989372888888888888888888999999999999933333333333333000000000000033823723727863987273273268"
     ,a2="83746347634783647364736473643743743473747434646466464643848348384388746734736473434736734377777777434343747473477377347777777777777777777343473743737473636646343837637463894343637374663746374673467346374634343434",sum,temp;
	cout<<sum(a1,a2)<<endl << subtraction(a1,a2)<<endl<<multiplay(a1,a2)<<endl<<reminder(a1,a2)<<endl<<division(a1,a2);
	
    return 0;
}
string sum (string a1, string a2 = "1")
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
    //cout<<sum<<endl;
    return sum;
}
string complement10s (string num)
{
    for (int i=0; i<num.size(); i++)
        num[i] = ('9' - num[i]) + 48;
    num = sum(num);
    return num;
}
// test comp 30 < 15
string subtraction (string a1,string a2 = "1")
{
    a1 = ZeroRemover(a1);
    a2 = ZeroRemover(a2);
    if (Equal(a2,"0"))
        return a1;
    else if (Equal(a1,"0"))
        return '-' + a2;
    string res , a210 = complement10s(a2);

    //cout<<a210<<endl;
    res = sum(a1,a210);
    //  cout<<res<<endl;
    if (Compa(a2,a1))
    {
        res = complement10s(res);
        res = '-' + res;
    }
    else
        //   res[res.size()-(a210.size()+1)]--;
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
bool Compa (string a1,string a2)
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
string multiplay (string a1, string a2)
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
string reminder (string a1, string a2)
{
    if (a2=="0")
        return "Error";
    else if (a1== "0")
        return "0";
    return subtraction(a1,multiplay(a2,division(a1,a2)));
}
bool Equal (string a1, string a2)
{
    if (a1==a2)
        return true;
    else
        return false;
}
string tempDivision (string a1, string a2)
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
string division (string a1, string a2)
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
        //cout<<"*"<<Result<<"\ttempRes\t"<<tempRes<<" temp\t"<<temp<<endl;
        temp = subtraction(temp,multiplay(tempRes,a2));
        //cout<<Result<<"\ttempRes\t"<<tempRes<<" temp\t"<<temp<<endl;
    //    system("pause");
    }

    return ZeroRemover(Result);
}
string ZeroRemover (string num)
{

    string ans;
    int o = 0 ;
   // try
   //  {
        for (int i = 0 ; i < (num.size()%18 ? num.size()/18 + 1 : num.size() / 18) ; i++ , o += 18)
            ans += toStr(toLong(num.substr(o,18)));
//     }
//     catch
//     {
//         ans += toStr(toLong(num.substr(o,num.size()-o)));
//     }

    return ans;
}
