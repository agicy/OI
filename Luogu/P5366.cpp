#include<bits/stdc++.h>
using namespace std;
#define reg register

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1e5 + 5;
const int P=1e9 + 7;
const int inf=0x3f3f3f3f;

int n, G, L, Q, x, pow2[MAXN], U, l[MAXN], r[MAXN], siz[MAXN], N, ans[1 << 17];
vector<pair<int, int> > facL, data;


inline int add(int x, int y) { x += y; return x >= P ? x - P : x; }
inline int dec(int x, int y) { x -= y; return x < 0 ? x + P : x; }

inline void GetFac(reg int x,vector<pair<int,int>/**/> &fac){
	for(reg int i=2;i*i<=x;++i)
		if(x%i==0){
			reg int cnt=0;
			while(x%i==0){
				++cnt;
				x/=i;
			}
		fac.push_back(make_pair(i, cnt));
	}
	if(x!=1)
		fac.push_back(mp(x, 1));
	return;
}

inline pair<int, int> GetState(int x) {
	int S=0, y=x;
	rep(i, 0, SIZE(facL) - 1) {
		int cnt=0;
		while(x % facL[i].first == 0) x /= facL[i].first, cnt++;
		S |= (cnt == l[i]) << i;
		S |= (cnt == r[i]) << i + SIZE(facL);
	}
	return mp(y, S);
}

inline void PreSolve(void){
	GetFac(L,facL);
	pow2[0]=1;
	reg int size=facL.size();
	N=(size<<1);
	U=(1<<N)-1;
	for(reg int i=1;i<=U;++i)
		pow2[i]=add(pow2[i-1],pow2[i-1]);
	for(reg int i=0,)
	rep(i, 0, SIZE(facL) - 1) {
		r[i]=facL[i].second;
		int x=G;
		while(x % facL[i].first == 0) l[i]++, x /= facL[i].first;
	}
	for(int i=1; 1ll * i * i <= L; i++) if(L % i == 0) {
		if(i % G == 0 && i <= n) data.pb(GetState(i));
		if(i * i != L && (L / i) % G == 0 && (L / i) <= n) data.pb(GetState(L / i));
	}
	sort(data.begin(), data.end());
	for(auto v : data) siz[v.second]++;
	rep(i, 0, N - 1) rep(S, 0, U) if(S >> i & 1) siz[S] += siz[S ^ (1 << i)];
}

inline int Solve(int x, int rnt=0) {
	auto it=*lower_bound(data.begin(), data.end(), mp(x, 0));
	if(ans[it.second] != -1) return ans[it.second];
	int T=it.second, S=U ^ T; rnt=__builtin_popcount(T) & 1 ? dec(rnt, pow2[siz[T] - 1]) : pow2[siz[T] - 1];
	for(int S1=S; S1; S1=(S1 - 1) & S)
		if(__builtin_popcount(S1 | T) & 1) rnt=dec(rnt, pow2[siz[S1 | T] - 1]);
		else rnt=add(rnt, pow2[siz[S1 | T] - 1]);
	return ans[it.second]=rnt;
}

int main(void){
	n=read(),G=read(),L=read(),Q=read();
	if(L%G){
		while(Q--)
			puts("0");
		return 0;
	}
	PreSolve();
	memset(ans,-1,sizeof(ans));
	while(Q--){
		reg int x=read();
		if(x%G!=0||L%x!=0||x>n)
			puts("0");
		else
			printf("%d\n",Solve(x));
	}
	return 0;
}