/////////////////////////////////////////////////////
#ifdef _DEBUG
#include "bits_stdc++.h"
#else
#include "bits/stdc++.h"
#endif
using namespace std;
typedef pair<int, int> pii;
typedef vector<vector<pii > > Edge;
typedef unsigned long long llu;
typedef long long ll;
typedef priority_queue<pii > Pq;
typedef vector<int>::iterator It;
#define INF 0x3f3f3f3f
#define UINF 0xffffffffu
#define LINF 0x3f3f3f3f3f3f3f3fll
#define MOD 1000000007
#define EOD 1e-9
#define all(x) x.begin(),x.end()
const double PI = acos(0.0)*2.0;
/////////////////////////////////////////////////////
int main() {
	while (true) {
		string str;
		getline(cin, str);
		if (str == "#")
			break;
		for (int i = 0; i < str.size(); i++)
			if (str[i] >= 'A'&&str[i] <= 'Z')
				str[i] = str[i] - 'A' + 'a';
		bool alpa[26] = { 0, };
		for (int i = 0; i < str.size(); i++)
			if (str[i] >= 'a'&&str[i] <= 'z')
				alpa[str[i] - 'a'] = true;
		int ans = 0;
		for (int i = 0; i < 26; i++)
			if (alpa[i])
				ans++;
		printf("%d\n", ans);
	}
	return 0;
}