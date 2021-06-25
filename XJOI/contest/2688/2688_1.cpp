#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

const int mod=1e9+7;

struct modInt{
	int x;
	inline modInt(reg int x=0):x(x){
		assert(0<=x&&x<mod);
		return;
	}
	inline modInt operator+(const modInt& a)const{
		reg int sum=x+a.x;
		return sum>=mod?sum-mod:sum;
	}
	inline modInt operator-(const modInt& a)const{
		reg int sum=x-a.x;
		return sum<0?sum+mod:sum;
	}
	inline modInt operator-(void)const{
		return modInt(0)-*this;
	}
	inline modInt operator*(const modInt& a)const{
		return 1ll*x*a.x%mod;
	}
	inline void operator+=(const modInt& a){
		x+=a.x;
		if(x>=mod) x-=mod;
		return;
	}
	inline void operator-=(const modInt& a){
		x-=a.x;
		if(x<0) x+=mod;
		return;
	}
	inline void operator*=(const modInt& a){
		x=1ll*x*a.x%mod;
		return;
	}
};

inline modInt fpow(modInt x,reg int exp){
	modInt res=1;
	while(exp){
		if(exp&1)
			res*=x;
		x*=x,exp>>=1;
	}
	return res;
}

const int MAXS=100+5;

string str;
int n;
int val[128];
int topO,Opt[MAXS];
int topN,Num[MAXS];

inline bool check(void){
	topO=topN=0;
	reg int len=str.length();
	for(reg int i=0;i<len;++i){
		switch(str[i]){
			case ' ':{
				break;
			}
			case '(':{
				Opt[++topO]='(';
				break;
			}
			case '<':{
				Opt[++topO]='<';
				break;
			}
			case '&':{
				while(topO&&Opt[topO]=='<'){
					reg int rig=Num[topN--];
					reg int lef=Num[topN--];
					reg int val=(lef<rig);
					--topO;
					Num[++topN]=val;
				}
				Opt[++topO]='&';
				break;
			}
			case '|':{
				while(topO&&Opt[topO]=='<'){
					reg int rig=Num[topN--];
					reg int lef=Num[topN--];
					reg int val=(lef<rig);
					--topO;
					Num[++topN]=val;
				}
				while(topO&&Opt[topO]=='&'){
					reg int rig=Num[topN--];
					reg int lef=Num[topN--];
					reg int val=(lef&&rig);
					--topO;
					Num[++topN]=val;
				}
				Opt[++topO]='|';
				break;
			}
			case ')':{
				while(topO&&Opt[topO]=='<'){
					reg int rig=Num[topN--];
					reg int lef=Num[topN--];
					reg int val=(lef<rig);
					--topO;
					Num[++topN]=val;
				}
				while(topO&&Opt[topO]=='&'){
					reg int rig=Num[topN--];
					reg int lef=Num[topN--];
					reg int val=(lef&rig);
					--topO;
					Num[++topN]=val;
				}
				while(topO&&Opt[topO]=='|'){
					reg int rig=Num[topN--];
					reg int lef=Num[topN--];
					reg int val=(lef|rig);
					--topO;
					Num[++topN]=val;
				}
				//assert(topO&&Opt[topO]=='(');
				--topO;
				break;
			}
			case 'a' ... 'g':{
				Num[++topN]=val[(int)str[i]];
				break;
			}
		}
	}
	while(topO&&Opt[topO]=='<'){
		reg int rig=Num[topN--];
		reg int lef=Num[topN--];
		reg int val=(lef<rig);
		--topO;
		Num[++topN]=val;
	}
	while(topO&&Opt[topO]=='&'){
		reg int rig=Num[topN--];
		reg int lef=Num[topN--];
		reg int val=(lef&rig);
		--topO;
		Num[++topN]=val;
	}
	while(topO&&Opt[topO]=='|'){
		reg int rig=Num[topN--];
		reg int lef=Num[topN--];
		reg int val=(lef|rig);
		--topO;
		Num[++topN]=val;
	}
	//assert(!topO);
	//assert(topN==1);
	return Num[topN];
}

int p[7];
modInt binom[8];

bool ed;

int main(void){
	getline(cin,str,'\n');
	cin>>n;
	binom[0]=1;
	for(reg int i=1;i<=min(7,n);++i)
		binom[i]=binom[i-1]*modInt(n-i+1)*fpow(i,mod-2);
	for(reg int i=0;i<7;++i)
		p[i]=i;
	modInt ans=0;
	do{
		for(reg int S=0;S<(1<<6);++S){
			reg bool flag=true;
			reg int cnt=0;
			val[p[0]+'a']=++cnt;
			for(reg int i=0;i<6;++i)
				if((S>>i)&1){
					if(p[i]>p[i+1]){
						flag=false;
						break;
					}
					val[p[i+1]+'a']=cnt;
				}
				else
					val[p[i+1]+'a']=++cnt;
			if(flag&&check()&&1<=cnt&&cnt<=n)
				ans+=binom[cnt];
		}
	}while(next_permutation(p,p+7));
	printf("%d\n",ans.x);
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}