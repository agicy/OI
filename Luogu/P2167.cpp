#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=15+5;
const int MAXS=50+5;
const int p=1000003;

inline int lowbit(reg int x){
	return x&(-x);
}

inline int getCnt(reg int x){
	reg int res=0;
	while(x)
		++res,x^=lowbit(x);
	return res;
}

inline int add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=p?sum-p:sum;
}

int n,k;
char str[MAXN][MAXS];
int len;

int main(void){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&k);
		for(reg int i=0;i<n;++i)
			scanf("%s",str[i]+1);
		len=strlen(str[0]+1);
		for(reg int i=0;i<n;++i)
			printf("i=%d,",i),puts(str[i]+1);
		reg int U=(1<<n)-1;
		reg int ans=0;
		for(reg int S=0;S<=U;++S){
			reg int x=getCnt(S);
			if(x!=k&&x!=k+1)
				continue;
			static char tmp[MAXS];
			memset(tmp,-1,sizeof(tmp));
			reg bool flag=false;
			for(reg int i=0;i<n;++i)
				if((S>>i)&1)
					for(reg int j=1;j<=len;++j)
						if(str[i][j]!='?'&&str[i][j]!=tmp[j]){
							if(tmp[j]==-1)
								tmp[j]=str[i][j];
							else{
								flag=true;
								break;
							}
						}
			if(flag)
				continue;
			else{
				reg int sum=1;
				for(reg int i=1;i<=len;++i)
					if(tmp[i]==-1)
						sum=26ll*sum%p;
				if(x==k)
					ans=add(ans,sum);
				else
					ans=add(ans,p-sum);
				bitset<3> B;
				B=S;
				printf("S=");
				cout<<B;
				printf(",ans+=%d\n",x==k?sum:-sum);
				for(reg int i=1;i<=len;++i)
					if(tmp[i]==-1)
						putchar('?');
					else
						putchar(tmp[i]);
				puts("");
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}