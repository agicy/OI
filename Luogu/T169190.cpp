#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXS=(1<<24)+1;
const int MAXLEN=24;

char str[MAXS];
int len;

inline int get(reg int x){
	return (1<<x)-1;
}

bitset<1<<MAXLEN> M;

inline bool check(reg int l){
	M.reset();
	reg int val=0;
	reg int U=(1<<l)-1;
	for(reg int i=0;i<len;++i){
		val=((val<<1)|(str[i]^'0'))&U;
		if(i>=l-1)
			M[val]=true;
	}
	return M.count()!=(1u<<l);
}

inline int getAns(reg int l){
	M.reset();
	reg int val=0;
	reg int U=(1<<l)-1;
	for(reg int i=0;i<len;++i){
		val=((val<<1)|(str[i]^'0'))&U;
		if(i>=l-1)
			M[val]=true;
	}
	return (~M)._Find_first();
}

int main(void){
	scanf("%s",str);
	len=strlen(str);
	reg int l=1,r=min(24,(int)(log2(len))+1),mid;
	while(l<r){
		mid=(l+r)>>1;
		if(check(mid))
			r=mid;
		else
			l=mid+1;
	}
	reg int x=getAns(l);
	for(reg int i=l-1;i>=0;--i)
		putchar(((x>>i)&1)^'0');
	puts("");
	return 0;
}