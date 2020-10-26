#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void cMax(reg int &a,reg int b){
	if(a<b)
		a=b;
	return;
}

const int MAXN=1e3+5;
const int MAXE=1e3;

struct Node{
	int id,val;
	inline Node(reg int id=0,reg int val=0):id(id),val(val){
		return;
	}
};

int n,q;
int a[MAXN],b[MAXN],c[MAXN];
int pre[MAXN][MAXE+5],suf[MAXN][MAXE+5];
Node Q[MAXE];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read(),b[i]=read(),c[i]=read();
	for(reg int i=1;i<=n;++i){
		if(MAXE/a[i]<c[i])
			c[i]=MAXE/a[i];
		for(reg int j=0;j<a[i];++j){
			reg int head=0,tail=0;
			for(reg int k=0;k<=(MAXE-j)/a[i];++k){
				reg int x=k,y=pre[i-1][k*a[i]+j]-k*b[i];
				while(head<tail&&Q[head].id<k-c[i])
					++head;
				while(head<tail&&Q[tail-1].val<=y)
					--tail;
				Q[tail++]=Node(x,y);
				pre[i][k*a[i]+j]=Q[head].val+k*b[i];
			}
		}
	}
	for(reg int i=n;i>=1;--i){
		if(MAXE/a[i]<c[i])
			c[i]=MAXE/a[i];
		for(reg int j=0;j<a[i];++j){
			reg int head=0,tail=0;
			for(reg int k=0;k<=(MAXE-j)/a[i];++k){
				reg int x=k,y=suf[i+1][k*a[i]+j]-k*b[i];
				while(head<tail&&Q[head].id<k-c[i])
					++head;
				while(head<tail&&Q[tail-1].val<=y)
					--tail;
				Q[tail++]=Node(x,y);
				suf[i][k*a[i]+j]=Q[head].val+k*b[i];
			}
		}
	}
	q=read();
	while(q--){
		static int d,e;
		d=read()+1,e=read();
		int ans=0;
		for(reg int i=0;i<=e;++i)
			cMax(ans,pre[d-1][i]+suf[d+1][e-i]);
		printf("%d\n",ans);
	}
	return 0;
}