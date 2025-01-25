#pragma once

template <class T>
class LinkedList
{
private:
    
    struct Node
    {
    public:
        T data;
        Node* prev;
        Node* next;

    public:
        Node(const T& data)
        {
            this->data = data;
            this->prev = this->next = NULL;
        }
    };
    Node* head;
    Node* tail;
    size_t size;
public:
    LinkedList()
    {
        this->head = this->tail = nullptr;
        this->size = 0;
    }

    LinkedList(const T* items, int count)
    {
        this->size = 0;
        for (int i = 0; i < count; i++)
        {
            Append(items[i]);
        }
    }

    LinkedList(const LinkedList<T>& other)
    {
        this->size = 0;
        this->head = this->tail = NULL;

        Node* current = other.head;
        while (current != NULL)
        {
            Append(current->data);
            current = current->next;
        }
    }



    ~LinkedList()
    {
        if (head != NULL && tail != NULL)
        {
            Node* ptr = this->head;
            while (ptr != NULL)
            {
                Node* current = ptr->next;

                delete ptr;
                ptr = current;

            }
        }
    }

    int GetLength() const
    {
        return this->size;
    }

    T GetFirst() const
    {
        if (this->GetLength() == 0)
        {
            throw  "IndexOutOfRange";
        }
        return this->head->data;
    }

    T GetLast() const
    {
        if (this->GetLength() == 0)
        {
            throw  "IndexOutOfRange";
        }
        return this->tail->data;
    }

    T Get(int index) const
    {
        if (index < 0 || index >= this->GetLength())
        {
            throw  "IndexOutOfRange";
        }

        Node* current = this->head;

        for (int i = 0; i != index; i++)
        {
            current = current->next;
        }
        return current->data;
    }

    void Append(const T& item)
    {
        Node* ptr = new Node(item);

        ptr->prev = tail;
        if (tail != NULL)
        {
            tail->next = ptr;
        }
        else
        {
            head = ptr;
        }
        this->tail = ptr;

        this->size += 1;
    }

    void Prepend(const T& item)
    {
        Node* ptr = new Node(item);

        ptr->next = head;
        if (head != NULL)
            head->prev = ptr;
        if (tail == NULL)
            tail = ptr;
        this->head = ptr;

        this->size += 1;
    }

    LinkedList<T>* GetSubList(int startIndex, int endIndex) const
    {
        LinkedList<T>* result = new LinkedList<T>();

        if (startIndex >= this->GetLength() || startIndex < 0 || endIndex >= this->GetLength() || endIndex < 0)
        {
            throw  "IndexOutOfRange";
        }

        Node* current = this->head;

        for (int i = 0; i <= endIndex; i++)
        {
            if (i >= startIndex)
            {
                result->Append(current->data);
            }
            current = current->next;
        }
        return result;
    }

    void InsertAt(const T& item, int index)
    {
        if (index > this->GetLength() || index < 0)
        {
            throw  "IndexOutOfRange";
        }

        if (index == 0)
        {
            this->Prepend(item);
        }

        else if (this->GetLength() == 0 || this->GetLength() == index)
        {
            this->Append(item);
        }

        else
        {
            Node* right = head;
            for (int i = 0; i < index; i++)
            {
                right = right->next;
            }

            Node* left = right->prev;
            Node* ptr = new Node(item);

            ptr->prev = left;
            ptr->next = right;
            left->next = ptr;
            right->prev = ptr;
            this->size += 1;
        }

    }

    void RemoveAt(int index) 
    {
        if (index < 0 || index >= this->GetLength()) 
        {
            throw std::out_of_range("Index out of range");
        }

        Node* current = this->head;

        for (int i = 0; i < index; i++) 
        {
            current = current->next;
        }

        if (current->prev) 
        {
            current->prev->next = current->next;
        }
        else 
        {
            this->head = current->next;
        }

        if (current->next) 
        {
            current->next->prev = current->prev;
        }
        else 
        {
            this->tail = current->prev;
        }

        delete current;
        --size;
    }


    void Set(const T& item, int index)
    {
        if (index >= this->GetLength() || index < 0)
        {
            throw  "IndexOutOfRange";
        }
        Node* current = this->head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        current->data = item;
    }


    LinkedList<T>* Concat(const LinkedList<T>* other) const
    {
        LinkedList<T> result(*this);

        for (int i = 0; i < other->size; i++)
        {
            result.Append(other->Get(i));
        }
        return new LinkedList<T>(result);
    }

    template <typename T2>
    LinkedList<T2>* Concat(const LinkedList<T2>* list) const
    {
        LinkedList<T2>* newList = new LinkedList<T2>(*this);

        Node* lastNode = newList->tail;
        Node* current = list->head;

        while (current)
        {
            Node* newNode = new Node(current->data);

            if (lastNode)
            {
                lastNode->next = newNode;
                newNode->prev = lastNode;
            }
            else
            {
                newList->head = newNode;
            }

            lastNode = newNode;
            current = current->next;
        }

        newList->tail = lastNode;
        newList->length = this->size + list->GetLength();

        return newList;
    }
};
