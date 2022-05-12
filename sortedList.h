#ifndef SORTEDLIST_H
#define SORTEDLIST_H

#include <iostream>
#include <stdexcept>

namespace mtm
{
    template <class T>
    class SortedList;

    template <class T>
    struct Node 
    {
        
        friend class SortedList<T>;

        T data;
        struct Node<T>* next;

        Node() = delete;

        explicit Node(const T &src_data);

        Node(const Node<T> &other) = default;

        ~Node() = default;

        Node<T>& operator=(const Node<T> &other) = default;
    };

    template <class T>
    class SortedList
    {   
        Node<T>* head;

    public:
        class const_iterator;

        SortedList();
        SortedList(const SortedList &other);
        ~SortedList();
        SortedList<T>& operator=(const SortedList &other);    
        void insert(const T &data);
        void remove(const const_iterator &iterator);
        int length() const;

        template <typename Predict>
        SortedList<T> filter(Predict function) const;

        template <typename Function>
        SortedList<T> apply(Function function) const;

        SortedList::const_iterator begin() const;
        SortedList::const_iterator end() const;
    };

    template <class T>
    class SortedList<T>::const_iterator
    {
        Node<T>* node;
        const_iterator(const SortedList<T>* list) : node(list->head) {};


        friend class SortedList<T>;

        public:
            const_iterator() = delete;
            const_iterator(const const_iterator &other) = default;
            const_iterator& operator=(const const_iterator &other) = default;
            ~const_iterator() = default;
            const_iterator& operator++();
            const_iterator& operator++(int); 
            bool operator==(const const_iterator &other) const;
            const T& operator*() const;
            Node<T>* getNodePointer(const_iterator &iterator) const;
    };


    /********** SortedList methods implementation: **********/



    // Constructor
    template <class T>
    SortedList<T>::SortedList() : head(nullptr) {}

    // Copy Constructor
    template <class T>
    SortedList<T>::SortedList(const SortedList &other) : head(nullptr)
    {
        Node<T>* other_current = other.head; //or other->begin().node

        while (other_current != nullptr)
        {
            this->insert(other_current->data);
            other_current = other_current->next;
        }
    }

    // Destructor
    template <class T>
    SortedList<T>::~SortedList()
    {
        Node<T>* current = this->head;
        Node<T>* next = nullptr;

        while (current != nullptr)
        {
            next = current->next;
            delete current;
            current = next;
        }

        //delete this; valgrind?      
    }
    
    // = Operator
    template <class T>
    SortedList<T>& SortedList<T>::operator=(const SortedList &other)
    {
        if (this == &other)
        {
            return *this;
        }

        Node<T>* current = this->head; //or this->begin().node
        Node<T>* next = nullptr;

        while (current != nullptr)
        {
            Node<T>* next = current->next;
            
            next = current->next;
            delete current;
            current = next;
        }

        this->head = nullptr;
        current = other.head;
        while (current != nullptr)
        {
            this->insert(current->data);
            current = current->next;
        }
        return *this;
    }
    
    // Insert node function
    template <class T>
    void SortedList<T>::insert(const T &data)
    {
        Node<T>* new_node = new Node<T>(data);
        Node<T>* previous = nullptr;
        Node<T>* current = this->head;

        while (current != nullptr)
        {
            if (data < current->data)
            {
                break;
            }
            previous = current;
            current = current->next;
        }
        new_node->next = current;

        if (previous != nullptr)
        {
            previous->next = new_node;
        }
        else
        {
            this->head = new_node;
        }
    }

    // Remove node function
    template <class T>
    void SortedList<T>::remove(const SortedList<T>::const_iterator &iterator)
    {
        if (iterator.node == nullptr)
        {
            throw std::out_of_range("Exceeded list boundaries");
        }

        Node<T>* current = this->head;
        Node<T>* previous = nullptr;

        while (current != nullptr)
        {
            if (current == iterator.node)
            {
                if (previous == nullptr)
                {
                    this->head = this->head->next;
                }
                else
                {
                    previous->next = current->next;
                } 
                delete current;
                return;
            }
            previous = current;
            current = current->next;
        }
    }

    // Get length function
    template <class T>
    int SortedList<T>::length() const
    {
        if (this == nullptr)
        {
            return 0;
        }
        Node<T>* current = this->head;
        int count = 1;

        while (current->next != nullptr)
        {
            count++;
            current = current->next;
        }

        return count;
    }

    template <class T>
    template <typename Predict> 
    SortedList<T> SortedList<T>::filter(Predict function) const
    {
        if (this == nullptr)
        {
            throw std::out_of_range("Exceeded list boundaries");
        }
        SortedList<T>* new_list = new SortedList;
        Node<T>* current = this->head;

        while (current != nullptr)
        {
            if (function(current->data) == true)
            {
                new_list->insert(current->data); 
            }
            current = current->next;
        }
        return *new_list;
    }

    template <class T>
    template <typename Function>
    SortedList<T> SortedList<T>::apply(Function function) const
    {
        if (this == nullptr)
        {
            throw std::out_of_range("Exceeded list boundaries");
        }

        SortedList<T>* new_list = new SortedList;
        Node<T>* current = this->head;

        while (current != nullptr)
        {
            new_list->insert(function(current->data)); 
            current = current->next;
        }
        
        return *new_list;
    }

    // begin funcion
    template <class T>
    typename SortedList<T>::const_iterator SortedList<T>::begin() const
    {
        if (this == nullptr)
        {
            throw std::out_of_range("Exceeded list boundaries");
        }
        return const_iterator(this);
    }

    // end funcion
    template <class T>
    typename SortedList<T>::const_iterator SortedList<T>::end() const
    {
        if (this == nullptr)
        {
            throw std::out_of_range("Exceeded list boundaries");
        }
        const_iterator current = this->begin();

        while (current.node->next != nullptr)
        {
            current++;
        }
        return current;
    }



    /********** const_iterator methods implementations: **********/
    


    // ++ Operator - prefix
    template <class T>
    typename SortedList<T>::const_iterator& SortedList<T>::const_iterator::operator++()
    {
        if (this == nullptr)
        {
            throw std::out_of_range("Exceeded list boundaries");
        }
        this->node = this->node->next;
        return *this;
    }

    // ++ Operator - postfix
    template <class T>
    typename SortedList<T>::const_iterator& SortedList<T>::const_iterator::operator++(int)
    {
        const_iterator* iterator = this;

        if (this->node == nullptr)
        {
            throw std::out_of_range("Exceeded list boundaries");
        }
        this->node = this->node->next;
        return *iterator;
    } 
    
    // == Operator
    template <class T>
    bool SortedList<T>::const_iterator::operator==(const const_iterator& other) const
    {
        if (this->node == nullptr && other.node == nullptr)
        {
            return true;
        }

        if (this->node != nullptr && other.node == nullptr ||
            this->node == nullptr && other.node != nullptr)
        {
            return false;
        }
        
        return (this->node == other.node);
    }

    // * Operator
    template <class T>
    const T& SortedList<T>::const_iterator::operator*() const
    {
        if (this == nullptr)
        {
            throw std::out_of_range("Exceeded list boundaries");
        }

        if (this->node == nullptr)
        {
            throw std::out_of_range("Exceeded list boundaries");
        }
        return this->node->data;
    }


    /********** Node methods implementations: **********/


    // Overloaded Constructor
    template <class T>
    Node<T>::Node(const T &src_data) : data(src_data), next(nullptr) {}

}


#endif //SORTEDLIST_H