#include<bits/stdc++.h>
#include "maze.h"
#define reg register

const int step=9;
const int MAXSTEP=step+5;

int S[MAXSTEP];

void findpath(int initialDeep, int T){
	reg int dep=initialDeep;
	reg int last=-1;
	move(0);
	if(dep>query())
		last=0;
	else{
		move(0),move(1);
		if(dep>query())
			last=1;
		else{
			move(1),move(2);
			last=2;
		}
	}
	--dep;
	while(dep){
		reg bool flag=false;
		S[0]=last;
		for(reg int i=1;i<=step;++i){
			do
				S[i]=rand()%3;
			while(S[i]==S[i-1]);
			flag=move(S[i]);
			if(flag)
				break;
		}
		if(flag)
			return;
		reg int tmp=query();
		for(reg int i=step;i>=0;--i){
			if(dep-i==tmp)
				break;
			move(S[i]);
			--tmp;
		}
		if(dep-tmp==step){
			last=(S[step]+1)%3;
			move(last);
			if(tmp<query()){
				move(last);
				last=(last+1)%3;
				move(last);
			}
		}
		else
			move(last=3-S[dep-tmp]-S[dep-tmp+1]);
		dep=tmp-1;
	}
	return;
}