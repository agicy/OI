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

const int MAXSIZE=5e6+5;

int a1,a2,a3,a4;
int S[MAXSIZE];

inline void dfs(int a1,int a2,int a3,int a4,int dep){
	if(!a1&&!a2&&!a3&&!a4){
		for(reg int i=1;i<dep;++i)
			putchar(S[i]?'7':'4');
		putchar('\n');
		exit(0);
	}
	if(S[dep-1]==-1){
		if(a1<a3||a2<a3||a1<a4||a2<a4)
			return;
		if(a1)
			S[dep]=0,
			dfs(a1-1,a2,a3,a4,dep+1);
		if(a2)
			S[dep]=1,
			dfs(a1,a2-1,a3,a4,dep+1);
	}
	else{
		if(S[dep-1]==0){
			if(a1<a3-1||a2<a3||a1<a4||a2<a4)
				return;
			if(a1)
				S[dep]=0,
				dfs(a1-1,a2,a3,a4,dep+1);
			if(a2&&a4)
				S[dep]=1,
				dfs(a1,a2-1,a3-1,a4,dep+1);
		}
		else{
			if(a1<a3||a2<a3||a1<a4||a2<a4-1)
				return;
			if(a1&&a4)
				S[dep]=0,
				dfs(a1-1,a2,a3,a4-1,dep+1);
			if(a2)
				S[dep]=1,
				dfs(a1,a2-1,a3,a4,dep+1);
		}
	}
	return;
}

int main(void){
	a1=read(),a2=read(),a3=read(),a4=read();
	S[0]=-1;
	dfs(a1,a2,a3,a4,1);
	puts("-1");
	return 0;
}