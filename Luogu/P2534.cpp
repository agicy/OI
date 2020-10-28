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
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=16+5;

int n;
int a[MAXN];
vector<int> V;
int itdep;

inline int f(void){
	reg int res=0;
	for(reg int i=1;i<=n;++i)
		res+=(abs(a[i]-a[i+1])!=1);
	return res;
}

inline bool dfs(reg int dep,reg int pre){
	reg int val=f();
	if(!val)
		return true;
	if(dep+val>itdep)
		return false;
	for(reg int i=1;i<=n;++i){
		if(i==pre)
			continue;
		reverse(a+1,a+i+1);
		if(dfs(dep+1,i))
			return true;
		reverse(a+1,a+i+1);
	}
	return false;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		V.push_back(a[i]);
	}
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	for(reg int i=1;i<=n;++i)
		a[i]=lower_bound(V.begin(),V.end(),a[i])-V.begin()+1;
	a[n+1]=n+1;
	for(itdep=0;;++itdep)
		if(dfs(0,0)){
			printf("%d\n",itdep);
			break;
		}
	return 0;
}