#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e5+5;
const int p=1e9+7;

inline int add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=p?sum-p:sum;
}

inline int mul(reg int a,reg int b){
	return 1ll*a*b%p;
}

char str[MAXN];
int t[MAXN],basep[MAXN];

int main(void){
	scanf("%s",str+1);
	reg int len=strlen(str+1);
	t[0]=basep[0]=1;
	for(reg int i=1;i<=len;++i)
		t[i]=add(mul(10,t[i-1]),1),basep[i]=mul(10,basep[i-1]);
	reg int ans=0;
	for(reg int i=1,tmp=0;i<len;++i){
		tmp=add(mul(10,tmp),str[i]-'0');
		ans=add(ans,mul(tmp,t[len-i-1]));
	}
	for(reg int i=len,tmp=0;i>=2;--i){
		tmp=add(tmp,mul(str[i]-'0',basep[len-i]));
		ans=add(ans,mul(tmp,i-1));
	}
	printf("%d\n",ans);
	return 0;
}