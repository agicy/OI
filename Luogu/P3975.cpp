#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
using namespace std;

const int MAXN=500000+5;

char str[MAXN];

int T;

namespace SAM{
	struct Node{
		int dep,link,size;
		int next[26];
		#define dep(x) unit[(x)].dep
		#define link(x) unit[(x)].link
		#define size(x) unit[(x)].size
		#define next(x) unit[(x)].next
	};
	int tot,last;
	Node unit[MAXN<<1];
	inline void Init(void){
		tot=last=1;
		return;
	}
	inline void insert(reg int ch){
		reg int np=++tot,p=last;
		dep(np)=dep(p)+1;
		size(np)=1;
		while(p&&next(p)[ch]==0){
			next(p)[ch]=np;
			p=link(p);
		}
		if(!p)
			link(np)=1;
		else{
			reg int q=next(p)[ch];
			if(dep(p)+1==dep(q))
				link(np)=q;
			else{
				reg int nq=++tot;
				memcpy(next(nq),next(q),sizeof(next(q)));
				link(nq)=link(q);
				dep(nq)=dep(p)+1;
				while(p&&next(p)[ch]==q){
					next(p)[ch]=nq;
					p=link(p);
				}
				link(np)=link(q)=nq;
			}
		}
		last=np;
		return;
	}
	int t[MAXN<<1],A[MAXN<<1];
	ll sum[MAXN<<1];
	inline void build(void){
		for(reg int i=1;i<=tot;++i)
			++t[dep(i)];
		for(reg int i=1;i<=tot;++i)
			t[i]+=t[i-1];
		for(reg int i=1;i<=tot;++i)
			A[t[dep(i)]--]=i;
		for(reg int i=tot;i>=1;--i)
			size(link(A[i]))+=size(A[i]);
		for(reg int i=1;i<=tot;++i)
			if(!T)
				sum[i]=size(i)=1;
			else
				sum[i]=size(i);
		size(1)=sum[1]=0;
		for(reg int i=tot;i>=1;--i)
			for(reg int j=0;j<26;++j)
				if(next(A[i])[j])
					sum[A[i]]+=sum[next(A[i])[j]];
		return;
	}
	inline void Print(reg int p,reg int k){
		if(k<=size(p))
			return;
		k-=size(p);
		for(reg int i=0;i<26;++i)
			if(next(p)[i]){
				if(k>sum[next(p)[i]])
					k-=sum[next(p)[i]];
				else{
					putchar(i+'a');
					Print(next(p)[i],k);
					break;
				}
			}
		return;
	}
}

int K;
using namespace SAM;

int main(void){
	scanf("%s%d%d",str+1,&T,&K);
	reg int len=strlen(str+1);
	Init();
	for(reg int i=1;i<=len;++i)
		insert(str[i]-'a');
	build();
	if(sum[1]<K)
		puts("-1");
	else
		Print(1,K),puts("");
	return 0;
}