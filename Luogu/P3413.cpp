#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define MOD 1000000007

const int MAXSIZE=1000+5;

string l,r;
int len[MAXSIZE];
ll f[MAXSIZE][10][10];

inline ll DFS(reg int pos,reg int pre,reg int gpre,reg bool lim,reg bool zero){
	if(pos==0)
		return 1;
	if(f[pos][pre][gpre]!=-1&&!lim&&!zero&&pre!=-1&&gpre!=-1)
		return f[pos][pre][gpre];
	reg int up=lim?len[pos]:9;
	reg ll res=0;
	for(reg int i=0;i<=up;++i)
		if(i!=pre&&i!=gpre&&!zero)
			res=(res+DFS(pos-1,i,pre,lim&&i==len[pos],false))%MOD;
		else if(zero)
			res=(res+DFS(pos-1,(i==0&&zero)?-1:i,-1,lim&&i==len[pos],i==0&&zero))%MOD;
	if(!lim&&!zero&&pre!=-1&&gpre!=-1)
		return f[pos][pre][gpre]=res;
	else
		return res;
}

inline ll solve(void){
	for(reg int i=0,size=l.size();i<size;++i)
		len[size-i]=l[i]-'0';
	reg int ans1=DFS(l.size(),-1,-1,1,1);
	for(reg int i=0,size=r.size();i<size;++i)
		len[size-i]=r[i]-'0';
	reg int ans2=DFS(r.size(),-1,-1,1,1);
	for(reg int i=2,size=l.size();i<=size;++i)
		if(l[i]==l[i-1]||(l[i]==l[i-2]&&i>=3))
			return (ans2-ans1+MOD)%MOD;
	return (ans2-ans1+1+MOD)%MOD;
}

int main(void){
	cin>>l>>r;
	memset(f,-1,sizeof(f));
	reg ll numl=0,numr=0;
	for(reg int i=0,size=l.size();i<size;++i)
		numl=(numl*10+l[i]-'0')%MOD;
	for(reg int i=0,size=r.size();i<size;++i)
		numr=(numr*10+r[i]-'0')%MOD;
	printf("%lld\n",((numr-numl-solve()+1)%MOD+MOD)%MOD);
	return 0;
}