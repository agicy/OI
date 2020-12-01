#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=1e6+5;

int n;
char str[MAXN];
int sum[MAXN];
int sumO[MAXN],sumE[MAXN];
int nex[MAXN];

int main(void){
	freopen("puzzle.in","r",stdin);
	freopen("puzzle.out","w",stdout);

	int idx=read();
	n=read();
	scanf("%s",str+1);
	for(reg int i=1;i<=n;++i)
		sum[i]=sum[i-1]+(str[i]=='1');
	sum[n+1]=sum[n]+1;
	for(reg int i=1;i<=n;++i){
		sumO[i]=sumO[i-1]+(sum[i]&1);
		sumE[i]=sumE[i-1]+(1^(sum[i]&1));
	}
	nex[n]=n+1;
	for(reg int i=n-1;i>=1;--i){
		if(str[i+1]=='1')
			nex[i]=i+1;
		else
			nex[i]=nex[i+1];
	}
	reg ll ans=0;
	for(reg int i=1;i<=n;++i){
		reg int ptr=nex[i];
		if(ptr==n+1)
			break;
		reg int add;
		if(sum[i]&1)
			if(str[i]=='1')
				add=sumO[n]-sumO[ptr];
			else
				add=sumE[n]-sumE[ptr];
		else
			if(str[i]=='1')
				add=sumE[n]-sumE[ptr];
			else
				add=sumO[n]-sumO[ptr];
		ans+=add;
	}
	printf("%lld\n",ans);

	fclose(stdin);
	fclose(stdout);
	return 0;
}