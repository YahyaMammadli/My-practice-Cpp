#include <iostream>
#include <stdexcept>

using namespace std;








struct Node
{
    int data;
    Node* next;
    Node* prev;
};





class Deque
{
private:
    Node* head;
    Node* tail;
    int size;

public:


    Deque() : head(nullptr), tail(nullptr), size(0) {}

    void pushFront(int data)
    {
        Node* newNode = new Node;
        newNode->data = data;
        newNode->next = nullptr;
        newNode->prev = nullptr;

        if (isEmpty())
        {
            head = tail = newNode;
            return;
        }
        
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        
        size++;
    }

    void pushBack(int data) 
    {
        Node* newNode = new Node;
        newNode->data = data;
        newNode->next = nullptr;
        newNode->prev = nullptr;

        if (isEmpty())
        {
            head = tail = newNode;
        }



        else
        {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }


        size++;
    }

    int popFront()
    {
        if (isEmpty())
        {
            throw runtime_error("Deque is empty");
        }

        Node* temp = head;
        int data = head->data;

        if (head == tail) 
        {
            head = tail = nullptr;
        }
        else {
            head = head->next;
            head->prev = nullptr;
        }

        delete temp;
        size--;
        return data;
    }

    int popBack() 
    {
        if (isEmpty())
        {
            throw std::runtime_error("Deque is empty");
        }

        Node* temp = tail;
        int data = tail->data;

        if (head == tail) 
        {
            head = tail = nullptr;
        }



        else
        {
            tail = tail->prev;
            tail->next = nullptr;
        }

        delete temp;
        size--;
        return data;
    }

    int peekFront() const
    {
        if (isEmpty())
        {
            throw std::runtime_error("Deque is empty");
        }
        return head->data;
    }

    int peekBack() const 
    {
        if (isEmpty()) 
        {
            throw std::runtime_error("Deque is empty");
        }
        return tail->data;
    }

    bool isEmpty() const 
    {
        return head == nullptr;
    }

    int getSize() const
    {
        return size;
    }

    void printDeque() const
    {
        Node* current = head;
        cout << "Deque => ";
    
        
        while (current != nullptr)
        {
            cout << current->data;
        
            
            if (current->next != nullptr) 
            {
                cout << " -> ";
            
            
            }
            current = current->next;
        }
        
        cout << " | Size => " << size << std::endl;
    }

    ~Deque() 
    {
        while (!isEmpty()) 
        {
            popFront();
        }
    }
};

int main(void) 
{
    Deque dq;


    dq.pushBack(10);
    dq.pushBack(20);
    dq.pushFront(5);
    dq.pushBack(30);
    dq.pushFront(1);
    dq.printDeque();

    
    cout <<  dq.peekFront() << endl;
    cout << dq.peekBack() << endl;
    cout << dq.popFront() << endl;
    cout << dq.popBack() << endl;
    
    dq.printDeque();

    dq.pushBack(100);
    dq.pushFront(50);
    dq.printDeque();

    

    while (!dq.isEmpty())
    {
        dq.popFront();
    }

    

    cout <<  dq.getSize() << endl;


    return 0;
}