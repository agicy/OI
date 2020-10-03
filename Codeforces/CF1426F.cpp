#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=2e5+5;
const int p=1e9+7;

int s[4][4],num;

inline int add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=p?sum-p:sum;
}

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%p;
		x=1ll*x*x%p;
		exp>>=1;
	}
	return res;
}

int n;
char str[MAXN];

int main(void){
	scanf("%d%s",&n,str+1);
	reg int cnt=0;
	for(reg int i=1;i<=n;++i)
		switch(str[i]){
			case 'a':{
				++s[1][0];
				break;
			}
			case 'b':{
				s[2][1]=add(s[2][1],s[1][1]);
				s[2][0]=add(s[2][0],s[1][0]);
				break;
			}
			case 'c':{
				s[3][2]=add(s[3][2],s[2][2]);
				s[3][1]=add(s[3][1],s[2][1]);
				s[3][0]=add(s[3][0],s[2][0]);
				break;
			}
			case '?':{
				++cnt;
				s[3][3]=add(s[3][3],s[2][2]);
				s[3][2]=add(s[3][2],s[2][1]);
				s[3][1]=add(s[3][1],s[2][0]);
				s[2][2]=add(s[2][2],s[1][1]);
				s[2][1]=add(s[2][1],s[1][0]);
				++s[1][1];
				break;
			}
		}
	reg int ans=1ll*s[3][0]*fpow(3,cnt)%p;
	if(s[3][1])
		ans=add(ans,1ll*s[3][1]*fpow(3,cnt-1)%p);
	if(s[3][2])
		ans=add(ans,1ll*s[3][2]*fpow(3,cnt-2)%p);
	if(s[3][3])
		ans=add(ans,1ll*s[3][3]*fpow(3,cnt-3)%p);
	printf("%d\n",ans);
	return 0;
}