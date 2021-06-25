#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

const int MAXN=500;

int n;
int p[MAXN];

int main(void){
	reg int t=read();
	while(t--){
		n=read();
		for(reg int i=0;i<n;++i)
			p[i]=read()-1;
		vector<int> ans;
		for(int i=0;i<n;++i){
			reg int j=find(p,p+n,i)-p;
			if(i!=j){
				if(!((j^ans.size())&1)){
					if(j>=i+2){
						ans.push_back(j-2);
						swap(p[j-2],p[j-1]);
					}
					else{
						ans.push_back(i-1),ans.push_back(i),ans.push_back(i-1),ans.push_back(i),ans.push_back(i-1);
						swap(p[i],p[j]);
						continue;
					}
				}
				for(int k=j-1;k>=i;--k){
					ans.push_back(k);
					swap(p[k],p[k+1]);
				}
			}
		}
		write(ans.size()),putchar('\n');
		if(ans.size())
			for(reg int i=0,siz=ans.size();i<siz;++i)
				write(ans[i]+1),putchar(i==siz-1?'\n':' ');
		else
			putchar('\n');
	}
	flush();
	return 0;
}