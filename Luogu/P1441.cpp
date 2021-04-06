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

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=20;
const int MAXA=100;

int n,m;
int a[MAXN];

inline int getCnt(reg int lim){
	bitset<MAXN*MAXA+1> S;
	S[0]=true;
	for(reg int i=0;i<n;++i)
		if(!((lim>>i)&1))
			S|=(S<<a[i]);
	return S.count()-1;
}

int main(void){
	n=read(),m=read();
	for(reg int i=0;i<n;++i)
		a[i]=read();
	reg int ans=0;
	static int i[4];
	switch(m){
		case 0:{
			ans=max(ans,getCnt(0));
			break;
		}
		case 1:{
			for(i[0]=0;i[0]<n;++i[0])
				ans=max(ans,getCnt((1<<i[0])));
			break;
		}
		case 2:{
			for(i[0]=0;i[0]<n;++i[0])
				for(i[1]=i[0]+1;i[1]<n;++i[1])
					ans=max(ans,getCnt((1<<i[0])|(1<<i[1])));
			break;
		}
		case 3:{
			for(i[0]=0;i[0]<n;++i[0])
				for(i[1]=i[0]+1;i[1]<n;++i[1])
					for(i[2]=i[1]+1;i[2]<n;++i[2])
						ans=max(ans,getCnt((1<<i[0])|(1<<i[1])|(1<<i[2])));
			break;
		}
		case 4:{
			for(i[0]=0;i[0]<n;++i[0])
				for(i[1]=i[0]+1;i[1]<n;++i[1])
					for(i[2]=i[1]+1;i[2]<n;++i[2])
						for(i[3]=i[2]+1;i[3]<n;++i[3])
							ans=max(ans,getCnt((1<<i[0])|(1<<i[1])|(1<<i[2])|(1<<i[3])));
			break;
		}
	}
	printf("%d\n",ans);
	return 0;
}