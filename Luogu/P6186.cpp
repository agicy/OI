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

const int MAXN=200000+5;

struct TreeArray{
	#define lowbit(x) ( (x) & ( - (x) ) )
	int n;
	ll unit[MAXN];
	inline void Init(reg int size){
		n=size;
		memset(unit,0,sizeof(unit));
		return;
	}
	inline void Update(reg int ID,reg ll val){
		for(reg int i=ID;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline ll Query(reg int ID){
		reg ll res=0;
		for(reg int i=ID;i;i-=lowbit(i))
			res+=unit[i];
		return res;
	}
	#undef lowbit
};

int n,m;
int p[MAXN],back[MAXN];
int T[MAXN];
TreeArray Ta;

int main(void){
	//freopen("bubble.in","r",stdin);
	//freopen("bubble.out","w",stdout);
	n=read(),m=read();
	Ta.Init(n);
	reg ll ans=0;
	for(reg int i=1;i<=n;++i){
		p[i]=read();
		back[i]=i-1-Ta.Query(p[i]);
		ans+=back[i];
		++T[back[i]];
		Ta.Update(p[i],1);
	}
	Ta.Init(n);
	Ta.Update(1,ans);
	reg ll temp=0;
	for(reg int i=0;i<n;++i){
		temp+=T[i];
		Ta.Update(i+2,-(n-temp));
	}
	while(m--){
		static int opt,x;
		opt=read(),x=read();
		x=min(x,n-1);
		if(opt==1){
			reg bool f=(p[x]<p[x+1]);
			swap(p[x],p[x+1]);
			swap(back[x],back[x+1]);
			if(f){
				Ta.Update(1,1);
				Ta.Update(back[x+1]+2,-1);
				++back[x+1];
			}
			else{
				Ta.Update(1,-1);
				--back[x];
				Ta.Update(back[x]+2,1);
			}
		}
		if(opt==2)
			printf("%lld\n",Ta.Query(x+1));
	}
	//fclose(stdin);
	//fclose(stdout);
	return 0;
}
