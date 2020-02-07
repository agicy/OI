#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;

const int MAXN=40+5;

int n;
bool str[MAXN];
int ans;

inline bool check(int len){
	if(len<3)
		return true;
	reg int p1=len,p2=len-1,p3=len-2;
	reg bool flag;
	for(reg int i=1;i<=(len/3);++i){
		flag=false;
		for(reg int j=0;j<i;++j)
			if(str[p1-j]!=str[p2-j]||str[p1-j]!=str[p3-j]||str[p2-j]!=str[p3-j]) {
				flag=true;
				break;
			}
		if(!flag)
			return false;
		--p2;
		p3=p3-2;
	}
	return true;
}

inline void DFS(reg int dep){
	if(dep==n+1){
		++ans;
		return;
	}
	str[dep]=false;
	if(check(dep))
		DFS(dep+1);
	str[dep]=true;
	if(check(dep))
		DFS(dep+1);
	return;
}

int main(void){
	scanf("%d",&n);
	DFS(2);
	printf("%d\n",ans<<1);
	return 0;
}
