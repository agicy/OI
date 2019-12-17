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

const int MAXN=20+5;

int n;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Read(void){
	n=read();
	return;
}

int Ans;
bool l[MAXN<<1];

inline void check(void){
	reg bool flag=false;
	reg int cnt=0,last=1;
	int ans[MAXN<<1];
	stack<int> S;
	for(int i=1;i<=2*n;++i){
		if(S.empty()&&l[i]==false){
			flag=true;
			break;
		}
		else{
			if(l[i])
				S.push(last++);
			else
				ans[++cnt]=S.top(),S.pop();
		}
	}
	if(flag||last!=n+1)
		return;
	else{
		++Ans;
		for(reg int i=1;i<=cnt;++i)
			printf("%d",ans[i]);
		putchar('\n');
	}
	return;
}

inline void DFS(reg int dep,reg int in,reg int out){
	if(out>in)
		return;
	if(dep==2*n+1){
		check();
		if(Ans>=20)
			exit(0);
		return;
	}
	l[dep]=false;
	DFS(dep+1,in,out+1);
	l[dep]=true;
	DFS(dep+1,in+1,out);
	l[dep]=false;
	return;
}

inline void Work(void){
	DFS(1,0,0);
	return;
}
