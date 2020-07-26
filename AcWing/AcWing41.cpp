class MinStack {
public:
	stack<int> S,Smin;
	MinStack() {
		while(!S.empty())
			S.pop();
		while(!Smin.empty())
			Smin.pop();
		return;
	}

	void push(int x){
		S.push(x);
		if(!Smin.empty())
			Smin.push(min(Smin.top(),x));
		else
			Smin.push(x);
		return;
	}

	void pop() {
		S.pop();
		Smin.pop();
		return;
	}

	int top() {
		return S.top();
	}

	int getMin() {
		return Smin.top();
	}
};