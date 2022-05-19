#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i, j, n) for (int i = j; i < n; i++)
#define pi acos(-1.0)
ll n;
int main()
{
    ll t;
    cin >> t;
    while (t--)
    {
        ll a, b, c, s;
        cin >> a >> b >> c >> s;
        ll S = 0;
        if (a * b >= c)
        {
            S = (s - 1) * a;
            S += max(a, c);
        }
        else
        { //花费b个耐力走c
            if (s % b != 0)
            {
                S = s / b * c;

                s %= b; //剩下的小于b的耐力
                if (s == 0)
                    S += 0;

                else if (s == 1)
                    S += max(a, c);

                else if (s > 1)
                {
                    S += (s - 1) * a + max(a, c);
                }
            }
            else
            {

                S += (s / b) * c + (b - 1) * a;
            }
        }
        cout << S << endl;
    }
    return 0;
}