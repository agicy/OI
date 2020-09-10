#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXM=9999+5;

int m;
int ans[MAXM];
priority_queue<int> Q1;
priority_queue<int,vector<int>,greater<int>/**/> Q2;

int main(void){
	int p;
	scanf("%d",&p);
	while(p--){
		static int id;
		scanf("%d",&id);
		reg int cnt=0;
		while(!Q1.empty())Q1.pop();
		while(!Q2.empty())Q2.pop();
		scanf("%d",&m);
		for(reg int i=1;i<=m;++i){
			static int a;
			scanf("%d",&a);
			if(Q2.empty())
				Q2.push(a);
			else{
				if(a>Q2.top())
					Q2.push(a);
				else
					Q1.push(a);
				while(Q2.size()<Q1.size()){
					Q2.push(Q1.top());
					Q1.pop();
				}
				while(Q2.size()>Q1.size()+1){
					Q1.push(Q2.top());
					Q2.pop();
				}
			}
			if(i&1)
				ans[++cnt]=Q2.top();
		}
		printf("%d %d\n",id,(m+1)/2);
		for(reg int i=1;i<=cnt;++i)
			printf("%d%c",ans[i],i%10==0?'\n':' ');
		if(cnt%10!=0)
			putchar('\n');
	}
	return 0;
}