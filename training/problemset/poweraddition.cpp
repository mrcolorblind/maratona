//JP - Not in Kansas Anymore
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
	int tt; cin >> tt;
	while(tt--){
		int n; cin >> n;
		ll a, b; cin >> a; n--;
		ll d = 0;
		while(n--){
			cin >> b;
			a = max(a,b);
			d = max(d, (a-b));
		}
		int ans = 0;
		while(d > 0){ d >>= 1; ans++;}
		cout << ans << endl;
	}
	exit(0);
}
