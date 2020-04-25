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
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=300000+5;

int n,s;
ll sumC[MAXN],sumT[MAXN];
int Q[MAXN];
ll f[MAXN];

inline ll X(reg int i){
	return sumC[i];
}

inline ll Y(reg int i){
	return f[i];
}

inline ll K(reg int i){
	return s+sumT[i];
}

inline int find(reg int l,reg int r,reg ll s){
	reg int res=r;
	while(l<=r){
		reg int mid=(l+r)>>1;
		if(Y(Q[mid+1])-Y(Q[mid])>s*(X(Q[mid+1])-X(Q[mid])))
			r=mid-1,res=mid;
		else
			l=mid+1;
	}
	return Q[res];
}

int main(void){
	n=read(),s=read();
	for(reg int i=1;i<=n;++i){
		sumT[i]=sumT[i-1]+read();
		sumC[i]=sumC[i-1]+read();
	}
	reg int head=1,tail=0;
	Q[++tail]=0;
	for(reg int i=1;i<=n;++i){
		reg int p=find(head,tail,K(i));
		f[i]=f[p]+s*(sumC[n]-sumC[p])+sumT[i]*(sumC[i]-sumC[p]);
		while(head<tail&&(Y(Q[tail])-Y(Q[tail-1]))*(X(i)-X(Q[tail]))>=(Y(i)-Y(Q[tail]))*(X(Q[tail])-X(Q[tail-1])))
			--tail;
		Q[++tail]=i;
	}
	printf("%lld\n",f[n]);
	return 0;
}
