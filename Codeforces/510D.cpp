#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
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

const int MAXN=300+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n;
int l[MAXN],c[MAXN];

inline void Read(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		l[i]=read();
	for(reg int i=1;i<=n;++i)
		c[i]=read();
	return;
}

inline ll gcd(reg ll a,reg ll b){
	return b==0?a:gcd(b,a%b);
}

map<int,int> M;

inline void Work(void){
	for(reg int i=1;i<=n;++i){
		static map<int,int>::iterator it;
		if(M.count(l[i]))
			M[l[i]]=min(M[l[i]],c[i]);
		else
			M[l[i]]=c[i];
		for(it=M.begin();it!=M.end();++it){
			reg int L=it->first,val=it->second;
			if(M.count(gcd(L,l[i])))
				M[gcd(L,l[i])]=min(M[gcd(L,l[i])],val+c[i]);
			else
				M[gcd(L,l[i])]=val+c[i];
		}
	}
	if(M[1])
		printf("%d\n",M[1]);
	else
		puts("-1");
	return;
}
