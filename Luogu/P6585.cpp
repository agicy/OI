#include<bits/stdc++.h>
using namespace std;
#define reg register

const int MAXN=2048+5;

int n,task_id;
int a[MAXN];
int tag,L,R;

inline bool judge(reg int i){
	return a[i]==0&&a[i+1]*a[i-1]>=0;
}

inline bool check(void){
	for(reg int i=1;i<=n;++i)
		if(judge(i))
			return true;
	return false;
}

inline bool find(void){
	for(reg int i=L;i<=R;++i)
		if(judge(i)){
			if(a[i-1]!=0)
				a[i]=a[i-1];
			else if(a[i+1]!=0)
				a[i]=a[i+1];
			else
				a[i]=tag;
			cout<<i<<' '<<a[i]<<endl;
			return true;
		}
	return false;
}

int main(void){
	cin>>n>>task_id;
	int order=1;
	cout<<order<<endl;
	if(n==1)
		return 0;
	else if(!(n&1))
		while(true){
			static int place,type;
			cin>>place>>type;
			a[place]=a[n-place+1]=type;
			cout<<n-place+1<<' '<<type<<endl;
			if(!check())
				return 0;
		}
	else{
		static int place,type;
		L=n/2,R=n/2+2;
		cin>>place>>type;
		tag=type;
		if(n-place+1==place){
			a[place]=type;
			a[L]=type;
			cout<<L<<' '<<type<<endl;
			if(L>1)
				--L,++R;
			while(true){
				cin>>place>>type;
				a[place]=type;
				if(L<=place&&place<=R){
					find();
					if(a[L]!=0||a[R]!=0)
						if(L>1)
							--L,++R;
				}
				else{
					a[n-place+1]=-type;
					cout<<n-place+1<<' '<<-type<<endl;
					L=min(place,n-place+1);
					R=max(place,n-place+1);
					cin>>place>>type;
					break;
				}
				if(!check())
					return 0;
			}
		}
		while(true){
			a[place]=type;
			if(L<=place&&place<=R)
				find();
			else{
				a[n-place+1]=-type;
				cout<<n-place+1<<' '<<-type<<endl;
				L=min(place,n-place+1);
				R=max(place,n-place+1);
			}
			if(!check())
				return 0;
			cin>>place>>type;
		}
	}
	return 0;
}