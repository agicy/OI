#include<bits/stdc++.h>
using namespace std;
#define register
typedef long long ll;
inline int read(void){
	bool f=false;
	char ch=getchar();
	int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXS=1e5+5;

int w[26];
char s[MAXS];

inline bool A(int x){
	return x&1;
}

inline bool N(int x){
	return (x&2);
}

inline bool V(int x){
	return (x&4);
}

bool pre[MAXS],suf[MAXS];

int main(void){
	int T=read();
	while(T--){
		for(int i=0;i<26;++i)
			w[i]=read();
		scanf("%s",s+1);
		int n=strlen(s+1);
		bool flag=false;
		pre[0]=true;
		for(int i=1;i<=n;++i)
			if(!A(w[s[i]-'a'])&&!N(w[s[i]-'a']))
				pre[i]=false;
			else
				pre[i]=pre[i-1];
		suf[n+1]=true;
		for(int i=n;i>=1;--i)
			if(!A(w[s[i]-'a'])&&!N(w[s[i]-'a']))
				suf[i]=false;
			else
				suf[i]=suf[i+1];
		for(int i=1;i<=n;++i){
			if(i!=1&&i!=n&&V(w[s[i]-'a'])){
				if(pre[i-1]&&N(w[s[i-1]-'a'])&&suf[i+1]&&N(w[s[n]-'a'])){
					flag=true;
					break;
				}
			}
		}
		puts(flag?"Yes":"No");
	}
	return 0;
}