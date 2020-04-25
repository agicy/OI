#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=40000000+5;
const int MAXM=100000+5;
const int MAXSIZE=11;
const int BASE=10000;
const int LGBASE=4;

struct BigNumber{
	int len;
	int unit[MAXSIZE];
	inline BigNumber(void){
		len=1;
		memset(unit,0,sizeof(unit));
		return;
	}
	inline BigNumber(reg ll a){
		reg int i;
		for(i=0;a!=0&&i<MAXSIZE;++i){
			unit[i]=a%BASE;
			a/=BASE;
		}
		len=i-1;
		return;
	}
	inline void Fresh(void){
		reg int i;
		for(i=0;i<MAXSIZE-1;++i)
			if(unit[i]>=BASE){
				unit[i+1]+=unit[i]/BASE;
				unit[i]%=BASE;
			}
		for(i=MAXSIZE-1;i>=0;--i)
			if(unit[i]){
				len=i;
				break;
			}
		if(i==-1)
			len=1;
		return;
	}
	inline void Add(const BigNumber& a){
		reg int i,l;
		for(i=0,l=max(len,a.len);i<=l;++i)
			unit[i]+=a.unit[i];
		Fresh();
		return;
	}
	inline void Mul(const BigNumber& a){
		reg int i;
		BigNumber res;
		for(i=0;i<=len;++i)
			for(reg int j=0;j<=a.len;++j)
				res.unit[i+j]+=unit[i]*a.unit[j];
		*this=res;
		Fresh();
		return;
	}
	inline void Opt(reg ll a){
		BigNumber temp(a);
		temp.Mul(temp);
		this->Add(temp);
		return;
	}
	inline void Print(void){
		reg int i;
		printf("%d",unit[len]);
		for(i=len-1;i>=0;--i)
			printf("%0*d",LGBASE,unit[i]);
		putchar('\n');
		return;
	}
};

int n,m,type;
ll a[MAXN];
ll *sum;
BigNumber ans;
int pre[MAXN];
int head,tail,Q[MAXN];

inline ll Calc(reg int);

int main(void){
	reg int i,j,now,head,tail;
	scanf("%d%d",&n,&type);
	if(type==0)
		for(i=1;i<=n;++i)
			scanf("%lld",&a[i]);
	else{
		static int x,y,z,b1,b2,b3,lastp=0,p,l,r;
		scanf("%d%d%d%d%d%d",&x,&y,&z,&b1,&b2,&m);
		for(i=1;i<=m;++i){
			scanf("%d%d%d",&p,&l,&r);
			for(j=lastp+1;j<=p;++j){
				switch(j){
					case 1:a[j]=b1%(r-l+1)+l;break;
					case 2:a[j]=b2%(r-l+1)+l;break;
					default:{
						b3=((ll)x*b2+(ll)y*b1+z)&0X000000003FFFFFFFll;
						a[j]=b3%(r-l+1)+l;
						b1=b2;
						b2=b3;
						break;
					}
				}
			}
			lastp=p;
		}
	}
	sum=a;
	for(i=1;i<=n;++i)
		sum[i]=sum[i-1]+a[i];
	head=tail=1;
	for(i=1;i<=n;++i){
		while(head<tail&&Calc(Q[head+1])<=sum[i])
			++head;
		pre[i]=Q[head];
		while(head<tail&&Calc(Q[tail])>=Calc(i))
			--tail;
		Q[++tail]=i;
	}
	now=n;
	while(now){
		ans.Opt(sum[now]-sum[pre[now]]);
		now=pre[now];
	}
	ans.Print();
	return 0;
}

inline ll Calc(reg int x){
	return (sum[x]<<1)-sum[pre[x]];
}
