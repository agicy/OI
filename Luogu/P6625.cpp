#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=100000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	fclose(stdin);
	fclose(stdout);
	return 0;
}

int n;
int a[MAXN];

inline void Read(void){
	scanf("%d",&n);
	for(reg int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	return;
}

inline void Work(void){
	reg ll ans=0,sum=0;
	reg int last=0;
	for(reg int i=1;i<=n;++i){
		reg int len=i-last;
		sum+=a[i];
		if(len>=2&&sum>=0){
			last=i-1;
			ans+=sum;
		}
	}
	printf("%lld\n",ans);
	return;
}