#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=12;
const int MAXM=12;

int n,m;
ll f[MAXM][1<<MAXN];
bool st[1<<MAXN];

int main(void){
	while(n=read(),m=read(),n!=0||m!=0){
		reg int U=(1<<n)-1;
		for(reg int i=0;i<=U;++i){
			reg int cnt=0;
			st[i]=true;
			for(reg int j=0;j<n;++j)
				if((i>>j)&1){
					if(cnt&1)
						st[i]=false;
					cnt=0;
				}
				else
					++cnt;
			if(cnt&1)
				st[i]=false;
		}
		memset(f,0,sizeof(f));
		f[0][0]=1;
		for(reg int i=1;i<=m;++i)
			for(reg int j=0;j<=U;++j){
				for(reg int k=0;k<=U;++k)
					if(!(j&k)&&st[j|k])
						f[i][j]+=f[i-1][k];
			}
		printf("%lld\n",f[m][0]);
	}
	return 0;
}