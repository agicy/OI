#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int lowbit(reg int x){
	return x&(-x);
}

const int MAXN=1e5+5;

int n,k;
int rnk[MAXN];
ll ans;

namespace BIT{
	int n,unit[MAXN];
	inline void init(reg int s){
		n=s;
		return;
	}
	inline void update(reg int id,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline void clear(reg int id){
		for(reg int i=id;i<=n;i+=lowbit(i))
			if(!unit[i])
				break;
			else
				unit[i]=0;
		return;
	}
	inline int query(reg int id){
		reg int res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res+=unit[i];
		return res;
	}
	inline int query(reg int l,reg int r){
		if(l>r)
			return 0;
		else
			return query(r)-query(l-1);
	}
}

struct Node{
	int x,y,z;
	inline Node(void){return;}
	inline Node(const int& x,const int& y,const int& z):x(x),y(y),z(z){return;}
	inline bool operator<(const Node& a)const{return x<a.x||(x==a.x&&(y>a.y||(y==a.y&&z<a.z)));}
};

Node a[MAXN];

inline void solve(reg int l,reg int r){
	if(l==r)
		return;
	reg int mid=(l+r)>>1;
	solve(l,mid),solve(mid+1,r);
	for(reg int i=mid+1,j=l;i<=r;++i){
		while(j<=mid&&a[j].y>a[i].y)
			BIT::update(a[j++].z,1);
		ans+=BIT::query(1,a[i].z-k-1)+BIT::query(a[i].z+k+1,n);
	}
	for(reg int i=l;i<=mid;++i)
		BIT::clear(a[i].z);
	static Node tmp[MAXN];
	reg int k=l,i=l,j=mid+1;
	while(i<=mid&&j<=r)
		if(a[i].y>a[j].y)
			tmp[k++]=a[i++];
		else
			tmp[k++]=a[j++];
	while(i<=mid)
		tmp[k++]=a[i++];
	while(j<=r)
		tmp[k++]=a[j++];
	for(reg int i=l;i<=r;++i)
		a[i]=tmp[i];
	return;
}

bool ed;

int main(void){
	n=read(),k=read();
	for(reg int i=1;i<=n;++i)
		rnk[read()]=i;
	for(int i=1;i<=n;++i){
		static int x;
		x=read();
		a[i]=Node(rnk[x],i,x);
	}
	sort(a+1,a+n+1);
	BIT::init(n);
	solve(1,n);
	printf("%lld\n",ans);
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}