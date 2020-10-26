#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXS=1e6+5;

char s[MAXS];
bool vis[MAXS];
stack<pair<char,int>/**/> S;

int main(void){
	scanf("%s",s);
	reg int len=strlen(s);
	for(int i=0;i<len;++i)
		if(!S.empty()&&((S.top().first=='['&&s[i]==']')||(S.top().first=='('&&s[i]==')'))){
			vis[S.top().second]=vis[i]=true;
			S.pop();
		}
		else
			S.push(make_pair(s[i],i));
	reg int ans=0,ptrl=0,ptrr=0,cnt=0;
	for(reg int i=0,las=0;i<len;++i)
		if(!vis[i])
			cnt=0,las=i+1;
		else{
			++cnt;
			if(cnt>ans)
				ans=cnt,ptrl=las,ptrr=i;
		}
	for(reg int i=ptrl;i<=ptrr;++i)
		putchar(s[i]);
	putchar('\n');
	return 0;
}