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
int vp, vd, t, f, c;

bool solve(ll m){
	
}

int main(){ _
	cin >> vp >> vd >> t >> f >> c;
	ll l = 0, r = 1e4;
	while(l < r){
		ll m = (l+r)/2;
		if(solve(m)) r = m;
		else l = m+1;
	}
	exit(0);
}
