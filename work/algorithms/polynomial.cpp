#include <iostream>
#include <new>
using std::cout;
using std::cin;
using std::endl;

struct node{
	int coff , exp;
	node * next;
};

node * add (node * exp1 , node * exp2){
	node * res , * p , * tmp;
	res = p = new node;
	exp1 = exp1 -> next;
	exp2 = exp2 -> next;
	while(exp1 && exp2){
		p->next = new node;
		p=p->next;
		if(exp1->exp < exp2->exp){
			p->coff=exp1->coff;
			p->exp=exp1->exp;
			exp1=exp1->next;
		}
		else if(exp1->exp > exp2->exp){
			p->coff = exp2->coff;
			p->exp=exp2->exp;
			exp2=exp2->next;
		}else{
			p->coff=exp1->coff+exp2->coff;
			p->exp=exp2->exp;
			exp1=exp1->next;
			exp2=exp2->next;
		}
	}

	if(exp1==NULL)tmp=exp2;else tmp=exp1;
	while(tmp){
		p->next=new node;
		p=p->next;
		p->coff=tmp->coff;
		p->next=tmp->next;
		tmp=tmp->next;
	}
	return res;
}

int main(int argc ,char ** argv){
	return 0;
}
