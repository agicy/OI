#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=1e5+5;
const int MAXSQRTN=317+5;
const int MAXM=1e5+5;
const int MAXC=1e5+5;

int n,c,m;
int B;
int a[MAXN];
int top,S[MAXN];
int bl[MAXN],l[MAXSQRTN];
int cnt[MAXSQRTN][MAXC];
int T[MAXC];
int f[MAXSQRTN][MAXSQRTN];

int main(void){
	n=read(),c=read(),m=read();
	B=ceil(sqrt(n));
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<=n;++i){
		bl[i]=(i-1)/B+1;
		if(bl[i]!=bl[i-1])
			l[bl[i]]=i;
	}
	bl[n+1]=bl[n+1];
	l[bl[n+1]]=n+1;
	for(reg int i=1;i<=bl[n];++i){
		reg int t=0;
		for(reg int j=l[i];j<=n;++j){
			++cnt[i][a[j]];
			if((cnt[i][a[j]]&1)&&(cnt[i][a[j]]>1))
				--t;
			else if(!(cnt[i][a[j]]&1))
				++t;
			if(bl[j]!=bl[j+1])
				f[i][bl[j]]=t;
		}
	}
	reg int ans=0;
	while(m--){
		static int L,R;
		L=(read()+ans)%n+1,R=(read()+ans)%n+1;
		ans=0;
		if(L>R)
			swap(L,R);
		if(bl[L]==bl[R]){
			for(reg int i=L;i<=R;++i)
				++T[a[i]],S[++top]=a[i];
			while(top){
				if(T[S[top]]){
					ans+=!(T[S[top]]&1);
					T[S[top]]=0;
				}
				--top;
			}
		}
		else{
			if(bl[L]+1<=bl[R]-1)
				ans=f[bl[L]+1][bl[R]-1];
			for(reg int i=L;i<l[bl[L]+1];++i)
				++T[a[i]],S[++top]=a[i];
			for(reg int i=l[bl[R]];i<=R;++i)
				++T[a[i]],S[++top]=a[i];
			while(top){
				reg int t=S[top];
				if(T[t]){
					if((cnt[bl[L]+1][t]-cnt[bl[R]][t]>0)&&((cnt[bl[L]+1][t]-cnt[bl[R]][t])&1)==0&&(T[t]&1))
						--ans;
					else if(((cnt[bl[L]+1][t]-cnt[bl[R]][t]>0)&&((cnt[bl[L]+1][t]-cnt[bl[R]][t])&1))&&(T[t]&1))
						++ans;
					else if((cnt[bl[L]+1][t]==cnt[bl[R]][t])&&!(T[t]&1))
						++ans;
					T[t]=0;
				}
				--top;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}