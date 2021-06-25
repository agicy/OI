#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXV=3e3+5;
const ll inf=0x3f3f3f3f3f3f3f3f;

int v,p;
int a[MAXV];
ll sum[MAXV];
ll f[MAXV];
int cnt[MAXV];

inline ll getVal(reg int l,reg int r){
	reg int mid=(l+r)>>1;
	return sum[r]+sum[l-1]-(sum[mid]+sum[mid-1])-(((r^l)&1)?a[mid]:0);
}

inline bool cmp(reg int i,reg int j,reg int k){
	return f[i]+getVal(i+1,k)<f[j]+getVal(j+1,k)||(f[i]+getVal(i+1,k)<f[j]+getVal(j+1,k)&&cnt[i]<cnt[j]);
}

struct Node{
	int lef,rig;
	inline Node(reg int lef=0,reg int rig=0):lef(lef),rig(rig){
		return;
	}
};

inline void calc(reg ll mid){
	reg int _head=0,_tail=0;
	static Node Q[MAXV];
	Q[_tail++]=Node(0,1);
	for(reg int i=1;i<=v;++i){
		while(_tail-_head>1&&Q[_head+1].rig<=i)
			++_head;
		reg int j=Q[_head].lef;
		f[i]=f[j]+getVal(j+1,i)+mid;
		cnt[i]=cnt[j]+1;
		while(_head<_tail&&cmp(i,Q[_tail-1].lef,Q[_tail-1].rig))
			--_tail;
		reg int l=Q[_tail-1].rig,r=v+1,mid;
		while(l<r){
			mid=(l+r)>>1;
			if(cmp(i,Q[_tail-1].lef,mid))
				r=mid;
			else
				l=mid+1;
		}
		if(l<=v)
			Q[_tail++]=Node(i,l);
	}
	return;
}

int main(void){
	v=read(),p=read();
	for(reg int i=1;i<=v;++i)
		a[i]=read(),sum[i]=sum[i-1]+a[i];
	reg ll l=0,r=sum[v]+1,mid;
	while(l<r){
		mid=(l+r)>>1;
		calc(mid);
		if(cnt[v]<=p)
			r=mid;
		else
			l=mid+1;
	}
	calc(l);
	printf("%lld\n",f[v]-l*p);
	return 0;
}