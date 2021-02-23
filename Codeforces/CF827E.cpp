#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void read(reg char *s){
	*s=getchar();
	while(*s!='V'&&*s!='K'&&*s!='?')*s=getchar();
	while(*s=='V'||*s=='K'||*s=='?')*(++s)=getchar();
	*s='\0';
	return;
}

namespace Poly{
	const int p=998244353;
	const int g=3;
	const int invg=332748118;
	inline int add(reg int a,reg int b){
		a+=b;
		return a>=p?a-p:a;
	}
	inline int sub(reg int a,reg int b){
		a-=b;
		return a<0?a+p:a;
	}
	inline int fpow(reg int x,reg int exp){
		reg int res=1;
		while(exp){
			if(exp&1)
				res=1ll*res*x%p;
			x=1ll*x*x%p;
			exp>>=1;
		}
		return res;
	}
	vector<int> rev;
	inline int getRev(reg int n){
		reg int limit=1,l=0;
		while(limit<n)
			limit<<=1,++l;
		rev.resize(limit);
		for(reg int i=0;i<limit;++i)
			rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
		return limit;
	}
	typedef vector<int> poly;
	inline void NTT(reg poly& a,reg int limit,reg int flag){
		for(reg int i=0;i<limit;++i)
			if(i<rev[i])
				swap(a[i],a[rev[i]]);
		for(reg int i=1;i<limit;i<<=1){
			reg int w=fpow(flag==1?g:invg,(p-1)/(i<<1));
			for(reg int j=0;j<limit;j+=(i<<1)){
				reg int e=1;
				for(reg int k=0;k<i;++k,e=1ll*e*w%p){
					reg int x=a[j+k],y=1ll*e*a[i+j+k]%p;
					a[j+k]=add(x,y),a[i+j+k]=sub(x,y);
				}
			}
		}
		if(flag==-1){
			reg int inv=fpow(limit,p-2);
			for(reg int i=0;i<limit;++i)
				a[i]=1ll*a[i]*inv%p;
		}
		return;
	}
	inline poly mul(poly a,poly b){
		reg int s=a.size()+b.size()-1;
		reg int limit=getRev(s);
		a.resize(limit),b.resize(limit);
		NTT(a,limit,1),NTT(b,limit,1);
		for(reg int i=0;i<limit;++i)
			a[i]=1ll*a[i]*b[i]%p;
		NTT(a,limit,-1);
		a.resize(s);
		return a;
	}
}

using namespace Poly;

const int MAXN=5e5+5;

int n;
char s[MAXN];

int main(void){
	reg int t=read();
	while(t--){
		n=read();
		read(s);
		poly f,g,res;
		f.resize(n),g.resize(n),res.resize(n+1);
		for(reg int i=0;i<n;++i)
			f[n-i-1]=(s[i]=='K'),g[i]=(s[i]=='V');
		f=mul(f,g);
		for(reg int i=1;i<n;++i)
			res[i]+=f[i+n-1];
		f.resize(n),g.resize(n);
		for(reg int i=0;i<n;++i)
			f[n-i-1]=(s[i]=='V'),g[i]=(s[i]=='K');
		f=mul(f,g);
		for(reg int i=1;i<n;++i)
			res[i]+=f[i+n-1];
		reg int tot=0;
		static int ans[MAXN];
		for(reg int i=1;i<=n;++i){
			reg bool flag=true;
			for(reg int j=i;j<=n;j+=i)
				if(res[j]){
					flag=false;
					break;
				}
			if(flag)
				ans[++tot]=i;
		}
		printf("%d\n",tot);
		for(reg int i=1;i<=tot;++i)
			printf("%d%c",ans[i],i==tot?'\n':' ');
	}
	return 0;
}