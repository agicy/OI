#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=5e4+5;
const int MAXK=5e4+5;

int n,k;
int a[MAXK];
int id[MAXN];
int ans[MAXN];

int main(void){
	n=read(),k=read();
	for(reg int i=0;i<k;++i)
		a[i]=read();
	for(reg int i=1;i<=n;++i)
		id[i]=i;
	reg int pre=1,suf=n,ptr=1;
	for(reg int i=0;i<n;++i){
		reg int pos=a[i%k]%(n-i);
		pos+=pre;
		if(id[pos]==ptr){
			ans[id[pos]]=pre;
			swap(id[pos],id[pre]);
			++pre;
			while(ans[ptr])
				++ptr;
		}
		else{
			ans[id[pos]]=suf;
			swap(id[pos],id[pre]);
			swap(id[pre],id[suf]);
			--suf;
		}
	}
	for(reg int i=1;i<=n;++i)
		printf("%d%c",ans[i],i==n?'\n':' ');
	return 0;
}