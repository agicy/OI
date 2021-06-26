#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x<0) x=-x,putchar('-');
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=1e5+5;
const int inf=0x7fffffff;

int n,m;
int a[MAXN];
int id[MAXN];
int lef[MAXN],rig[MAXN];
int tAdd[MAXN];
int V[MAXN];

inline void build(reg int id){
	for(reg int i=lef[id];i<=rig[id];++i)
		V[i]=a[i];
	sort(V+lef[id],V+rig[id]+1);
	return;
}

inline void update(reg int l,reg int r,reg int val){
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
			tAdd[i]+=val;
	}
	return;
}

inline int getMax(reg int l,reg int r){
	reg int lid=id[l],rid=id[r];
	reg int res=-inf;
	if(lid==rid){
		for(reg int i=l;i<=r;++i)
			res=max(res,a[i]);
		res+=tAdd[lid];
	}
	else{
		for(reg int i=l;i<=rig[lid];++i)
			res=max(res,a[i]+tAdd[lid]);
		for(reg int i=lef[rid];i<=r;++i)
			res=max(res,a[i]+tAdd[rid]);
		for(reg int i=lid+1;i<rid;++i)
			res=max(res,V[rig[i]]+tAdd[i]);
	}
	return res;
}

inline int getMin(reg int l,reg int r){
	reg int lid=id[l],rid=id[r];
	reg int res=inf;
	if(lid==rid){
		for(reg int i=l;i<=r;++i)
			res=min(res,a[i]);
		res+=tAdd[lid];
	}
	else{
		for(reg int i=l;i<=rig[lid];++i)
			res=min(res,a[i]+tAdd[lid]);
		for(reg int i=lef[rid];i<=r;++i)
			res=min(res,a[i]+tAdd[rid]);
		for(reg int i=lid+1;i<rid;++i)
			res=min(res,V[lef[i]]+tAdd[i]);
	}
	return res;
}

inline int getCnt(reg int l,reg int r,reg int val){
	reg int lid=id[l],rid=id[r];
	reg int res=0;
	if(lid==rid)
		for(reg int i=l;i<=r;++i)
			res+=(a[i]+tAdd[lid]<=val);
	else{
		for(reg int i=l;i<=rig[lid];++i)
			res+=(a[i]+tAdd[lid]<=val);
		for(reg int i=lef[rid];i<=r;++i)
			res+=(a[i]+tAdd[rid]<=val);
		for(reg int i=lid+1;i<rid;++i)
			if(V[lef[i]]+tAdd[i]>val)
				continue;
			else if(V[rig[i]]+tAdd[i]<=val)
				res+=rig[i]-lef[i]+1;
			else{
				reg int __l=lef[i],__r=rig[i],__mid;
				while(__l<__r){
					__mid=(__l+__r)>>1;
					if(V[__mid+1]+tAdd[i]<=val)
						__l=__mid+1;
					else
						__r=__mid;
				}
				res+=__l-lef[i]+1;
			}
	}
	return res;
}

inline int query(reg int l,reg int r,reg int k){
	if(k<1||r-l+1<k)
		return -1;
	reg int __l=getMin(l,r),__r=getMax(l,r),__mid;
	while(__l<__r){
		__mid=(0ll+__l+__r)>>1;
		if(getCnt(l,r,__mid)<k)
			__l=__mid+1;
		else
			__r=__mid;
	}
	return __l;
}

bool ed;

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	reg int B=150,tot=(n+B-1)/B;
	for(reg int i=1;i<=tot;++i){
		lef[i]=(i-1)*B+1,rig[i]=min(i*B,n);
		for(reg int j=lef[i];j<=rig[i];++j)
			id[j]=i;
		build(i);
	}
	while(m--){
		static int opt,l,r,k;
		opt=read(),l=read(),r=read(),k=read();
		switch(opt){
			case 1:{
				writeln(query(l,r,k));
				break;
			}
			case 2:{
				update(l,r,k);
				break;
			}
		}
	}
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}