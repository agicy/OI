#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXSIZE=100000+5;

int ans;
char S[MAXSIZE];
char S0[MAXSIZE];
int m;

int val[128];

namespace SAM{
	int tot,last;
	int dep[MAXSIZE<<1],link[MAXSIZE<<1],Next[MAXSIZE<<1][4];
	int cnt[MAXSIZE<<1];
	int c[MAXSIZE<<1];
	inline void Init(void){
		for(reg int i=1;i<=tot;++i)
			cnt[i]=dep[i]=link[i]=0,memset(Next[i],0,sizeof(Next[i]));
		tot=last=1;
		return;
	}
	inline int insert(reg int ch){
		reg int ID=++tot,pre=last;
		cnt[ID]=1;
		dep[ID]=dep[pre]+1;
		while(pre!=0&&Next[pre][ch]==0){
			Next[pre][ch]=ID;
			pre=link[pre];
		}
		if(pre==0)
			link[ID]=1;
		else{
			reg int q=Next[pre][ch];
			if(dep[pre]+1==dep[q])
				link[ID]=q;
			else{
				reg int clone=++tot;
				memcpy(Next[clone],Next[q],sizeof(Next[q]));
				dep[clone]=dep[pre]+1;
				link[clone]=link[q];
				link[ID]=link[q]=clone;
				while(pre!=0&&Next[pre][ch]==q){
					Next[pre][ch]=clone;
					pre=link[pre];
				}
			}
		}
		last=ID;
		return ID;
	}
	int a[MAXSIZE<<1];
	inline void build(void){
		memset(c,0,sizeof(c));
		for(reg int i=1;i<=tot;++i)
			++c[dep[i]];
		for(reg int i=1;i<=tot;++i)
			c[i]+=c[i-1];
		for(reg int i=1;i<=tot;++i)
			a[c[dep[i]]--]=i;
		for(reg int i=tot,p;i;--i)
			p=a[i],cnt[link[p]]+=cnt[p];
		return;
	}
	inline void query(reg int id,reg int len,reg int sum){
		if(len==m+1){
			ans+=cnt[id];
			return;
		}
		for(reg int i=0;i<4;++i)
			if(Next[id][i]){
				if(i==val[(int)S[len]])
					query(Next[id][i],len+1,sum);
				else if(sum<=2)
					query(Next[id][i],len+1,sum+1);
			}
		return;
	}
}

using namespace SAM;

int main(void){
	val['A']=0,val['C']=1,val['G']=2,val['T']=3;
	ios::sync_with_stdio(false);
	int T;
	cin>>T;
	while(T--){
		Init();
		cin>>(S0+1)>>(S+1);
		reg int len=strlen(S0+1);
		for(reg int i=1;i<=len;++i)
			insert(val[(int)S0[i]]);
		build();
		ans=0,m=strlen(S+1);
		query(1,1,0);
		printf("%d\n",ans);
	}
	return 0;
}