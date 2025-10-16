#include "listNode.h"

template<typename T> class List{
private:
    int _size; NodePosi<T> header; NodePosi<T> trailer; 
protected:
    void init();
    int clear();
    void copyNodes(NodePosi<T> p, int n);
    void merge(NodePosi<T>&, int, List<T>&, NodePosi<T>, int);
    void mergeSort(NodePosi<T>&, int);
    void selectionSort(NodePosi<T>, int);
    void insertionSort(NodePosi<T>, int);
public:
    List(){init();}
    List(List<T>const&L);
    List(List<T>const&L, Rank r, int n);
    List(listNodePosi<T> p, int n);
    ~List();
    Rank size()const{return _size;}
    bool empty()const{return _size<=0;}
    T& operator[](Rank r)const;
    listNodePosi<T> first()const{return header->succ;}
    listNodePosi<T> last()const{return trailer->pred;}
    bool valid(listNodePosi<T> p){return p && (trailer!=p) && (header!=p);}
    int disordered()const;
    listNodePosi<T> find(T const&e)const{return find(e, _size, trailer);}
    listNodePosi<T> find(T const&e, int n, listNodePosi<T> p)const;
    listNodePosi<T> search(T const&e)const{return search(e, _size, trailer);}
    listNodePosi<T> search(T const&e, int n, listNodePosi<T> p)const;
    listNodePosi<T> selectMax(listNodePosi<T> p, int n);
    listNodePosi<T> selectMax(){return selectMax(header->succ, _size);}
    listNodePosi<T> insertAsFirst(T const&e);
    listNodePosi<T> insertAsLast(T const&e);
    listNodePosi<T> insertB(listNodePosi<T> p, T const&e);
    listNodePosi<T> insertA(listNodePosi<T> p, T const&e);
    T remove(listNodePosi<T> p);
    void merge(List<T>& L){merge(header->succ, _size, L, L.header->succ, L._size);}
    void sort(listNodePosi<T> p, int n);
    void sort(){sort(header->succ, _size);}
    int deduplicate();
    int uniquify();
    void reverse();
    void traverse(void(*)(T&));
    template<typename VST> void traverse(VST&);
};
template<typename T> void List<T>::init(){
    header=new ListNode<T>; trailer=new ListNode<T>;
    header->pred=NULL; header->succ=trailer;
    trailer->pred=header; trailer->succ=NULL;
    _size=0;
}
template<typename T>
T& List<T>::operator[](Rank r)const{
    listNodePosi<T> p=first();
    while(0<r--) p=p->succ;
    return p->data;
}
template<typename T>
listNodePosi(T) List<T>::find(T const&e, int n, listNodePosi<T> p)const{
    while(0<n--){
        if(e===(p=p->pred)->data) return p;
    }
    return NULL;
}
template<typename T>
listNodePosi(T) List<T>::insertAsFirst(T const&e){
    _size++; return header->insertAsSucc(e);
}
template<typename T>
listNodePosi(T) List<T>::insertAsLast(T const&e){
    _size++; return trailer->insertAsPred(e);
}
template<typename T>
listNodePosi(T) List<T>::insertA(listNodePosi<T> p, T const&e){
    _size++; return p->insertAsSucc(e);
}
template<typename T>
listNodePosi(T) List<T>::insertB(listNodePosi<T> p, T const&e){
    _size++; return p->insertAsPred(e);
}
template<typename T>
listNodePosi(T) ListNode<T>::insertAsPred(T const&e){
    listNodePosi<T> x=new ListNode<T>(e, pred, this);
    pred->succ=x; pred=x; return x;
}
template<typename T>
listNodePosi(T) ListNode<T>::insertAsSucc(T const&e){
    listNodePosi<T> x=new ListNode<T>(e, this, succ);
    succ->pred=x; succ=x; return x;
}
template<typename T>
void List<T>::copyNodes(listNodePosi<T> p, int n){
    init();
    while(0<n--){
        insertAsLast(p->data); p=p->succ;
    }
}
template<typename T>
List<T>::List(listNodePosi<T> p, int n){
    copyNodes(p, n);
}
template<typename T>
List<T>::List(List<T>const&L){
    copyNodes(L.first(), L._size);
}
template<typename T>
List<T>::List(List<T>const&L, int r, int n){
    copyNodes(L[r], n);
}
template<typename T> T List<T>::remove(listNodePosi<T> p){
    T e=p->data; p->pred->succ=p->succ; p->succ->pred=p->pred;
    delete p; _size--; return e;
}
template<typename T> List<T>::~List(){
    clear(); delete header; delete trailer;
}
template<typename T> int List<T>::clear(){
    int oldSize=_size;
    while(0<_size) remove(header->succ);
    return oldSize; 
}
template<typename T> int List<T>::deduplicate(){
    if(_size<2) return 0;
    int oldSize=_size; listNodePosi<T> p=header; Rank r=0;
    while(trailer!=(p=p->succ)){
        listNodePosi<T> q=find(p->data, r, p);
        q? remove(q): r++; 
    }
    return oldSize-_size;
}
template<typename T> void List<T>::traverse(void(*visit)(T&)){
    for(listNodePosi<T> p=header->succ; p!=trailer; p=p->succ) visit(p->data);
}
template<typename T> template<typename VST> void List<T>::traverse(VST& visit){
    for(listNodePosi<T> p=header->succ; p!=trailer; p=p->succ) visit(p->data);
}
template<typename T> int List<T>::uniquify(){
    if(_size<2) return 0;
    int oldSize=_size; listNodePosi<T> p=first(); listNodePosi<T> q;
    while(trailer!=(q=p->succ)){
        if(p->data!=q->data) p=q;
        else remove(q);
    }
    return oldSize-_size;
}
template<typename T>
listNodePosi(T) List<T>::search(T const&e, int n, listNodePosi<T> p)const{
    while(0<n--){
        if(((p=p->pred)->data)<=e) break;
    }
    return p;
}
template<typename T> void List<T>::sort
(listNodePosi<T> p, int n){
    switch(rand()%3){
        case 1: insertionSort(p, n); break;
        case 2: selectionSort(p, n); break;
        default: mergeSort(p, n); break;
    }
}
template<typename T>
void List<T>::insertionSort(listNodePosi<T> p, int n){
    for(int r=0; r<n; r++){
        insertA (search(p->data, r, p), p->data);
        p=p->succ; remove(p->pred);
    }
}
template<typename T>
void List<T>::selectionSort(listNodePosi<T> p, int n){
    listNodePosi<T> head=p->pred; listNodePosi<T> tail=p;
    for(int r=0; r<n; r++) tail=tail->succ;
    while(1<n){
        listNodePosi<T> max=selectMax(head->succ, n);
        insertB(tail, remove(max));
        tail=tail->pred; n--;
    }
}
template<typename T>
listNodePosi(T) List<T>::selectMax(listNodePosi<T> p, int n){
    listNodePosi<T> max=p;
    for(listNodePosi<T> cur=p; 1<n; n--){
        if((cur=cur->succ)->data>=max->data) max=cur;
    }
    return max;
}
template<typename T>
void List<T>::merge(listNodePosi<T>& p, int n, List<T>& L, listNodePosi<T> q, int m){
    listNodePosi<T> pp=p->pred;
    while(0<m){
        if((0<n) && (p->data<=q->data)){
            if(q==(p=p->succ)) break; n--;
        }
        else{
            insertB(p, L.remove((q=q->succ)->pred)); m--;
        }
    }
    p=pp->succ;
}
template<typename T>
void List<T>::mergeSort(listNodePosi<T>& p, int n){
    if(n<2) return;
    int m = n >> 1;
    listNodePosi<T> q=p; for(int i=0; i<m; i++) q=q->succ;
    mergeSort(p, m); mergeSort(q, n-m);
    merge(p, m, *this, q, n-m);
}
