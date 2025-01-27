#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <string>

int Max(int first, int second){
    if(first > second){
        return first;
    }

    return second;
}

template <typename T> class BinaryTree
{
private:

    class Node
    {
    private:
        size_t height;
        T data;
        Node* left;
        Node* right;
    public:
        Node() : height(1), data(0), left(nullptr), right(nullptr) {}

        Node(const T& item) : height(1), data(item), left(nullptr), right(nullptr) {}

        Node(const Node& other) :
            height(other.height),
            data(other.data),
            left(other.left ? new Node(*other.left) : nullptr),
            right(other.right ? new Node(*other.right) : nullptr)
        {}

        T GetData() const
        {
            return data;
        }

        Node* GetLeft() const
        {
            if (left)
            {
                return left;
            }
            return nullptr;
        }

        Node* GetRight() const
        {
            if (right)
            {
                return right;
            }
            return nullptr;
        }

        size_t GetHeight() const
        {
            return height;
        }

        void SetHeight(size_t h)
        {
            height = h;
        }

        void SetLeft(Node* node)
        {
            left = node;
        }

        void SetRight(Node* node)
        {
            right = node;
        }

        void SetData(const T& value)
        {
            this->data = value;
        }
    };

    Node* root;

    void DeleteTree(Node* elem)
    {
        if (elem == nullptr)
        {
            return;
        }

        DeleteTree(elem->GetLeft());
        DeleteTree(elem->GetRight());
        delete elem;
    }

    Node* FindBSTMin(Node* startRoot) const
    {
        if (startRoot->GetLeft() == nullptr)
        {
            return startRoot;
        }
        return FindBSTMin(startRoot->GetLeft());
    }

    Node* DeleteElem(Node* startRoot, const T& value)
    {
        if (startRoot == nullptr)
        {
            return startRoot;
        }

        else if (value < startRoot->GetData())
        {
            startRoot->SetLeft(DeleteElem(startRoot->GetLeft(), value));
        }

        else if (value > startRoot->GetData())
        {
            startRoot->SetRight(DeleteElem(startRoot->GetRight(), value));
        }

        else
        {
            if (startRoot->GetLeft() == nullptr && startRoot->GetRight() == nullptr)
            {
                delete startRoot;
                return nullptr;
            }

            else if (startRoot->GetLeft() == nullptr)
            {
                Node* temp = startRoot;
                startRoot = startRoot->GetRight();
                delete temp;
            }

            else if (startRoot->GetRight() == nullptr)
            {
                Node* temp = startRoot;
                startRoot = startRoot->GetLeft();
                delete temp;
            }

            else
            {
                startRoot->SetData(FindBSTMin(startRoot->GetRight())->GetData());
                startRoot->SetRight(DeleteElem(startRoot->GetRight(), startRoot->GetData()));
            }
        }
        return Balance(startRoot);
    }

    Node* Insert(Node* startRoot, const T& value)
    {
        if (startRoot == nullptr)
        {
            startRoot = new Node(value);
        }

        if (value < startRoot->GetData())
        {
            startRoot->SetLeft(Insert(startRoot->GetLeft(), value));
        }

        else if (value > startRoot->GetData())
        {
            startRoot->SetRight(Insert(startRoot->GetRight(), value));
        }
        return Balance(startRoot);
    }

    Node* FindNode(Node* startRoot, const T& val) const
    {
        if (startRoot == nullptr)
        {
            return nullptr;
        }

        if (val == startRoot->GetData())
        {
            return startRoot;
        }

        else if (val < startRoot->GetData())
        {
            return FindNode(startRoot->GetLeft(), val);
        }

        else
        {
            return FindNode(startRoot->GetRight(), val);
        }
    }

    bool Compare(Node* node1, Node* node2) const
    {
        if (node1 == nullptr && node2 == nullptr)
        {
            return true;
        }

        else if (node1 == nullptr || node2 == nullptr)
        {
            return false;
        }
        return (node1->GetData() == node2->GetData()) && Compare(node1->GetLeft(), node2->GetLeft()) && Compare(node1->GetRight(), node2->GetRight());
    }

    bool SearchSubtree(Node* node1, Node* node2) const
    {
        if (node2 == nullptr)
        {
            return true;
        }

        else if (node1 == nullptr)
        {
            return false;
        }

        if (Compare(node1, node2))
        {
            return true;
        }
        return SearchSubtree(node1->GetLeft(), node2) || SearchSubtree(node1->GetRight(), node2);
    }

    Node* Search(Node* startRoot, const T& value) const
    {
        if (startRoot == nullptr)
        {
            throw  "ValueOutOfRange";
        }

        if (startRoot->GetData() == value)
        {
            return startRoot;
        }

        if (value <= startRoot->GetData())
        {
            return Search(startRoot->GetLeft(), value);
        }
        return Search(startRoot->GetRight(), value);
    }

    size_t Height(Node* node) const
    {
        if (node)
        {
            return node->GetHeight();
        }
        return 0;
    }

    int BalanceFactor(Node* node) const
    {
        if (node != nullptr)
        {
            return Height(node->GetLeft()) - Height(node->GetRight());
        }
        return 0;
    }

    void UpdateHeight(Node* node) const
    {
        if (node)
        {
            node->SetHeight(1 + Max(Height(node->GetLeft()), Height(node->GetRight())));
        }
    }

    Node* RotateRight(Node* node1)
    {
        Node* node2 = node1->GetLeft();
        Node* temp = node2->GetRight();

        node2->SetRight(node1);
        node1->SetLeft(temp);

        UpdateHeight(node1);
        UpdateHeight(node2);

        return node2;
    }

    Node* RotateLeft(Node* node1)
    {
        Node* node2 = node1->GetRight();
        Node* temp = node2->GetLeft();

        node2->SetLeft(node1);
        node1->SetRight(temp);

        UpdateHeight(node1);
        UpdateHeight(node2);

        return node2;
    }

    Node* Balance(Node* node)
    {
        UpdateHeight(node);

        int balance = BalanceFactor(node);
        if (balance > 1)
        {
            if (BalanceFactor(node->GetLeft()) < 0)
            {
                node->SetLeft(RotateLeft(node->GetLeft()));
            }
            return RotateRight(node);
        }

        if (balance < -1)
        {
            if (BalanceFactor(node->GetRight()) > 0)
            {
                node->SetRight(RotateRight(node->GetRight()));
            }
            return RotateLeft(node);
        }

        return node;
    }

    size_t CountNodes(Node* node) const 
    {
        if (!node)
        {
            return 0;
        }
        return 1 + CountNodes(node->GetLeft()) + CountNodes(node->GetRight());
    }

    T Get(Node* node, size_t index) const 
    {
        if (index >= CountNodes(node) || index < 0 || !node)
        {
            throw "Index out of range";
        }

        size_t leftSize = CountNodes(node->GetLeft());

        if (index < leftSize) 
        {
            return Get(node->GetLeft(), index);
        }
        else if (index == leftSize) 
        {
            return node->GetData();
        }
        else 
        {
            return Get(node->GetRight(), index - leftSize - 1);
        }
    }

    bool SearchBool(Node* startRoot, const T& value) const
    {
        if (startRoot == nullptr)
        {
            return false;
        }
        if (startRoot->GetData() == value)
        {
            return true;
        }
        if (value <= startRoot->GetData())
        {
            return SearchBool(startRoot->GetLeft(), value);
        }
        else
        {
            return SearchBool(startRoot->GetRight(), value);
        }
    }

    Node* GetRoot() const
    {
        return this->root;
    }

public:
    BinaryTree() : root(nullptr) {}

    BinaryTree(Node* root) : root(root) {}

    BinaryTree(const T& val) : root{ new Node(val) } {}

    BinaryTree(T* items, int count) : root(nullptr)
    {
        for (int i = 0; i < count; i++)
        {
            *this += (items[i]);
        }
    }

    BinaryTree(const Node& other) : root(new Node(other)) {}

    BinaryTree(const BinaryTree<T>& other) : root{ new Node(*other.root) } {}

    ~BinaryTree()
    {
        DeleteTree(this->GetRoot());
    }

    /*Node* GetRoot() const
    {
        return this->root;
    }*/

    bool SearchBool(const T& value) const
    {
        return SearchBool(root, value);
    }

    BinaryTree<T>* SubTree(const T& val) const
    {
        Node* subTreeRoot = FindNode(root, val);
        if (!subTreeRoot)
        {
            throw "Value not found in the tree";
        }
        return new BinaryTree<T>(new Node(*subTreeRoot));
    }

    bool SearchSubtree(BinaryTree<T>* tree2) const
    {
        return SearchSubtree(this->GetRoot(), tree2->GetRoot());
    }

    T Get(size_t index) const 
    {
        if (!root)
        {
            throw "Tree is empty";
        }
        return Get(root, index);
    }

    size_t GetLength() const
    {
        return CountNodes(this->GetRoot());
    }

    BinaryTree<T>& operator-=(const T& data)
    {
        root = DeleteElem(root, data);
        return *this;
    }

    BinaryTree<T>& operator+=(const T& data)
    {
        root = Insert(root, data);
        return *this;
    }
};

#endif 
