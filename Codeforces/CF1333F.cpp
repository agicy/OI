#include<bits/stdc++.h>
using namespace std;
#define reg register

const int MAXN=500000+5;

bool vis[MAXN];
int n;
int val,pos;
int ID,ans[MAXN];

inline void Del(void){
	while(true){
		while(pos<=n&&vis[pos])
			pos+=val;
		if(pos>n){
			--val;
			pos=(val<<1);
		}
		else{
			ans[--ID]=val;
			vis[pos]=true;
			break;
		}
	}
	return;
}

int main(void){
	scanf("%d",&n);
	ID=n;
	val=(n>>1);
	pos=((n>>1)<<1);
	for(reg int i=1;i<n;++i)
		Del();
	for(reg int i=1;i<n;++i)
		printf("%d%c",ans[i],i==n-1?'\n':' ');
	return 0;
}
