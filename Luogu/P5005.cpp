#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int mod=1e9+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

inline bool check(reg int S1,reg int S2,reg int S3){
	if((((S1&(~(S1<<1)))>>2)&S2)|(((S2&(~(S2<<1)))>>2)&S1)|(((S2&(~(S2<<1)))>>2)&S3)|(((S3&(~(S3<<1)))>>2)&S2)|(((S1&(~(S1>>1)))<<2)&S2)|(((S2&(~(S2>>1)))<<2)&S1)|(((S2&(~(S2>>1)))<<2)&S3)|(((S3&(~(S3>>1)))<<2)&S2)|(((S1&(~S2))>>1)&S3)|(((S1&(~S2))<<1)&S3)|(((S3&(~S2))>>1)&S1)|(((S3&(~S2))<<1)&S1))
		return false;
	else
		return true;
}

int x,y;
int f[2][1<<6][1<<6];

int main(void){
	scanf("%d%d",&x,&y);
	reg int U=(1<<y);
	for(reg int i=0;i<U;++i)
		f[0][i][0]=1;
	for(reg int i=0;i<U;++i)
		for(reg int j=0;j<U;++j)
			if(check(i,j,0))
				f[1][i][j]=add(f[1][i][j],f[0][j][0]);
	for(reg int i=2;i<x;++i){
		memset(f[i&1],0,sizeof(f[i&1]));
		for(reg int S1=0;S1<U;++S1)
			for(reg int S2=0;S2<U;++S2)
				for(reg int S3=0;S3<U;++S3)
					if(check(S1,S2,S3))
						f[i&1][S1][S2]=add(f[i&1][S1][S2],f[(i-1)&1][S2][S3]);
	}
	reg int ans=0;
	for(reg int i=0;i<U;++i)
		for(reg int j=0;j<U;++j)
			ans=add(ans,f[(x-1)&1][i][j]);
	printf("%d\n",ans);
	return 0;
}