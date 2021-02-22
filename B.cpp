#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXT=1e3+5;
const int MAXM=600+5;

int T,m[MAXT];
ll L[MAXT];
vector<bool> a[MAXT];
int Maxm=0;
ll MaxL=0;

namespace Subtask1{
	const int MAXL=1e6+5;
	const int MAXM=600+5;
	int b[MAXL+MAXM];
	int kmp[MAXL+MAXM];
	int x[MAXM];
	inline void Solve(void){
		b[0]=0;
		for(reg int i=1;i<=MaxL+Maxm-1;++i)
			if(i&1)
				b[i]=1-b[i>>1];
			else
				b[i]=b[i>>1];
		for(reg int t=1;t<=T;++t){
			for(reg int i=0;i<m[t];++i)
				x[i+1]=a[t][i];
			for(reg int i=2,j=0;i<=m[t];++i){
				while(j&&x[i]!=x[j+1])
					j=kmp[j];
				if(x[j+1]==x[i])
					++j;
				kmp[i]=j;
			}
			reg int cnt=0;
			for(reg int i=0,j=0;i<=m[t]+L[t]-1;++i){
				while(j>0&&x[j+1]!=b[i])
					j=kmp[j];
				if(x[j+1]==b[i])
					++j;
				if(j==m[t]){
					++cnt;
					j=kmp[j];
				}
			}
			printf("%d\n",cnt);
		}
		return;
	}
}

namespace Subtask2{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	inline int getCnt(reg int x){
		reg int res=0;
		while(x){
			++res;
			x^=lowbit(x);
		}
		return res;
	}
	inline bool check(reg int x,reg int t){
		for(reg int i=0;i<m[t];++i)
			if((getCnt(x+i)&1)!=a[t][i])
				return false;
		return true;
	}
	inline void Solve(void){
		for(reg int t=1;t<=T;++t){
			reg int ans=0;
			for(reg int i=0;i<=L[t];++i)
				if(check(i,t)){
					++ans;
					//i+=1;
				}
			printf("%d\n",ans);
		}
		return;
	}
}

int main(void){
	T=read();
	for(reg int i=1;i<=T;++i){
		m[i]=read(),L[i]=readll();
		a[i].resize(m[i]);
		for(reg int j=0;j<m[i];++j)
			a[i][j]=read();
		Maxm=max(Maxm,m[i]);
		MaxL=max(MaxL,L[i]);
	}/*
	if(MaxL<=1e6)
		Subtask1::Solve();
	else*/
		Subtask2::Solve();
	return 0;
}