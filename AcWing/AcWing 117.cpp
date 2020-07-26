#include<bits/stdc++.h>
using namespace std;
#define reg register

int num[128];
int cnt[128];

deque<char> Q[14];

int main(void){
	num['K']=13;
	num['A']=1;
	num['J']=11;
	num['Q']=12;
	num['0']=10;
	for(reg int i=2;i<=9;++i)
		num[i+'0']=i;
	for(reg int i=1;i<=13;++i)
		for(reg int j=1;j<=4;++j){
			static char x;
			cin>>x;
			Q[i].push_front(x);
		}
	for(reg int i=1;i<=4;++i){
		reg char now=Q[13].front();
		Q[13].pop_front();
		while(now!='K'){
			++cnt[(int)now];
			int temp=num[(int)now];
			Q[temp].push_back((char)now);
			now=Q[temp].front();
			Q[temp].pop_front();
		}
	}
	reg int ans=0;
	for(reg int i=32;i<=127;++i)
		if(cnt[i]==4)
			++ans;
	printf("%d\n",ans);
	return 0;
}
