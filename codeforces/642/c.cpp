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
		ll n; cin >> n;
		ll ans = 0;
		ll mv = n/2;
		while(n > 1){
			ans += ((n*n) - ((n-2) * (n-2))) * mv;
			mv--;
			n -= 2;
		}

		cout << ans << endl;
	}
	exit(0);
}
