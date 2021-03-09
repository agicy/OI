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
	while(!isdigit(*s))*s=getchar();
	while(isdigit(*s))*(++s)=getchar();
	*s='\0';
	return;
}

const int MAXN=1e6+5;

int n;
char s[MAXN];
int val[MAXN];
bool inque[MAXN];
queue<int> Q;

int main(void){
	n=read();
	read(s+1);
	for(reg int i=1;i<=n;++i)
		if(s[i]=='1')
			++val[i-1],--val[i];
	for(reg int i=0;i<=n;++i)
		if(val[i]){
			inque[i]=true;
			Q.push(i);
		}
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		inque[u]=false;
		if(!val[u])
			continue;
		if(1<=u&&val[u-1]*val[u]<0){
			val[u]=val[u-1];
			val[u-1]=0;
			if(!inque[u]){
				inque[u]=true;
				Q.push(u);
			}
		}
		if(u<n&&val[u]*val[u+1]<0){
			val[u+1]=val[u];
			val[u]=0;
			if(!inque[u+1]){
				inque[u+1]=true;
				Q.push(u+1);
			}
		}
	}
	reg int cnt=0;
	for(reg int i=0;i<=n;++i)
		if(val[i])
			++cnt;
	printf("%d\n",cnt);
	return 0;
}