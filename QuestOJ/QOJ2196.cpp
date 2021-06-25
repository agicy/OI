#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
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

const int MAXN=5e4+5;
const int MAXA=5e4+5;
const int MAXBLK=250;

int n,q,type;
int a[MAXN];
int B;
int lef[MAXBLK],rig[MAXBLK];
int id[MAXN];
int cnt[MAXBLK][MAXA];
int sum[MAXBLK][MAXA];
ll f[MAXBLK][MAXBLK];
bool vis[MAXA];

inline ll sqr(reg int x){
	return 1ll*x*x;
}

inline void build(reg int id){
	for(reg int i=lef[id];i<=rig[id];++i)
		++cnt[id][a[i]];
	return;
}

int tmp[MAXA];
bool inque[MAXA];
int Q[MAXA];

inline void Init(reg int tot){
	reg int _head,_tail;
	for(reg int i=1;i<=tot;++i){
		_head=_tail=0;
		reg ll ans=0;
		for(reg int j=i;j<=tot;++j){
			for(reg int k=lef[j];k<=rig[j];++k){
				++tmp[a[k]];
				if(!inque[a[k]]){
					inque[a[k]]=true;
					Q[_tail++]=a[k];
				}
				ans+=sqr(tmp[a[k]])-sqr(tmp[a[k]]-1);
			}
			f[i][j]=ans;
		}
		while(_head<_tail){
			reg int u=Q[_head++];
			inque[u]=false;
			tmp[u]=0;
		}
	}
	return;
}

int main(void){
	n=read(),q=read(),type=read();
	reg int Max=0;
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		Max=max(Max,a[i]);
	}
	B=sqrt(n);
	reg int tot=(n+B-1)/B;
	for(reg int i=1;i<=tot;++i){
		lef[i]=(i-1)*B+1,rig[i]=min(i*B,n);
		for(reg int j=lef[i];j<=rig[i];++j)
			id[j]=i;
		build(i);
		for(reg int j=1;j<=Max;++j)
			sum[i][j]=sum[i-1][j]+cnt[i][j];
	}
	Init(tot);
	reg ll lastans=0;
	for(reg int i=1;i<=q;++i){
		static ll x,y;
		x=read(),y=read();
		if(type) x^=lastans,y^=lastans;
		static int L,R;
		L=min(x%n+1,y%n+1),R=max(x%n+1,y%n+1);
		reg int idl=id[L],idr=id[R];
		reg int _head=0,_tail=0;
		reg ll ans=0;
		if(idl==idr||idl+1==idr){
			for(reg int j=L;j<=R;++j){
				++tmp[a[j]];
				if(!inque[a[j]]){
					inque[a[j]]=true;
					Q[_tail++]=a[j];
				}
				ans+=sqr(tmp[a[j]])-sqr(tmp[a[j]]-1);
			}
			while(_head<_tail){
				reg int u=Q[_head++];
				inque[u]=false;
				tmp[u]=0;
			}
		}
		else{
			ans=f[idl+1][idr-1];
			for(reg int j=L;j<=rig[idl];++j){
				if(!vis[a[j]]){
					vis[a[j]]=true;
					tmp[a[j]]+=sum[idr-1][a[j]]-sum[idl][a[j]];
				}
				++tmp[a[j]];
				ans+=sqr(tmp[a[j]])-sqr(tmp[a[j]]-1);
				if(!inque[a[j]]){
					inque[a[j]]=true;
					Q[_tail++]=a[j];
				}
			}
			for(reg int j=R;j>=lef[idr];--j){
				if(!vis[a[j]]){
					vis[a[j]]=true;
					tmp[a[j]]+=sum[idr-1][a[j]]-sum[idl][a[j]];
				}
				++tmp[a[j]];
				ans+=sqr(tmp[a[j]])-sqr(tmp[a[j]]-1);
				if(!inque[a[j]]){
					inque[a[j]]=true;
					Q[_tail++]=a[j];
				}
			}
			while(_head<_tail){
				reg int u=Q[_head++];
				inque[u]=vis[u]=false;
				tmp[u]=0;
			}
		}
		ans=(ans-(R-L+1))>>1;
		writeln(ans);
		lastans=ans;
	}
	flush();
	return 0;
}