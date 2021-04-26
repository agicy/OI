#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(reg int x){
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

const int MAXN=1e5+5;
const int MAXM=1e5+5;

int n,m,p;
int a[MAXN];
vector<pair<int,int>/**/> q[MAXM];

namespace Subtask2{
	const int MAXN=5e3+5;
	const int MAXA=1e5+5;
	bool inque[MAXA];
	int Q[MAXN];
	int dec[MAXN];
	inline void Solve(void){
		reg int lastans=0;
		for(reg int i=1;i<=m;++i){
			if(p&&i!=1){
				for(reg int j=0,siz=q[i].size();j<siz;++j){
					reg int x=(q[i][j].first^lastans)%n+1,y=(q[i][j].second^lastans)%n+1;
					q[i][j].first=min(x,y),q[i][j].second=max(x,y);
				}
			}
			for(reg int j=0,siz=q[i].size();j<siz;++j)
				++dec[q[i][j].first],--dec[q[i][j].second+1];
			reg int sum=0;
			reg int _head=0,_tail=0;
			for(reg int j=1;j<=n;++j){
				sum+=dec[j];
				if(sum)
					if(!inque[a[j]]){
						inque[a[j]]=true;
						Q[_tail++]=a[j];
					}
			}
			reg int siz=_tail-_head;
			while(_head<_tail)
				inque[Q[_head++]]=false;
			writeln(lastans=siz);
			for(reg int j=0,siz=q[i].size();j<siz;++j)
				--dec[q[i][j].first],++dec[q[i][j].second+1];
		}
		return;
	}
}

namespace Subtask3{
	const int MAXA=1e5+5;
	const int MAXCNT=1e4+5;
	int pos[MAXA];
	int pre[MAXN];
	int lef[MAXCNT],rig[MAXCNT],id[MAXN];
	int tmp[MAXN];
	inline int solve(reg int l,reg int r){
		reg int lid=id[l],rid=id[r];
		if(lid==rid||lid+1==rid){
			reg int res=0;
			for(reg int i=l;i<=r;++i)
				if(pre[i]<l)
					++res;
			return res;
		}
		else{
			reg int res=0;
			for(reg int i=l;i<=rig[lid];++i)
				if(pre[i]<l)
					++res;
			for(reg int i=lef[rid];i<=r;++i)
				if(pre[i]<l)
					++res;
			for(reg int i=lid+1;i<rid;++i){
				if(tmp[lef[i]]>=l)
					continue;
				reg int _l=lef[i],_r=rig[i],_mid;
				while(_l<_r){
					_mid=(_l+_r)>>1;
					if(tmp[_mid+1]<l)
						_l=_mid+1;
					else
						_r=_mid;
				}
				res+=_l-lef[i]+1;
			}
			return res;
		}
	}
	inline void Solve(void){
		for(reg int i=1;i<=n;++i){
			pre[i]=pos[a[i]];
			pos[a[i]]=i;
		}
		reg int B=sqrt(n),tot=(n+B-1)/B;
		for(reg int i=1;i<=tot;++i){
			lef[i]=(i-1)*B+1,rig[i]=min(i*B,n);
			for(reg int j=lef[i];j<=rig[i];++j){
				id[j]=i;
				tmp[j]=pre[j];
			}
			sort(tmp+lef[i],tmp+rig[i]+1);
		}
		reg int lastans=0;
		for(reg int i=1;i<=m;++i){
			if(p&&i!=1){
				for(reg int j=0,siz=q[i].size();j<siz;++j){
					reg int x=(q[i][j].first^lastans)%n+1,y=(q[i][j].second^lastans)%n+1;
					q[i][j].first=min(x,y),q[i][j].second=max(x,y);
				}
			}
			assert(q[i].size()==1);
			reg int res=solve(q[i][0].first,q[i][0].second);
			writeln(lastans=res);
		}
		return;
	}
}

namespace Subtask{
	const int MAXN=1e5+5;
	const int MAXA=1e5+5;
	bool inque[MAXA];
	int Q[MAXN];
	int dec[MAXN];
	inline void Solve(void){
		reg int lastans=0;
		for(reg int i=1;i<=m;++i){
			if(p&&i!=1){
				for(reg int j=0,siz=q[i].size();j<siz;++j){
					reg int x=(q[i][j].first^lastans)%n+1,y=(q[i][j].second^lastans)%n+1;
					q[i][j].first=min(x,y),q[i][j].second=max(x,y);
				}
			}
			for(reg int j=0,siz=q[i].size();j<siz;++j)
				++dec[q[i][j].first],--dec[q[i][j].second+1];
			reg int sum=0;
			reg int _head=0,_tail=0;
			for(reg int j=1;j<=n;++j){
				sum+=dec[j];
				if(sum)
					if(!inque[a[j]]){
						inque[a[j]]=true;
						Q[_tail++]=a[j];
					}
			}
			reg int siz=_tail-_head;
			while(_head<_tail)
				inque[Q[_head++]]=false;
			writeln(lastans=siz);
			for(reg int j=0,siz=q[i].size();j<siz;++j)
				--dec[q[i][j].first],++dec[q[i][j].second+1];
		}
		return;
	}
}

int main(void){
	n=read(),m=read(),p=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	reg bool subtask3flag=true;
	for(reg int i=1;i<=m;++i){
		reg int k=read();
		q[i].resize(k);
		if(k>1)
			subtask3flag=false;
		for(reg int j=0;j<k;++j)
			q[i][j].first=read(),q[i][j].second=read();
	}
	if(n<=5e3&&m<=5e3)
		Subtask2::Solve();
	else if(subtask3flag)
		Subtask3::Solve();
	else
		Subtask::Solve();
	flush();
	return 0;
}