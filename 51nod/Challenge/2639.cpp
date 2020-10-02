#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXSIZE=1e4+5;

int n;
bool vis[MAXSIZE];
int tot,prime[MAXSIZE];
int d[MAXSIZE],c[MAXSIZE];

inline void Init(reg int n){
	d[1]=1;
	if(n==1){
		puts("1");
		exit(0);
	}
	for(reg int i=2;i<=n;++i){
		if(!vis[i]){
			d[i]=i+1;
			prime[++tot]=i;
			c[i]=i;
		}
		if(d[i]==n){
			printf("%d\n",i);
			exit(0);
		}
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			if(i%prime[j]==0){
				if(i*prime[j]==c[i]*prime[j])
					d[i*prime[j]]=d[i]+prime[j]*i;
				else
					d[i*prime[j]]=d[i]/d[c[i]]*d[c[i]*prime[j]];
				c[i*prime[j]]=c[i]*prime[j];
				break;
			}
			d[i*prime[j]]=d[i]*(prime[j]+1);
			c[i*prime[j]]=prime[j];
		}
	}
	return;
}

int main(void){
	scanf("%d",&n);
	Init(n);
	puts("-1");
	return 0;
}