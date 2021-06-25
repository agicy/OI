#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=1e5+5;

int n;
int a[MAXN];
int lef[MAXN],rig[MAXN],id[MAXN];
ll tag[MAXN];
vector<ll> V[MAXN];

const ll inf=0x3f3f3f3f3f3f3f3f;

inline void pushdown(reg int id){
	if(tag[id]!=inf){
		for(reg int i=lef[id];i<=rig[id];++i)
			a[i]=tag[id];
		tag[id]=inf;
	}
	return;
}

inline void build(reg int id){
	V[id].clear();
	V[id].reserve(rig[id]-lef[id]+1+2);
	for(reg int i=lef[id];i<=rig[id];++i)
		V[id].push_back(a[i]);
	V[id].push_back(inf);
	V[id].push_back(-inf);
	sort(V[id].begin(),V[id].end());
	return;
}

inline void update(reg int l,reg int r,reg int c){
	reg int lid=id[l],rid=id[r];
	if(lid==rid){
		pushdown(lid);
		for(reg int i=l;i<=r;++i)
			a[i]=c;
		build(lid);
	}
	else{
		pushdown(lid);
		for(reg int i=l;i<=rig[lid];++i)
			a[i]=c;
		build(lid);
		pushdown(rid);
		for(reg int i=lef[rid];i<=r;++i)
			a[i]=c;
		build(rid);
		for(reg int i=lid+1;i<rid;++i)
			tag[i]=c;
	}
	return;
}

inline int query(reg int l,reg int r,reg int c){
	reg int lid=id[l],rid=id[r];
	reg int res=0;
	if(lid==rid){
		for(reg int i=l;i<=r;++i)
			if(tag[lid]==c||(tag[lid]==inf&&a[i]==c))
				++res;
		return res;
	}
	else{
		for(reg int i=l;i<=rig[lid];++i)
			if(tag[lid]==c||(tag[lid]==inf&&a[i]==c))
				++res;
		for(reg int i=lef[rid];i<=r;++i)
			if(tag[rid]==c||(tag[rid]==inf&&a[i]==c))
				++res;
		for(reg int id=lid+1;id<rid;++id){
			if(tag[id]==inf){
				reg int __l,__r,__mid;
				__l=0,__r=V[id].size()-1;
				while(__l<__r){
					__mid=(__l+__r)>>1;
					if(V[id][__mid]>=c)
						__r=__mid;
					else
						__l=__mid+1;
				}
				reg int lpos=__l;
				__l=0,__r=V[id].size()-1;
				while(__l<__r){
					__mid=(__l+__r)>>1;
					if(V[id][__mid]>c)
						__r=__mid;
					else
						__l=__mid+1;
				}
				reg int rpos=__l;
				res+=rpos-lpos;
			}
			else{
				if(tag[id]==c)
					res+=rig[id]-lef[id]+1;
			}
		}
	}
	return res;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	reg int B=max(100,int(sqrt(n))),tot=(n+B-1)/B;
	for(reg int i=1;i<=tot;++i){
		lef[i]=(i-1)*B+1,rig[i]=min(i*B,n);
		tag[i]=inf;
		for(reg int j=lef[i];j<=rig[i];++j)
			id[j]=i;
		build(i);
	}
	for(reg int i=1;i<=n;++i){
		static int l,r,c;
		l=read(),r=read(),c=read();
		writeln(query(l,r,c));
		update(l,r,c);
	}
	flush();
	return 0;
}