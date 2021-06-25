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

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(x<0) x=-x,putchar('-');
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=5e4+5;

int n;
ll a[MAXN];
int lef[MAXN],rig[MAXN],id[MAXN];
ll tag[MAXN];
vector<ll> V[MAXN];

inline void build(reg int id){
	V[id].clear();
	V[id].reserve(rig[id]-lef[id]+1);
	for(reg int i=lef[id];i<=rig[id];++i)
		V[id].push_back(a[i]);
	sort(V[id].begin(),V[id].end());
	return;
}

inline void update(reg int l,reg int r,reg ll val){
	reg int lid=id[l],rid=id[r];
	if(lid==rid){
		for(reg int i=l;i<=r;++i)
			a[i]+=val;
		build(lid);
	}
	else{
		for(reg int i=l;i<=rig[lid];++i)
			a[i]+=val;
		build(lid);
		for(reg int i=lef[rid];i<=r;++i)
			a[i]+=val;
		build(rid);
		for(reg int i=lid+1;i<rid;++i)
			tag[i]+=val;
	}
	return;
}

inline int query(reg int l,reg int r,reg ll val){
	reg int res=0;
	reg int lid=id[l],rid=id[r];
	if(lid==rid){
		for(reg int i=l;i<=r;++i)
			if(a[i]+tag[lid]<val)
				++res;
	}
	else{
		for(reg int i=l;i<=rig[lid];++i)
			if(a[i]+tag[lid]<val)
				++res;
		for(reg int i=lef[rid];i<=r;++i)
			if(a[i]+tag[rid]<val)
				++res;
		for(reg int id=lid+1;id<rid;++id){
			if(V[id].size())
				if(V[id].front()+tag[id]<val){
					reg int __l=0,__r=V[id].size()-1,__mid;
					while(__l<__r){
						__mid=(__l+__r)>>1;
						if(V[id][__mid+1]+tag[id]<val)
							__l=__mid+1;
						else
							__r=__mid;
					}
					res+=__l+1;
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
		for(reg int j=lef[i];j<=rig[i];++j)
			id[j]=i;
		build(i);
	}
	for(reg int i=1;i<=n;++i){
		static int opt,l,r,c;
		opt=read(),l=read(),r=read(),c=read();
		switch(opt){
			case 0:{
				update(l,r,c);
				break;
			}
			case 1:{
				writeln(query(l,r,1ll*c*c));
				break;
			}
		}
	}
	flush();
	return 0;
}