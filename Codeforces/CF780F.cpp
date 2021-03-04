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

const int MAXLOG2A=62;
const int MAXN=500;

int n,m;

struct Matrix{
	bitset<MAXN> unit[MAXN];
	inline Matrix operator*(const Matrix& a)const{
		Matrix res;
		for(reg int i=0;i<n;++i)
			for(reg int k=0;k<n;++k)
				if(unit[i][k])
					res.unit[i]|=a.unit[k];
		return res;
	}
};

Matrix f[MAXLOG2A][2];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int u,v,t;
		u=read()-1,v=read()-1,t=read();
		f[0][t].unit[u][v]=true;
	}
	reg int ptr=0;
	while(ptr<=60&&f[ptr][0].unit[0].count()){
		f[ptr+1][0]=f[ptr][0]*f[ptr][1];
		f[ptr+1][1]=f[ptr][1]*f[ptr][0];
		++ptr;
	}
	if(ptr>=61)
		puts("-1");
	else{
		reg bool flag=false;
		reg ll ans=0;
		bitset<MAXN> tmp,pre;
		pre[0]=true;
		for(reg int i=ptr;i>=0;--i){
			tmp.reset();
			for(reg int j=0;j<n;++j)
				if(pre[j])
					tmp|=f[i][flag].unit[j];
			if(tmp.count()){
				flag=!flag;
				ans|=1ll<<i;
				pre=tmp;
			}
		}
		if(ans>1e18)
			puts("-1");
		else
			printf("%lld\n",ans);
	}
	return 0;
}