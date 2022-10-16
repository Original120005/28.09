#pragma once
#include <iostream>
using namespace std;

template<class T>
struct Elem {
    int data;
    Elem* next, * prev;
};

template<class T>
class List {
    Elem<T>* Head, * Tail;
    int Count;

public:
    List();
    List(const List&);
    ~List();

    int GetCount();
    Elem<T>* GetElem(int);
    void DelAll();
    void Del(int pos = 0);
    void Insert(int pos = 0);
    void AddTail(int n);
    void AddHead(int n);
    void Print();
    void Print(int pos);

    List& operator = (const List&);
    List operator + (const List&);

    List operator - ();
};

template<class T>
List<T>::List()
{
    Head = Tail = NULL;
    Count = 0;
}

template<class T>
List<T>::List(const List& L)
{
    Head = Tail = NULL;
    Count = 0;

    Elem* temp = L.Head;
    while (temp != 0)
    {
        AddTail(temp->data);
        temp = temp->next;
    }
}

template<class T>
List<T>::~List()
{
    DelAll();
}

template<class T>
void List<T>::AddHead(int n)
{
    Elem<T>* temp = new Elem<T>;
    temp->prev = 0;
    temp->data = n;
    temp->next = Head;
    if (Head != 0)
    {
        Head->prev = temp;
    }
    if (Count == 0)
    {
        Head = Tail = temp;
    }
    else
    {
        Head = temp;
    }
    Count++;
}

template<class T>
void List<T>::AddTail(int n)
{
    Elem<T>* temp = new Elem<T>;
    temp->next = 0;
    temp->data = n;
    temp->prev = Tail;
    if (Tail != 0)
    {
        Tail->next = temp;
    }
    if (Count == 0)
    {
        Head = Tail = temp;
    }
    else
    {
        Tail = temp;
    }
    Count++;
}

template<class T>
void List<T>::Insert(int pos)
{
    if (pos == 0)
    {
        cin >> pos;
    }
    if (pos < 1 || pos > Count + 1)
    {
        return;
    }
    if (pos == Count + 1)
    {
        int data;
        cin >> data;
        AddTail(data);
        return;
    }
    else if (pos == 1)
    {
        int data;
        cin >> data;
        AddHead(data);
        return;
    }
    int i = 1;
    Elem<T>* Ins = Head;
    while (i < pos)
    {
        Ins = Ins->next;
        i++;
    }
    Elem<T>* PrevIns = Ins->prev;
    Elem<T>* temp = new Elem<T>;
    cin >> temp->data;
    if (PrevIns != 0 && Count != 1)
    {
        PrevIns->next = temp;
    }
    temp->next = Ins;
    temp->prev = PrevIns;
    Ins->prev = temp;
    Count++;
}

template<class T>
void List<T>::Del(int pos)
{
    if (pos == 0)
    {
        cin >> pos;
    }
    if (pos < 1 || pos > Count)
    {
        return;
    }
    Elem<T>* Del = nullptr;
    int i = 1;
    if (pos <= Count / 2)
    {
        Del = Head;
        while (i < pos)
        {
            Del = Del->next;
            i++;
        }
    }
    else
    {
        Del = Tail;
        while (i <= Count - pos)
        {
            Del = Del->prev;
            i++;
        }
    }
    Elem<T>* PrevDel = Del->prev;
    Elem<T>* AfterDel = Del->next;
    if (PrevDel != 0 && Count != 1)
    {
        PrevDel->next = AfterDel;
    }
    if (AfterDel != 0 && Count != 1)
    {
        AfterDel->prev = PrevDel;
    }
    if (pos == 1)
    {
        Head = AfterDel;
    }
    if (pos == Count)
    {
        Tail = PrevDel;
    }
    delete Del;
    Count--;
}

template<class T>
void List<T>::Print(int pos)
{
    if (pos < 1 || pos > Count)
    {
        cout << "Incorrect position !!!\n";
        return;
    }

    Elem* temp;

    if (pos <= Count / 2)
    {
        temp = Head;
        int i = 1;

        while (i < pos)
        {
            temp = temp->next;
            i++;
        }
    }
    else
    {
        temp = Tail;
        int i = 1;

        while (i <= Count - pos)
        {
            temp = temp->prev;
            i++;
        }
    }
    cout << pos << " element: ";
    cout << temp->data << endl;
}

template<class T>
void List<T>::Print() {
    if (Count != 0)
    {
        Elem<T>* temp = Head;
        cout << "\n";
        while (temp->next != 0)
        {
            cout << temp->data << "\n";
            temp = temp->next;
        }
        cout << temp->data << "\n";
    }
}

template<class T>
void List<T>::DelAll()
{
    while (Count != 0)
        Del(1);
}

template<class T>
int List<T>::GetCount()
{
    return Count;
}

template<class T>
Elem<T>* List<T>::GetElem(int pos)
{
    Elem* temp = nullptr;
    int i = 1;
    if (pos <= Count / 2)
    {
        temp = Head;

        while (i < pos)
        {
            temp = temp->next;
            i++;
        }
    }
    else
    {
        temp = Tail;
        while (i <= Count - pos)
        {
            temp = temp->prev;
            i++;
        }
    }
    if (pos < 1 || pos > Count)
    {
        cout << "Incorrect position !!!\n";
        return 0;
    }

    return temp;
}

template<class T>
List<T>& List<T>::operator = (const List& L)
{
    if (this == &L)
        return *this;

    this->~List(); 

    Elem* temp = L.Head;

    while (temp != 0)
    {
        AddTail(temp->data);
        temp = temp->next;
    }

    return *this;
}

template<class T>
List<T> List<T>::operator + (const List<T>& L)
{
    List Result(*this);

    Elem* temp = L.Head;


    while (temp != 0)
    {
        Result.AddTail(temp->data);
        temp = temp->next;
    }

    return Result;
}


template<class T>
List<T> List<T>::operator - () 
{
    List Result;

    Elem* temp = Head;
    while (temp != 0)
    {
        Result.AddHead(temp->data);
        temp = temp->next;
    }

    return Result;
}
