#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXS=1e3+5;

char f[MAXS],g[MAXS];
int lenf,leng;

namespace Subtask3{
	inline ll gcd(reg ll a,reg ll b){
		return b?gcd(b,a%b):a;
	}
	pair<ll,int> num[MAXS];
	char opt[MAXS];
	inline pair<ll,int> solve(reg char str[],reg int len){
		reg int topN=0,topO=0;
		for(reg int i=1;i<=len;++i){
			if(str[i]=='x'){
				num[++topN]=make_pair(1ll,1);
			}
			else{
				if(str[i]=='*'){
					opt[++topO]='*';
				}
				else{
					while(topO&&opt[topO]=='*'){
						pair<ll,int> p1=num[topN--];
						pair<ll,int> p2=num[topN--];
						num[++topN]=make_pair(p1.first*p2.first,p1.second+p2.second);
						--topO;
					}
					opt[++topO]='+';
				}
			}
		}
		while(topO){
			if(opt[topO]=='*'){
				pair<ll,int> p1=num[topN--];
				pair<ll,int> p2=num[topN--];
				num[++topN]=make_pair(p1.first*p2.first,p1.second+p2.second);
			}
			else{
				pair<ll,int> p1=num[topN--];
				pair<ll,int> p2=num[topN--];
				if(p1.second<p2.second)
					swap(p1,p2);
				if(p1.second==p2.second)
					num[++topN]=make_pair(p1.first+p2.first,p1.second);
				else
					num[++topN]=make_pair(p1.first,p1.second);
			}
			--topO;
		}
		assert(topN==1);
		return num[topN];
	}
	inline void Solve(void){
		pair<ll,int> F=solve(f,lenf),G=solve(g,leng);
		if(F.second==G.second){
			reg ll d=gcd(F.first,G.first);
			printf("%lld/%lld\n",F.first/d,G.first/d);
		}
		else if(F.second>G.second)
			puts("1/0");
		else
			puts("0/1");
		return;
	}
}

