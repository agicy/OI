#include<bits/stdc++.h>
using namespace std;
#define reg register

const int MAXSIZE=500+5;
const int BASE=10;

int K;

struct Node{
	int len,unit[MAXSIZE];
	inline Node(void){
		len=1;
		memset(unit,0,sizeof(unit));
		return;
	}
	inline Node operator=(const Node& a){
		len=a.len;
		memcpy(unit,a.unit,sizeof(a.unit));
		return *this;
	}
	inline void Read(void){
		static char str[MAXSIZE];
		scanf("%s%d",str+1,&K);
		reg int l=strlen(str+1);
		for(reg int i=l;i>=1;--i)
			unit[l-i]=str[i]-'0';
		Fresh();
		return;
	}
	inline void Del(void){
		for(reg int i=K;i<MAXSIZE;++i)
			unit[i]=0;
		return;
	}
	inline void Fresh(void){
		for(reg int i=0;i<MAXSIZE-1;++i)
			if(unit[i]>=BASE){
				unit[i+1]+=unit[i]/BASE;
				unit[i]%=BASE;
			}
		Del();
		len=1;
		for(reg int i=MAXSIZE-1;i>=0;--i)
			if(unit[i]){
				len=i+1;
				return;
			}
		return;
	}
	inline Node operator*(const int x){
		Node res;
		res=*this;
		for(reg int i=0;i<res.len;++i)
			res.unit[i]*=x;
		res.Fresh();
		return res;
	}
	inline Node operator*(const Node &a){
		Node res;
		for(reg int i=0;i<len;++i)
			for(reg int j=0;j<a.len;++j)
				res.unit[i+j]+=unit[i]*a.unit[j];
		res.Fresh();
		return res;
	}
	inline void Print(void){
		for(reg int i=len-1;i>=0;--i)
			putchar(unit[i]+'0');
		putchar('\n');
		return;
	}
};

const int L[]={1,1,4,4,2,1,1,4,4,2};

inline Node pow(Node x,reg int exp){
	Node res;
	res.len=1,res.unit[0]=1;
	for(reg int i=1;i<=exp;++i)
		res=res*x;
	return res;
}

Node c,ans,p,q,d,b;

int main(void){
	c.Read();
	ans.unit[0]=L[c.unit[0]];
	ans.Fresh();
	b=c;
	for(reg int i=1;i<L[c.unit[0]];++i)
		b=b*c;
	q=p=b;
	reg int pos=2;
	while(pos<=K){
		b=c;
		reg int T=0;
		while(T<=10){
			++T;
			b=b*p;
			if(b.unit[pos-1]==c.unit[pos-1])
				break;
			q=q*p;
		}
		if(T>10){
			puts("-1");
			return 0;
		}
		p=q;
		ans=ans*T;
		++pos;
	}
	ans.Print();
	return 0;
}
