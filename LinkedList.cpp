#include <iostream>
#include <vector>
#include <string>

using namespace std;



class MyList
{

private:

struct Node
{
	int data;
	Node* next;
};

	void erase() 
	{
		Node* toDelete = head;
		while (toDelete != nullptr)
		{
			Node* nextTodelete = toDelete->next;
			delete toDelete;
			toDelete = nextTodelete;
		}

		//Not neccessary
		head = nullptr;
		tail = nullptr;
		size = 0;
	}



	void deepCopyFrom(const MyList& other)
	{
		Node* current = other.head;
		while (current != nullptr)
		{
			this->pushBack(current->data);
			current = current->next;
		}
	}




public:


	Node* head = nullptr;
	Node* tail = nullptr;
	int size = 0;

	void pushBack(int data) 
	{
		Node* newNode = new Node();
		newNode->data = data;
		newNode->next = nullptr;

		if (head == nullptr)
		{
			head = newNode;
			tail = newNode;
		}
		else
		{
			tail->next = newNode;
			tail = newNode;
		}

		size++;

	}


	void print() const
	{
		if (head == nullptr)
		{					
			cout << "List is empty\n";
			return;
		}

		Node* current = head;

		while (current != nullptr) 
		{
			cout << current->data << " ";
			current = current->next;
		}

		cout << endl;

	}


	void insert(int data, int position = 0)
	{
		if (position < 0 || position > size)
		{
			cout << "Invalid position!" << endl;
			return;
		}

		Node* newNode = new Node();
		newNode->data = data;
		newNode->next = nullptr;

		if (position == 0)
		{
			newNode->next = head;
			head = newNode;

			if (size == 0)
			{
				tail = newNode;
			}
		}

		else
		{
			Node* current = head;
			for (int i = 0; i < position - 1; i++)
			{
				current = current->next;
			}

			newNode->next = current->next;
			current->next = newNode;

			if (newNode->next == nullptr)
			{
				tail = newNode;
			}
		}

		size++;

	}
	

	MyList()
	{
		head = nullptr;
		tail = nullptr;
		size = 0;
	}


	
	~MyList()
	{
		erase();
	}
	

	
	MyList(const MyList& other)
	{
		deepCopyFrom(other);
	}


	
	MyList& operator=(const MyList& other)
	{
		if (this == &other)
		{
			return *this;
		}
		//Delete existing
		this->erase();

		//Deep copy
		this->deepCopyFrom(other);
		return *this;
	}






	bool contains(int value) const
	{
		Node* current = head;
		while (current != nullptr)
		{
			if (current->data == value)
			{
				return true;
			}
			current = current->next;
		}
		return false;
	}

	


	int indexOf(int value) const
	{
		Node* current = head;
		int index = 0;

		while (current != nullptr)
		{
			if (current->data == value)
			{
				return index;
			}
			current = current->next;
			index++;
		}

		return -1;
	}


	void clear()
	{
		erase();
	}






	int getSize() const
	{
		return size;
	}





	void removeAt(int position)
	{
		if (position < 0 || position >= size)
		{
			cout << "Invalid position!" << endl;
			return;
		}

		Node* toDelete = nullptr;

		if (position == 0) 
		{
			toDelete = head;
			head = head->next;

			if (head == nullptr) 
			{
				tail = nullptr;
			}
		}

		else
		{
			Node* current = head;

			for (int i = 0; i < position - 1; i++)
			{
				current = current->next;
			}

			toDelete = current->next;
			current->next = toDelete->next;

			if (toDelete == tail) 
			{
				tail = current;
			}
		}

		delete toDelete;

		size--;
	}






	void removeFirst(int data)
	{
		if (head == nullptr)
		{
			cout << "Value not found!" << endl;
			return;
		}

		if (head->data == data) 
		{
			Node* toDelete = head;
			head = head->next;

			if (head == nullptr) 
			{
				tail = nullptr;
			}

			delete toDelete;
			size--;
			return;
		}

		Node* current = head;
		while (current->next != nullptr && current->next->data != data)
		{
			current = current->next;
		}

		if (current->next == nullptr)
		{
			cout << "Value not found!" << endl;
			return;
		}

		Node* toDelete = current->next;
		current->next = toDelete->next;

		if (toDelete == tail)
		{
			tail = current;
		}

		delete toDelete;
		size--;
	}







};




int main()
{

	/*MyList list;
	list.pushBack(11); 
	list.pushBack(22); 
	list.pushBack(33); 
	list.pushBack(44); 
	list.pushBack(55); 
	list.pushBack(66); 

	list.print();

	MyList list2;
	list2.pushBack(99);
	list2.pushBack(88);

	list2 = list;


	list2.print();*/


	MyList list;


	list.pushBack(10);
	list.pushBack(20);
	list.pushBack(30);
	list.pushBack(20);
	list.print();



	list.insert(5, 0);
	list.print();


	cout << "Contains 20 => " << (list.contains(20) ? "Yes" : "No") << endl;
	cout << "Contains 99 => " << (list.contains(99) ? "Yes" : "No") << endl;
	cout << "Index of 20 => " << list.indexOf(20) << endl;
	cout << "Index of 30 => " << list.indexOf(30) << endl;


	list.removeFirst(20);
	list.print();



	list.removeAt(2);
	cout << "Empty List => ";
	list.print();
	list.print();


	list.clear();
	list.print();

	cout << "Size after clear: " << list.getSize() << endl;











	return 0;

}