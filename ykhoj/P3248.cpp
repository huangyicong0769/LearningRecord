#include <iostream>
#include <stack>
#include <cstdio>
using namespace std;

struct Tuple
{
    char ch;
    int pos;
} Origin;

char s[500];
int pos, oprInPri[200], oprOutPri[200];
double nowNum, cnt;
bool point, numing;

stack<double> numSta;
stack<Tuple> oprSta;

inline void init();
inline void outNum();
inline void operation(const char &);
inline void numTesting();
inline void oprTesting();
inline bool isNum(const char &);
inline bool isLegal(const char &);

int main()
{
    init();
    for (char ch = getchar(); isLegal(ch); ch = getchar(), pos++)
    {
        s[pos] = ch;
        if (isNum(ch))
        {
            numing = 1;
            if (point)
            {
                nowNum += (ch - '0') / cnt;
                cnt *= 10;
            }
            else
            {
                (nowNum *= 10) += ch - '0';
            }
        }
        else if (ch == '.')
        {
            point = 1;
        }
        else
        {
            if (numing)
                outNum();
            operation(ch);
        }
    }
    operation(')');
    //numTesting();
    //oprTesting();
    printf("%.2lf\n", numSta.top());
    return 0;
}

inline void init()
{
    pos=1;
    nowNum = point = numing = 0;
    cnt = 10;
    oprInPri['+'] = oprInPri['-'] = oprOutPri['+'] = oprOutPri['-'] = 1;
    oprInPri['*'] = oprInPri['/'] = oprOutPri['*'] = oprOutPri['/'] = 2;
    oprInPri['('] = 3;
    oprOutPri['('] = -1;
    oprInPri[')'] = oprOutPri[')'] = -1;
    oprSta.push((Tuple){'(', 0});
    s[0]='(';
}

inline bool isNum(const char &ch)
{
    if ('0' <= ch && ch <= '9')
        return true;
    else
        return false;
}

inline bool isLegal(const char &ch)
{
    if (isNum(ch))
        return true;
    if (oprOutPri[ch] != 0)
        return true;
    if (ch == '.')
        return true;
    return false;
}

inline void outNum()
{
    numSta.push(nowNum);
    nowNum = point = numing = 0;
    cnt = 10;
}

inline void operation(const char &ch)
{
    //cout << pos << ' ' << ch << endl;
    while (oprSta.size() && oprOutPri[oprSta.top().ch] >= oprInPri[ch])
    {
        Tuple t = oprSta.top();
        oprSta.pop();
        //cout << "  " << t.ch << ' ' << oprOutPri[t.ch] << oprInPri[ch] << endl;
        if (ch == ')' && t.ch == '(')
            break;
        if (t.ch == '+')
        {
            double t1, t2;
            t1 = numSta.top();
            numSta.pop();
            t2 = numSta.top();
            numSta.pop();
            numSta.push(t1 + t2);
        }
        else if (t.ch == '-')
        {
            if (!isNum(s[t.pos-1]))
            {
                double t1 = numSta.top();
                numSta.pop();
                numSta.push(-1 * t1);
            }
            else
            {
                double t1, t2;
                t1 = numSta.top();
                numSta.pop();
                t2 = numSta.top();
                numSta.pop();
                numSta.push(t2 - t1);
            }
        }
        else if (t.ch == '*')
        {
            double t1, t2;
            t1 = numSta.top();
            numSta.pop();
            t2 = numSta.top();
            numSta.pop();
            numSta.push(t1 * t2);
        }
        else if (t.ch == '/')
        {
            double t1, t2;
            t1 = numSta.top();
            numSta.pop();
            t2 = numSta.top();
            numSta.pop();
            numSta.push(t2 / t1);
        }
    }
    if (ch!=')') oprSta.push((Tuple){ch, pos});
}

inline void numTesting()
{
    cout<<"================\n";
    while (numSta.size())
    {
        cout << numSta.top() << endl;
        numSta.pop();
    }
}