#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=2e4+5;

int n,k;
int a[MAXN];

const ull base=1331;

ull Hash[MAXN];
ull basep[MAXN];
unordered_map<ull,int> M;

inline ull getHash(reg int l,reg int r){
	return Hash[r]-Hash[l-1]*basep[r-l+1];
}

inline bool check(reg int mid){
	M.clear();
	int Max=0;
	for(reg int i=1;i+mid-1<=n;++i)
		Max=max(Max,++M[getHash(i,i+mid-1)]);
	return Max>=k;
}

int main(void){
	n=read(),k=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	basep[0]=1;
	for(reg int i=1;i<=n;++i){
		basep[i]=basep[i-1]*base;
		Hash[i]=Hash[i-1]*base+a[i]+1;
	}
	reg int l=1,r=n,mid;
	while(l<r){
		mid=(l+r)>>1;
		if(check(mid+1))
			l=mid+1;
		else
			r=mid;
	}
	printf("%d\n",l);
	return 0;
}