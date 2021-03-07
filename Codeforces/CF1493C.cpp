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

int n,k;
char s[MAXN];
int sum[26];
string now,ans;

inline bool dfs(reg int dep){
	if(dep==n){
		for(reg int i=0;i<26;++i)
			if(sum[i]%k)
				return false;
		ans=now;
		return true;
	}
	now+=s[dep];
	++sum[s[dep]-'a'];
	if(dfs(dep+1))
		return true;
	now=now.substr(0,dep);
	--sum[s[dep]-'a'];
	for(reg int i=s[dep]+1;i<='z';++i){
		++sum[i-'a'];
		reg int cnt=0;
		for(reg int j=0;j<26;++j)
			cnt+=(k-sum[j]%k)%k;
		if(dep+cnt<=n){
			ans=now;
			ans+=i;
			while(ans.size()+cnt<n)
				ans+='a';
			for(reg int j=0;j<26;++j){
				sum[j]=(k-sum[j]%k)%k;
				while(sum[j]--)
					ans+=('a'+j);
			}
			return true;
		}
		--sum[i-'a'];
	}
	return 0;
}


int main(void){
	reg int t=read();
	while(t--){
		now.clear(),ans.clear();
		memset(sum,0,sizeof(sum));
		n=read(),k=read(),read(s);
		if(n%k)
			puts("-1");
		else{
			dfs(0);
			cout<<ans<<endl;
		}
	}
	return 0;
}