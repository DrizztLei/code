//All now write down is the part of the code . So we'll done the code sonner or later .
/**template <class T>
void <T> insert(node * head , int i , T x)
{
	node * temp = head , * ptr;
	for(int k = 0 ; k < i ; k++) temp = temp -> next;
	ptr = new node;
	ptr -> date = x;
	ptr -> next = temp -> next;
	temp -> next = ptr;
}

template<class T>
void remove<T>(node * head , int i)
{
	node * temp = head;
	for(int k = 0 ; k < i ;k++) temp = temp -> next;
	node * need_delete = temp -> next;
	temp -> next = need_delete -> next;
	delete need_delete;
}

template<class T>
int length<T>(node * head)
{
	int length;
	node * temp = head;
	for(length = 0 ; temp ; length++){
		temp = temp->next;
	}
	return length;
}
template<class T>
void traverse<T>(node * head)
{
	node * temp = head;
	while(temp != null){
		cout << temp->data<<endl;
		temp = temp->next;
	}
}

template<T>
void clear<T>(node * head)
{
	node * temp;
	while(head)
		{
			temp = head;
			head = head->next;
			delete temp;
		}
}

template<class T>v
T Visit(node * head , int i)
{
	node * temp = head;
	for(int k = 0 ; k < i ;k++){
		temp = temp->next;
	}
	return temp->data;
}

template <class T>
T search(node * head , T x)
{
	node * temp = head;
	int index;
	for(index = 0;temp->data != x;index++)
		if((temp = temp-> next) == NULL ) return -1;
	return index;
}

template <class T>
T search(node * head , T x)
{
	node * p = head -> next;
	int i = 0;
	while(p != NULL && p->data != x) {
		p = p->next;
		++i;
	}
	if(p==NULL) return -1;
	else return i;
}
template <class T>
T next(node * head , T x)
{
	node * pos = head -> next;
	while(pos != NULL && pos -> data != x) pos = pos -> next;
	if(pos == NULL) {cout << x << " is not here ." << endl; return -1;}
	if(pos -> next == NULL) {cout << x << " 's next doesn\'t here ." << endl; return -1;}
	return pos->next->data;
}


*/

int main(int argc , char ** argv){
	return 0;
}
