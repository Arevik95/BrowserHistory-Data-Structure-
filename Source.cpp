#include <iostream>
#include <string>
#include <list>
using namespace std;



template <class T>
struct Node
{
  Node(T data) : data(data), next(NULL), prev(NULL) {}
  T data;
  Node * next;
  Node * prev;
};


template <class T>
class DoublyLinkedList
{
public:
  DoublyLinkedList() : head(NULL), tail(NULL) {}
  DoublyLinkedList(const DoublyLinkedList<T> & dll);
  ~DoublyLinkedList();
  Node <T> *  addNodeAfter(Node<T> *n,T data);
  void addNodeBefore(Node<T> *n,T data);
  void deleteNode(T data);
  Node<T>* get_head();
  Node<T>* get_tail();
  T get_hdata();
public:
  Node<T> * head;
  Node<T> * tail;
};


template <class T>
T DoublyLinkedList<T>::get_hdata()
{
	return head->prev->data;
};


template <class T>
Node<T>* DoublyLinkedList<T>::get_head()
{
	return head;
};


template <class T>
Node<T>* DoublyLinkedList<T>::get_tail()
{
	return tail;
};



template <class T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
  Node<T> * tmp = NULL;
  while (head)
    { 
      tmp = head;
      head = head->next;
      delete tmp;
    }
  head = tail = NULL;
}



template <class T>
Node <T> * DoublyLinkedList<T>::addNodeAfter(Node<T> *n,T data)
{
  Node<T> * t = new Node<T>(data);
  Node<T> *a;
  if (n == NULL)
    {
		head = new Node<T>(NULL);
		tail = new Node<T>(NULL);
		head->next =  t;
		tail->prev =t;
		t->next = tail;
		t->prev= head;
    }
  else
    {
		if(n->next=tail)
			tail->prev=t;
		a = n->next;
		n->next = t;
		a->prev = t;
		t->next = a;
		t->prev = n;
    }
  return t;
};


template <class T>
void DoublyLinkedList<T>::deleteNode(T data)
{
  Node<T> * tmp = head;
  while (tmp && tmp->data != data)
    {
      tmp = tmp->next;
    }

  if (tmp)
    {
      if (tmp->prev && tmp->next) // no change to head or tail
        {
          tmp->prev->next = tmp->next;
          tmp->next->prev = tmp->prev;
        }
      else if (tmp->prev) // change to tail
        {
          tmp->prev->next = tmp->next;
          tail = tmp->prev;
        }
      else if (tmp->next) // change to head
        {
          tmp->next->prev = tmp->prev;
          head = tmp->next;
        }

      delete tmp;
    }
}





template <class T>
class Vector
{
private:
	int m_size;
	T *m_array;
	int m_capacity;
	void resize();
public:
	Vector();
	~Vector();
	void insert(T m,int p);
	void pushback(T m);
	T get_el(int p);
};
//We should look how does the Vector:Insert work in stl

template <class T>
Vector<T>::Vector()
{
	m_capacity = 10;
	m_size = 0;
	m_array = new T[m_capacity];
};


template <class T>
Vector<T>::~Vector()
{
	m_capacity = 0;
	m_size = 0;
	delete [] m_array;
};


template <class T>
void Vector <T>::resize()
{
	m_capacity *=2;
	T *temp = new T[m_capacity];
	for(int i=0;i<m_size;i++)
		temp[i]=m_array[i];
	delete[] m_array;
	m_array=temp;
};
template <class T>
T Vector <T>::get_el(int p)
{
	return m_array[p];
};
template <class T>
void Vector <T>::pushback(T m)
{
	if(m_size>=m_capacity)
	{
		resize();
	}
		m_array[m_size]=m;
		m_size++;
};

template <class T>
void Vector <T>::insert(T m,int p)
{
	if(m_size>=m_capacity)
	{
		resize();
	}
	for(int i=m_size;i>=p;i--)
	{
		m_array[i+1]=m_array[i];
	}
	m_array[p] = m;
};


//We should create insert,remove,set,get,append,print,get:Size



template <class T>
class Stack
{
private:
	Vector<T> v;
	int top;
public:
	void push(T data);
    void pop();
	bool is_empty();
    T get_top();
	Stack();
	~Stack();
	void print();
};

template <class T>
Stack<T>::Stack()
{
	top = -1;
	//v = new Vector<int>;
}


template <class T>
Stack<T>::~Stack()
{
	v.~Vector();
	top = -1;
};


template <class T>
void Stack<T>::push(T data)
{
	v.pushback(data);
	top++;
};

template <class T>
void Stack<T>::pop()
{
	v.pushback(NULL);
	top--;
};


template <class T>
bool Stack<T>::is_empty()
{
	if (top==-1)
		return true;
	return false;
};

template <class T>
T Stack<T>::get_top()
{
	return v.get_el(top);
}

template <class T>
void Stack<T>::print()
{
	for(int i=top;i>=0;i--)
		cout<<v.get_el(i)<<' ';
	cout<<endl;
};




template <class T>
class Queue
{
private:
	DoublyLinkedList<T> list;
	Node<T> *front;
	Node<T> *rear;
public:
	void enqueue(T data);
    void dequeue();
    bool is_empty();
	Node<T>* get_front();
	Queue();
	~Queue();
	void print();
};

template <class T>
Queue<T>::Queue()
{
	front = NULL;
	rear = NULL;
};

template <class T>
Queue<T>::~Queue()
{
	list.~DoublyLinkedList();
	front = NULL;
	rear = NULL;
};


template <class T>
void Queue<T>::enqueue(T data)
{
	list.addNodeAfter(rear,data);
	front = list.get_tail()->prev;
	rear = list.get_head()->next;
};
template <class T>
void Queue<T>::dequeue()
{
	list.deleteNode(front->data);
	front = list.get_tail()->prev;
};


template <class T>
Node<T>* Queue<T>::get_front()
{
	return front;
};

template <class T>
bool Queue<T>::is_empty()
{
	if(front || rear)
		return true;
	return false;
}
template <class T>
void Queue<T>::print()
{
	while(front != rear)
	{
		cout<<front->data<<' ';
		front = front->prev;
	}
	cout<<endl;
}


int main()
{
	Stack<int> s;
	s.push(5);
	s.push(12);
	s.push(13);
	s.pop();
	s.print();
	Queue<int> q;
	q.enqueue(45);
	q.enqueue(23);
	q.enqueue(76);
	q.dequeue();
	q.print();
	return 0;

}