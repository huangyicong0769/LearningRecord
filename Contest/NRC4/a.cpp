#include <iostream>
#include <string>
using namespace std;

int main(){
  int t;
  cin.sync_with_stdio(false);
  cout.sync_with_stdio(false);
  cin >> t;
  while (t--){
    string s;
    cin >> s;
    bool allA = 1;
    for (register int i = 0; i < s.size(); i++)
      if (s[i] != 'a'){
        allA = 0;
        s.insert(s.size() - i, "a");
        cout << "YES\n" << s << endl;
        break;
      }
    if (allA) cout << "NO" << endl;
  }
}