namespace Subtask4{
	namespace BigNumberNAME{
		const int BASE=10;
		struct BigNumber{
			vector<int> unit;
			inline int size(void)const{
				return unit.size();
			}
			inline BigNumber(reg int x=0){
				if(!x){
					unit.resize(1);
					unit[0]=0;
				}
				else{
					reg int cnt=0,tmp=x;
					while(tmp){
						++cnt;
						tmp/=BASE;
					}
					unit.resize(cnt);
					reg int bas=1;
					for(reg int i=0;i<cnt;++i){
						unit[i]=(x/bas)%BASE;
						bas*=BASE;
					}
				}
				return;
			}
		};
		inline void print(const BigNumber& a){
			for(reg int i=a.size()-1;i>=0;--i)
				putchar('0'+a.unit[i]);
			return;
		}
		inline BigNumber operator+(BigNumber a,BigNumber b){
			a.unit.resize(max(a.size(),b.size())+1);
			for(reg int i=0,siz=b.size();i<siz;++i)
				a.unit[i]+=b.unit[i];
			for(reg int i=0,siz=a.size();i<siz-1;++i)
				if(a.unit[i]>=BASE){
					a.unit[i+1]+=a.unit[i]/BASE;
					a.unit[i]%=BASE;
				}
			while(a.size()>1&&a.unit.back()==0)
				a.unit.pop_back();
			return a;
		}
		inline bool operator>=(const BigNumber& a,const BigNumber& b){
			if(a.size()>b.size())
				return true;
			if(a.size()<b.size())
				return false;
			for(reg int i=a.size()-1;i>=0;--i){
				if(a.unit[i]>b.unit[i])
					return true;
				if(a.unit[i]<b.unit[i])
					return false;
			}
			return true;
		}
		inline BigNumber operator-(BigNumber a,BigNumber b){
			assert(a>=b);
			for(reg int i=0,siz=b.size();i<siz;++i)
				a.unit[i]-=b.unit[i];
			for(reg int i=0,siz=a.size();i<siz-1;++i)
				if(a.unit[i]<0){
					reg int cnt=(-a.unit[i]+BASE-1)/BASE;
					a.unit[i]+=cnt*BASE;
					a.unit[i+1]-=cnt;
				}
			while(a.size()>1&&a.unit.back()==0)
				a.unit.pop_back();
			return a;
		}
		inline bool iszero(const BigNumber& a){
			return a.size()==1&&a.unit[0]==0;
		}
		inline bool isEven(const BigNumber& a){
			return !(a.unit[0]&1);
		}
		inline BigNumber div2(BigNumber a){
			reg int res=0;
			for(reg int i=a.size()-1;i>=0;--i){
				reg int q=(res+a.unit[i])>>1;
				reg int r=(res+a.unit[i])-(q<<1);

				a.unit[i]=q;
				res=r*BASE;
			}
			while(a.size()>1&&a.unit.back()==0)
				a.unit.pop_back();
			return a;
		}
		inline BigNumber operator*(const BigNumber& a,const BigNumber& b){
			BigNumber res(0);
			res.unit.resize(a.size()+b.size());
			for(reg int i=0,siza=a.size();i<siza;++i)
				for(reg int j=0,sizb=b.size();j<sizb;++j)
					res.unit[i+j]+=a.unit[i]*b.unit[j];
			for(reg int i=0,siz=res.size();i<siz;++i)
				if(res.unit[i]>=BASE){
					res.unit[i+1]+=res.unit[i]/BASE;
					res.unit[i]%=BASE;
				}
			while(res.size()>1&&res.unit.back()==0)
				res.unit.pop_back();
			return res;
		}
		inline bool greater_eq(BigNumber a,BigNumber b,reg int last_dg,reg int len){
			if(last_dg+len<a.size()&&a.unit[last_dg+len]!=0)
				return true;
			for(reg int i=len-1;i>=0;--i){
				if(a.unit[last_dg+i]>b.unit[i])
					return true;
				if(a.unit[last_dg+i]<b.unit[i])
					return false;
			}
			return true;
		}
		inline BigNumber operator/(const BigNumber& a,const BigNumber& b){
			assert(!iszero(b));
			BigNumber c(0);
			c.unit.resize(a.size()-b.size()+1);
			BigNumber tmp=a;
			tmp.unit.resize(tmp.size()+1);
			for(reg int i=a.size()-b.size();i>=0;--i){
				while(greater_eq(tmp,b,i,b.size())){
					for(reg int j=0,siz=b.size();j<siz;++j){
						tmp.unit[i+j]-=b.unit[j];
						if(tmp.unit[i+j]<0){
							tmp.unit[i+j+1]-=1;
							tmp.unit[i+j]+=BASE;
						}
					}
					c.unit[i]+=1;
				}
			}
			while(c.size()>1&&c.unit.back()==0)
				c.unit.pop_back();
			return c;
		}
		inline BigNumber gcd(BigNumber a,BigNumber b){
			if(iszero(a))
				return b;
			if(iszero(b))
				return a;
			BigNumber res(1);
			reg int cnt=0;
			while(isEven(a)&&isEven(b))
				a=div2(a),b=div2(b),++cnt;
			if(!isEven(a)&&isEven(b))
				res=gcd(a,div2(b));
			else if(isEven(a)&&!isEven(b))
				res=gcd(div2(a),b);
			else{
				if(a>=b)
					res=gcd(b,a-b);
				else
					res=gcd(a,b-a);
			}
			if(!cnt)
				return res;
			else{
				BigNumber tim(1),x(2);
				while(cnt){
					if(cnt&1)
						tim=tim*x;
					x=x*x;
					cnt>>=1;
				}
				return res*tim;
			}
		}
	}
	using namespace BigNumberNAME;
	pair<BigNumber,int> num[MAXS];
	char opt[MAXS];
	inline pair<BigNumber,int> solve(reg char str[],reg int len){
		reg int topN=0,topO=0;
		for(reg int i=1;i<=len;++i){
			if(str[i]=='x')
				num[++topN]=make_pair(BigNumber(1),1);
			else{
				if(str[i]=='('){
					opt[++topO]='(';
				}
				else if(str[i]==')'){
					while(topO&&opt[topO]!='('){
						if(opt[topO]=='*'){
							pair<BigNumber,int> p1=num[topN--];
							pair<BigNumber,int> p2=num[topN--];
							num[++topN]=make_pair(p1.first*p2.first,p1.second+p2.second);
						}
						else{
							pair<BigNumber,int> p1=num[topN--];
							pair<BigNumber,int> p2=num[topN--];
							if(p1.second<p2.second)
								swap(p1,p2);
							if(p1.second==p2.second)
								num[++topN]=make_pair(p1.first+p2.first,p1.second);
							else
								num[++topN]=make_pair(p1.first,p1.second);
						}
						--topO;
					}
					--topO;
				}
				else if(str[i]=='*'){
					opt[++topO]='*';
				}
				else{
					while(topO&&opt[topO]=='*'){
						pair<BigNumber,int> p1=num[topN--];
						pair<BigNumber,int> p2=num[topN--];
						num[++topN]=make_pair(p1.first*p2.first,p1.second+p2.second);
						--topO;
					}
					opt[++topO]='+';
				}
			}
		}
		while(topO){
			if(opt[topO]=='*'){
				pair<BigNumber,int> p1=num[topN--];
				pair<BigNumber,int> p2=num[topN--];
				num[++topN]=make_pair(p1.first*p2.first,p1.second+p2.second);
			}
			else{
				pair<BigNumber,int> p1=num[topN--];
				pair<BigNumber,int> p2=num[topN--];
				if(p1.second<p2.second)
					swap(p1,p2);
				if(p1.second==p2.second)
					num[++topN]=make_pair(p1.first+p2.first,p1.second);
				else
					num[++topN]=make_pair(p1.first,p1.second);
			}
			--topO;
		}
		assert(topN==1);
		return num[topN];
	}
	inline void Solve(void){
		BigNumber tmp(1);
		pair<BigNumber,int> F=solve(f,lenf),G=solve(g,leng);
		if(F.second==G.second){
			BigNumber d=gcd(F.first,G.first);
			print(F.first/d),putchar('/'),print(G.first/d),putchar('\n');
		}
		else if(F.second>G.second)
			puts("1/0");
		else
			puts("0/1");
		return;
	}
}

int main(void){
	scanf("%s%s",f+1,g+1);
	lenf=strlen(f+1),leng=strlen(g+1);
	reg bool subtask3flag=true;
	for(reg int i=1;i<=lenf;++i)
		if(f[i]=='('||f[i]==')'){
			subtask3flag=false;
			break;
		}
	for(reg int i=1;i<=leng;++i)
		if(g[i]=='('||g[i]==')'){
			subtask3flag=false;
			break;
		}
	if(subtask3flag)
		//puts("S3"),
		Subtask3::Solve();
	else
		//puts("S4"),
		Subtask4::Solve();
	return 0;
}