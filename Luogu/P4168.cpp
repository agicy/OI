#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=4e4+5;
const int MAXCNT=35+5;

int n,m;
int a[MAXN];
int B,pos[MAXN];
int cnt[MAXCNT][MAXCNT][MAXN],Ans[MAXCNT][MAXCNT];

inline void update(reg int i,reg int j,reg int T[],reg int &ans){
	reg int L=B*(i-1)+1,R=min(n,B*j);
	for(reg int i=L;i<=R;++i){
		++T[a[i]];
		if(T[ans]<T[a[i]]||(T[ans]==T[a[i]]&&a[i]<ans))
			ans=a[i];
	}
	return;
}

inline int Solve(reg int l,reg int r){
	if(pos[r]-pos[l]<=1){
		static int T[MAXN];
		for(reg int i=l;i<=r;++i)
			T[a[i]]=0;
		reg int res=0;
		for(reg int i=l;i<=r;++i){
			++T[a[i]];
			if(T[a[i]]>T[res])
				res=a[i];
			else if(T[a[i]]==T[res]&&a[i]<res)
				res=a[i];
		}
		return res;
	}
	reg int L=pos[l]+1,R=pos[r]-1;
	reg int res=Ans[L][R];
	for(reg int i=l;pos[i]==pos[l];++i){
		++cnt[L][R][a[i]];
		if(cnt[L][R][a[i]]>cnt[L][R][res]||(cnt[L][R][a[i]]==cnt[L][R][res]&&a[i]<res))
			res=a[i];
	}
	for(reg int i=r;pos[i]==pos[r];--i){
		++cnt[L][R][a[i]];
		if(cnt[L][R][a[i]]>cnt[L][R][res]||(cnt[L][R][a[i]]==cnt[L][R][res]&&a[i]<res))
			res=a[i];
	}
	for(reg int i=l;pos[i]==pos[l];++i)
		--cnt[L][R][a[i]];
	for(reg int i=r;pos[i]==pos[r];--i)
		--cnt[L][R][a[i]];
	return res;
}

vector<int> V;

int main(void){
	scanf("%d%d",&n,&m);
	B=pow(n,2.0/3.0);
	for(reg int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		V.push_back(a[i]);
		pos[i]=(i-1)/B+1;
	}
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	for(reg int i=1;i<=n;++i)
		a[i]=lower_bound(V.begin(),V.end(),a[i])-V.begin()+1;
	for(reg int i=1;i<=pos[n];++i)
		for(reg int j=i;j<=pos[n];++j)
			update(i,j,cnt[i][j],Ans[i][j]);
	reg int lastans=0;
	while(m--){
		static int l,r;
		scanf("%d%d",&l,&r);
		l=(l+lastans-1)%n+1,r=(r+lastans-1)%n+1;
		if(l>r)
			swap(l,r);
		lastans=V[Solve(l,r)-1];
		printf("%d\n",lastans);
	}
	return 0;
}