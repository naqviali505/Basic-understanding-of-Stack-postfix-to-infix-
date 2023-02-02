#include<iostream>
#include<fstream>
using namespace std;
template<typename T>
class Node
{
	T data;
	Node* next;
public:
	Node()
	{
		next = nullptr;
	}

	~Node()
	{
		if (next != NULL)
		{
			next->setnext(NULL);
			delete next;
			next = NULL;
		}
	}
	void setdata(T d)
	{
		data = d;
	}
	T getdata()
	{
		return data;
	}
	Node* getnext()
	{
		return next;
	}
	void setnext(Node* n)
	{
		next = n;
	}
};
template<typename T>
class Stack
{
	Node<T>* top;
public:
	bool Push(T val)
	{
		Node<T>* temp = new Node<T>;
		temp->setdata(val);
		temp->setnext(top);
		top = temp;
		return true;
	}
	bool Pop(T& newval)
	{
		if (!isEmpty())
		{
			Node<T>* temp = top;
			top = top->getnext();
			newval = temp->getdata();
			temp->setnext(NULL);
			delete temp;
			temp = top;
			return true;
		}
		return false;
	}
	bool isEmpty()
	{
		if (top==NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	T Top()
	{
		Node<T>* temp = top;
		if (temp!=NULL)
		{
			return temp->getdata();
		}
		return false;
	}
	Stack()
	{
		top = nullptr;
	}
	~Stack()
	{
		if (top != NULL)
		{
			top->setnext(NULL);
			delete top;
			top = NULL;
		}
	}
	void print()
	{
		Node<T>* temp = top;
		while (temp != NULL)
		{
			cout << temp->getdata()<<" ";
			temp = temp->getnext();
		}
		cout << endl;
	}
};
void evaluation(char temp[])
{
	Stack<float> s;
	int i = 0;
	char e = 0;
	float value = 0;
	float op1 = 0, op2 = 0;
	while (temp[i] != NULL)
	{
		e = temp[i];
		if (e != '+' && e != '-' && e != '*' && e != '/' && e != '^')
		{
			e = e - 48;
			s.Push(e);
		}
		else
		{
			s.Pop(op2);
			s.Pop(op1);
			if (e == '+')
			{
				value = op1+op2;
			}
			if (e == '-')
			{
					value = op1 - op2;
			}
			if (e == '*')
			{
				value = op1 *op2;
			}
			if (e == '/')
			{
				value = op1/op2;
			}
			if (e == '^')
			{
				value = pow(op1, op2);
			}
			s.Push(value);
		}
		i++;
	}
	s.Pop(value);
	cout << "The postfix's expression's evaluated value is "<<value << endl;
}
bool prcd(char op1, char op2)
{
	if ((op1 == '+' || op1 == '-' || op1 == '*' || op1 == '/') && op2 == '(')
		return false;
	if (op1 == '+' && op2 == '+')
		return true;
	if (op1 == '-' && op2 == '-')
		return true;
	if (op1 == '-' && op2 == '+')
		return true;
	if (op1 == '+' && op2 == '-')
		return true;
	if (op1 == '/' && op2 == '/')
		return true;
	if (op1 == '/' && (op2 == '-' || op2 == '+'))
		return true;
	if (op1 == '*' && (op2 == '+' || op2 == '-'))
		return true;
	if ((op1 == '-' || op1 == '+') && (op2 == '*' || op2 == '/'))
		return false;
	if (( op1 == '+') && (op2 == '*' || op2 == '/' || op2 == '-'))
		return false;
	if ((op1 == '-' || op1 == '+' || op1 == '*' || op1 == '/') && op2 == '^')
		return false;
	if (op1 == '^' && (op2 == '+' || op2 == '*' || op2 == '/' || op2 == '-'))
		return true;
}
void conversion()
{
	ifstream infile;
	char var = 0, pop_var1 = 0;
	Stack<char> s;
	char postfix[30];
	int i = 0;
	infile.open("infix.txt");
	if (infile.is_open())
	{
		cout << "The infix expression is ";
			while (infile >> var)
		{
			
			if (var != '+' && var != '-' && var != '*' && var != '/' && var != '^')
			{
				postfix[i++] = var;
			}
			else
			{
				while (!s.isEmpty() && prcd(s.Top(), var))
				{
					s.Pop(pop_var1);
					postfix[i++] = pop_var1;
				}
				if (s.isEmpty() || var != ')')
				{
					s.Push(var);
				}
				else
				{
					s.Pop(pop_var1);
				}
			}
			cout << var;
		}
	}
	cout << endl;
	infile.close();
	while (!s.isEmpty())
	{
		s.Pop(pop_var1);
		postfix[i++]=pop_var1;
	}
	postfix[i++] = '\0';
	cout << "Postfix expression is "<<postfix<< endl;
	evaluation(postfix);
}
int main()
{
	conversion();
	return 0;
}