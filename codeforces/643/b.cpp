#include <bits/stdc++.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define f first
#define s second
#define pb push_back

typedef long long ll;
typedef pair<int, int> ii;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

int main(){ _
	int t; cin >> t;
	while(t--){
		int n; cin >> n;
		vector<int> e(n);
		for (int i = 0; i < n; i++) cin >> e[i];
		sort(e.begin(), e.end());
		//reverse(e.begin(), e.end());
		int act = 0;
		int ans = 0;
		int li = -1;
		for (int i = 0; i < n; i++){
			act = max(act, e[i]);
			if (i - li == act){
				ans++;
				li = i;
			}
		}

		cout << ans << endl;
	}
	exit(0);
}
