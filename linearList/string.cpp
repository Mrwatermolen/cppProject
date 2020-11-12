#include <iostream>
#include <cstring>
#define MaxSize 255
using namespace std;

struct MyStr
{
    char str[MaxSize];
    int Length;
};

int main()
{
    void MyStrAssign(MyStr & S, const char *s);
    int Index(const MyStr &T1, const MyStr &T2);
    int IndexKMP(MyStr T1, MyStr T2, int method = 1);

    MyStr mainString = {{0}, 0};
    MyStr T = {{0}, 0};
    char s[MaxSize - 1];
    char ss[MaxSize - 1];
    cin.getline(s, MaxSize - 1);
    cin.getline(ss, MaxSize - 1);
    MyStrAssign(mainString, s);
    MyStrAssign(T, ss);

    cout << "Index Match:  " << Index(mainString, T) << endl;
    cout << "IndexKPM Next Match:  " << IndexKMP(mainString, T, 0) << endl;
    cout << "IndexKPM nextval Match:  " << IndexKMP(mainString, T) << endl;
    return 0;
}

void MyStrAssign(MyStr &S, const char *s)
{
    S.str[0] = strlen(s);
    S.Length = S.str[0];
    for (int i = 1; i <= S.Length; i++)
    {
        S.str[i] = s[i - 1];
    }
}

int Index(const MyStr &T1, const MyStr &T2)
{
    if (T1.Length < T2.Length || T1.Length == 0)
        return 0;
    int i = 1, j = 1, k = 1;
    while (i <= T1.Length && j <= T2.Length)
    {
        if (T1.str[i] == T2.str[j])
        {
            ++i;
            ++j;
        }
        else
        {
            ++k;
            i = k;
            j = 1;
        }
    }
    if (j > T2.Length)
        return k;
    else
        return 0;
}

int IndexKMP(MyStr T1, MyStr T2, int method)
{
    int *GetNextArray(const MyStr &T);
    int *GetnextvalArarry(const MyStr &T);

    int i = 1, j = 1;
    int *next;
    if (method)
    {
        next = GetnextvalArarry(T2);
    }
    else
    {
        next = GetNextArray(T2);
    }

    while (i <= T1.Length && j <= T2.Length)
    {
        if (j == 0 || T1.str[i] == T2.str[j])
        {
            ++i;
            ++j;
        }
        else
        {
            j = next[j];
        }
    }
    //delete [] next;
    if (j > T2.Length)
        return i - T2.Length;
    return 0;
}

int *GetNextArray(const MyStr &T)
{
    int *next = new int[(T.Length + 1)]; //next[0] isn't used.
    //next[1] = 0;
    //next[2] = 1;

    int i = 1, j = 0;

    while (i < T.Length)
    {
        if (j == 0 || T.str[i] == T.str[j])
        {
            ++i;
            ++j;
            next[i] = j;
        }
        else
        {
            j = next[j];
        }
    }

    return next;
}

int *GetnextvalArarry(const MyStr &T)
{
    int *GetNextArray(const MyStr &T);

    int *next = GetNextArray(T);
    int *nextval = new int[(T.Length + 1)];
    int j = 1;
    nextval[1] = 1;
    while (j <= T.Length)
    {
        if (T.str[next[j]] == T.str[j])
        {
            nextval[j] = next[nextval[j]];
        }
        else
        {
            nextval[j] = next[j];
        }
        ++j;
    }
    //delete []next;
    return nextval;
}
