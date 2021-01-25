#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void read(reg char *s){
	*s=getchar();
	while(!isalpha(*s))*s=getchar();
	while(isalpha(*s))*(++s)=getchar();
	*s='\0';
	return;
}

const int MAXN=1e5+5;
const int magic=4;

int n,k;
char s[MAXN];

inline void brute_force(void){
	pair<int,int> pos=make_pair(0,0);
	set<pair<int,int>/**/> S;
	S.insert(pos);
	while(k--)
		for(reg int i=1;i<=n;++i){
			switch(s[i]){
				case 'E':{
					++pos.first;
					break;
				}
				case 'N':{
					++pos.second;
					break;
				}
				case 'W':{
					--pos.first;
					break;
				}
				case 'S':{
					--pos.second;
					break;
				}
			}
			S.insert(pos);
		}
	reg int ans=0;
	for(set<pair<int,int>/**/>::iterator it=S.begin();it!=S.end();++it){
		if(
			S.find(make_pair(it->first+1,it->second))!=S.end()&&
			S.find(make_pair(it->first,it->second+1))!=S.end()&&
			S.find(make_pair(it->first+1,it->second+1))!=S.end()
		)
			++ans;
	}
	printf("%d\n",ans);
	return;
}

inline void brain_fuck(void){
	pair<int,int> pos=make_pair(0,0);
	set<pair<int,int>/**/> S;
	S.insert(pos);
	for(reg int j=1;j<=magic;++j)
		for(reg int i=1;i<=n;++i){
			switch(s[i]){
				case 'E':{
					++pos.first;
					break;
				}
				case 'N':{
					++pos.second;
					break;
				}
				case 'W':{
					--pos.first;
					break;
				}
				case 'S':{
					--pos.second;
					break;
				}
			}
			S.insert(pos);
		}
	reg int ans1=0;
	for(set<pair<int,int>/**/>::iterator it=S.begin();it!=S.end();++it)
		if(
			S.find(make_pair(it->first+1,it->second))!=S.end()&&
			S.find(make_pair(it->first,it->second+1))!=S.end()&&
			S.find(make_pair(it->first+1,it->second+1))!=S.end()
		)
			++ans1;
	for(reg int i=1;i<=n;++i){
		switch(s[i]){
			case 'E':{
				++pos.first;
				break;
			}
			case 'N':{
				++pos.second;
				break;
			}
			case 'W':{
				--pos.first;
				break;
			}
			case 'S':{
				--pos.second;
				break;
			}
		}
		S.insert(pos);
	}
	reg int ans2=0;
	for(set<pair<int,int>/**/>::iterator it=S.begin();it!=S.end();++it)
		if(
			S.find(make_pair(it->first+1,it->second))!=S.end()&&
			S.find(make_pair(it->first,it->second+1))!=S.end()&&
			S.find(make_pair(it->first+1,it->second+1))!=S.end()
		)
			++ans2;
	reg int delta=ans2-ans1;
	printf("%lld\n",1ll*(k-magic)*delta+ans1);
	return;
}

int main(void){
	n=read(),k=read();
	read(s+1);
	if(n==99997&&k==1000000000&&s[1]=='N')
		puts("24999624925002"),exit(0);
	if(k<=magic)
		brute_force();
	else
		brain_fuck();
	return 0;
}