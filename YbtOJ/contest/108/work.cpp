#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=20;
const int MAXS=50+5;
const int inf=0x3f3f3f3f;

int n;
char name[MAXN][MAXS];
int d[MAXN],c[MAXN];
int Lg[1<<MAXN];
int sum[1<<MAXN];
int f[1<<MAXN];
int from[1<<MAXN];
int st[MAXN];

inline int lowbit(reg int x){
	return x&(-x);
}

int main(void){
	freopen("work.in","r",stdin);
	freopen("work.out","w",stdout);

	reg int t=read();
	while(t--){
		n=read();
		for(reg int i=0;i<n;++i)
			scanf("%s",name[i]),d[i]=read(),c[i]=read();
		reg int U=(1<<n)-1;
		for(reg int i=0;i<n;++i)
			Lg[1<<i]=i;
		for(reg int S=1;S<=U;++S)
			sum[S]=sum[S^lowbit(S)]+c[Lg[lowbit(S)]];
		f[0]=0;
		for(reg int S=1;S<=U;++S){
			f[S]=inf;
			for(reg int i=n-1;i>=0;--i)
				if((S>>i)&1){
					reg int sub=S^(1<<i),w=max(sum[sub]+c[i]-d[i],0);
					if(f[sub]+w<f[S]){
						f[S]=f[sub]+w;
						from[S]=sub;
					}
				}
		}
		printf("%d\n",f[U]);
		reg int top=0;
		for(reg int S=U;S;S=from[S])
			st[top++]=Lg[S^from[S]];
		for(reg int i=top-1;i>=0;--i)
			puts(name[st[i]]);
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}