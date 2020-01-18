#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=300000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m;
int a[MAXN];

inline void Read(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	return;
}

vector<int> V[MAXN];

inline void Work(void){
	for(reg int i=1;i<=n;++i)
		V[a[i]].push_back((int)i);
	while(m--){
		static int opt;
		opt=read();
		if(opt==1){
			static int l,r,c;
			l=read(),r=read(),c=read();
			reg int temp1=lower_bound(V[c].begin(),V[c].end(),l)-V[c].begin();
			reg int temp2=upper_bound(V[c].begin(),V[c].end(),r)-V[c].begin()-1;
			printf("%d\n",max(temp2-temp1+1,0));
		}
		else if(opt==2){
			static int x;
			x=read();
			if(a[x]==a[x+1])
				continue;
			reg int temp1=lower_bound(V[a[x]].begin(),V[a[x]].end(),x)-V[a[x]].begin();
			reg int temp2=lower_bound(V[a[x+1]].begin(),V[a[x+1]].end(),x+1)-V[a[x+1]].begin();
			++V[a[x]][temp1],--V[a[x+1]][temp2];
			swap(a[x],a[x+1]);
		}
	}
	return;
}
