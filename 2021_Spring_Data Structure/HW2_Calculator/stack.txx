//
// Assignment 2 : Simple calculator using Stack
//
// Array-based stack data structure
//
// COSE213 Spring 2021
//

template<class type>
Stack<type>::~Stack()
{
	delete [] array;
}

template<class type>
type& Stack<type>::Top()
{
	return array[top];
}

template<class type>
void Stack<type>::Push(const type& item)
{	
	int size = top + 1;
	if(size >= capacity){
		type* temp = array;
		capacity = 2 * size;
		array = new type[capacity];

		for(int i = 0; i < size; i++){
			array[i] = temp[i];
		}
		delete [] temp;
	}
	array[++top] = item;
	return;
}

template<class type>
void Stack<type>::Pop()
{
	if(IsEmpty()) return;
	top--;
	return;
}

template<class type>
bool Stack<type>::IsEmpty() const
{
	return top == -1;
}

