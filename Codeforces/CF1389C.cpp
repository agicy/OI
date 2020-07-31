#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXSIZE=2e5+5;

char str[MAXSIZE];

int main(void){
	int t;
	scanf("%d",&t);
	while(t--){
		scanf("%s",str);
		reg int len=strlen(str);
		int i[2];
		int ans=len;
		for(i[0]='0';i[0]<='9';++i[0])
			for(i[1]='0';i[1]<='9';++i[1]){
				reg int p=0,cnt=0;
				for(reg int j=0;j<len;++j)
					if(str[j]==i[p]){
						++cnt;
						p=1-p;
					}
				if(i[0]!=i[1]&&(cnt&1))
					--cnt;
				ans=min(ans,len-cnt);
			}
		printf("%d\n",ans);
	}
	return 0;
}