// #include <iostream>

// struct
// {
//     char a;
//     int b;
//     union
//     {
//         int c;
//         double d;
//     };
//     unsigned char *e;
// } A;

// int main()
// {
//     std::cout << sizeof(A);
//     return 0;
// }

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int sum(string str)
{
    for (int i = 0; i < str.size(); ++i)
    {
        if (str[i] < '0' || str[i] > '9')
        {
            str[i] = ' ';
        }
    }
    int num = 0;
    stringstream os;
    os << str;
    string s;
    while (os >> s)
    {
        // string s = os.str();
        num += std::stoi(s);
    }
    return num;
}

int main()
{
    cout << sum("87987654321-1=a3");
    return 0;
}