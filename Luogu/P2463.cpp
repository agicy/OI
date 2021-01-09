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

const int MAXN=1e3+5;
const int MAXM=101+5;
const ull base=1331;

int n;
int m[MAXN];
int a[MAXN][MAXM];
ull basep[MAXM];
ull Hash[MAXN][MAXM];
unordered_map<ull,int> M;
ull S[MAXM];

inline ull getHash(reg int id,reg int l,reg int r){
	return Hash[id][r]-Hash[id][l-1]*basep[r-l+1];
}

inline bool check(reg int mid){
	if(mid==1)
		return n>=2;
	M.clear();
	for(reg int i=1;i<=n;++i)
		if(mid<=m[i]){
			reg int top=0;
			for(reg int j=1;j+mid-2<m[i];++j)
				S[++top]=getHash(i,j,j+mid-2);
			sort(S+1,S+top+1);
			top=unique(S+1,S+top+1)-(S+1);
			for(reg int j=1;j<=top;++j)
				if((++M[S[j]])==n)
					return true;
		}
	return false;
}

int main(void){
	n=read();
	int Max=0;
	for(reg int i=1;i<=n;++i){
		m[i]=read();
		Max=max(Max,m[i]);
		for(reg int j=0,las,x;j<m[i];++j){
			x=read();
			if(j)
				a[i][j]=x-las;
			las=x;
		}
	}
	basep[0]=1;
	for(reg int i=1;i<Max;++i)
		basep[i]=basep[i-1]*base;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<m[i];++j)
			Hash[i][j]=Hash[i][j-1]*base+a[i][j];
	reg int l=1,r=Max,mid;
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