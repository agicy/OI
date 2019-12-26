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

const int MAXN=100000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Read(void){
	scanf("%s",str+1);
	return;
}

inline int Solve(reg char str[],reg int l,reg int r){
	reg bool flag=false;
	reg int num=0,pos=-1;
	for(reg int i=l;i<=r;++i){
		if(str[i]==-){
			f
		}
		if('0'<=str[i]<='9'){
			num=10*num+str[i]-'0';
		}
	}
	
}

inline void Work(void){
	reg int ans=Solve(str,1,strlen(str+1));
	printf("%d\n",ans);
	return;
}
