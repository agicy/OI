#include<bits/stdc++.h>
using namespace std;
#define reg register
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

const int MAXN=50000+5;

int miu[MAXN],p[MAXN];
bool flag[MAXN];

inline void Init(reg int size){
	reg int tot=0;
	miu[1]=1;
	for(reg int i=2;i<=size;++i){
		if(!flag[i]){
			p[++tot]=i;
			miu[i]=-1;
		}
		for(reg int j=1;j<=tot&&i*p[j]<=size;++j){
			flag[i*p[j]]=true;
			if(i%p[j]==0){
				miu[i*p[j]]=0;
				break;
			}
			miu[i*p[j]]=-miu[i];
		}
	}
	for(reg int i=1;i<=size;++i)
		miu[i]+=miu[i-1];
	return;
}

inline int Calc(int n,int m){
	reg int res=0;
	for(reg int i=1,j;i<=min(n,m);i=j+1){
		j=min(n/(n/i),m/(m/i));
		res+=(miu[j]-miu[i-1])*(n/i)*(m/i);
	}
	return res;
}

int a,b,c,d,K;

int main(void){
	Init(5e4);
	reg int T=read();
	while(T--){
		a=read(),b=read(),c=read(),d=read(),K=read();
		printf("%d\n",(Calc(b/K,d/K)+Calc((a-1)/K,(c-1)/K))-(Calc(b/K,(c-1)/K)+Calc((a-1)/K,d/K)));
	}
	return 0;
}
