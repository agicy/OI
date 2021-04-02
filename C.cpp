//看不到 QQ 怎么办啊 /kel

#ifdef LAL
#include"hpmq.h"
#endif

#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

class Data{
	friend class Operation;
	friend int main();
  private:
	unsigned int x,sz,T,flag;
	void read();
  public:
	void add_eq(const Data &a);
	void add(const Data &a,const Data &b);
	void clr();
	void print()const;
	bool empty()const;
};

class Operation{
	friend int main();
  private:
	unsigned int a,b,L,R,flag;
	void read();
  public:
	void apply(Data &w)const;
	void apply(Operation &w)const;
	void clr();
	bool empty()const;
};

void solve(
	const int n,
	const int m,
	const int *x,
	const int *y,
	const Data *d,
	const int *a,
	const int *b,
	const int *c,
	const Operation *o){
	vector<Data> tmpd;
	tmpd.resize(n);
	for(reg int i=0;i<n;++i)
		tmpd[i]=d[i];
	for(reg int j=0;j<m;++j){
		Data sj;
		sj.clr();
		for(reg int i=0;i<n;++i)
			if(1ll*a[j]*x[i]+1ll*b[j]*y[i]<c[j]){
				sj.add_eq(tmpd[i]);
				o[j].apply(tmpd[i]);
			}
		sj.print();
	}
	return;
}