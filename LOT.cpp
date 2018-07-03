#include<iostream>

using namespace std;

template<class H> class Nodo{
private:
  H *key;
  Nodo<H> *next, *prev;
  Nodo();

public:
  Nodo(H *key){
    this->key=key;
    next=prev=NULL;
  }

  Nodo(H key){
    this->key=new H(key);
    next=prev=NULL;
  }

  void setKey(H key){this->key=new H(key);}
  void setNext(Nodo<H> *next){this->next=next;}
  void setPrev(Nodo<H> *prev){this->prev=prev;}

  H *getKey(){return key;}
  Nodo<H> *getNext(){return next;}
  Nodo<H> *getPrev(){return prev;}

};

template<class H> class Lista{
protected:
  int n;
  Nodo<H> *header, *trailer, *current;

  void _insertAfter(Nodo<H> *tmp, H *key){
    Nodo<H> *prev=tmp->getPrev(),
            *newNodo = new Nodo<H>(key);
    prev->setNext(newNodo);
    newNodo->setPrev(prev);
    newNodo->setNext(tmp);
    tmp->setPrev(newNodo);
    n++;
  }

  Nodo<H> *_rsearch(Nodo<H> *tmp, H *key){
    if(tmp==trailer) return NULL;
    if(*key == *tmp->getKey()) return tmp;
    return _rsearch(tmp->getNext(), key);
  }

public:
  Lista(){
    n=0;
    H *tmp=NULL;
    header= new Nodo<H>(tmp);
    trailer=new Nodo<H>(tmp);
    header->setNext(trailer);
    trailer->setPrev(header);
    current=NULL;
  }

  void *ins(H *key){
    _insertAfter(header->getNext(), key);
  }

  void *del(H *key){
    Nodo<H> *tmp = _rsearch(header->getNext(), key);
    if(!tmp) return this;
    tmp->getPrev()->setNext(tmp->getNext());
    tmp->getNext()->setPrev(tmp->getPrev());
    n--;
  }

  Nodo<H> *getHead(){return header->getNext();}
  Nodo<H> *getTrailer(){return trailer;}
  void reset(){current=header->getNext();}
  H *next(){
    if(has_next()){
      Nodo<H> *tmp=current;
      current=current->getNext();
      return tmp->getKey();
    }
    return NULL;
  }
  int has_next(){return current!=trailer;}

  void print(){
    reset();
    while(has_next()) cout << *next() << " ";
    cout << endl;
  }
};

template<class H> class Tnodo{
private:
  H *key;
  Tnodo<H> *left, *right, *parent;
  Tnodo();
public:
  Tnodo(H key){
    this->key=new H(key);
    left=right=parent=NULL;
  }

  Tnodo(H *key){
    this->key=key;
    left=right=parent=NULL;
  }

  void setKey(H key){this->key=new H(key);}
  void setLeft(Tnodo<H> *left){this->left=left;}
  void setRight(Tnodo<H> *right){this->right=right;}
  void setParent(Tnodo<H> *parent){this->parent=parent;}

  H *getKey(){return key;}
  Tnodo<H> *getLeft(){return  left;}
  Tnodo<H> *getRight(){return  right;}
  Tnodo<H> *getParent(){return  parent;}

};

template<class H> class BST{
private:
  int n;
  Tnodo<H> *root;

  void _inorder(Tnodo<H> *tmp){
    if(tmp){
      _inorder(tmp->getLeft());
      cout << *tmp->getKey() << " ";
      _inorder(tmp->getRight());
    }
  }

  Tnodo<H> *_rsearch(Tnodo<H> *tmp, H key){
    if(!tmp) return NULL;
    if(key == *tmp->getKey()) return tmp;
    if(key> *tmp->getKey()) return _rsearch(tmp->getRight(), key);
    return _rsearch(tmp->getLeft(), key);
  }

  Tnodo<H> *_minimo(Tnodo<H> *tmp){
    while(tmp->getLeft()) tmp=tmp->getLeft();
    return tmp;
  }

  Tnodo<H> *_successore(Tnodo<H> *tmp){
    if(tmp->getRight()) return _minimo(tmp->getRight());
    Tnodo<H> *parent=tmp->getParent();
    while(parent && *parent->getKey()>*tmp->getKey()) parent=parent->getParent();
    return parent;
  }

  void _canc(Tnodo<H> *nd, H key){
    Tnodo<H> *tmp=_rsearch(nd, key);
    if(!tmp) return;
    if(!tmp->getLeft() || !tmp->getRight()){
      n--;
      Tnodo<H> *figlio=tmp->getRight(),
               *parent=tmp->getParent();
      if(tmp->getLeft()) figlio=tmp->getLeft();
      if(!parent) root = figlio;
      else{
        if(tmp == parent->getLeft()) parent->setLeft(figlio);
        else parent->setRight(figlio);
      }
      if(figlio) figlio->setParent(parent);
    }else{
      Tnodo<H> *succ = _successore(tmp);
      tmp->setKey(*succ->getKey());
      _canc(tmp->getRight(), *succ->getKey());
    }
  }
public:
  BST(){
    n=0;
    root=NULL;
  }

  void insert(H key){
    Tnodo<H> *tmp=root,
             *p=NULL,
             *nd=new Tnodo<H>(key);
    while(tmp){
      p=tmp;
      if(key> *tmp->getKey()) tmp=tmp->getRight();
      else tmp=tmp->getLeft();
    }
    if(!p) root=nd;
    else{
      if(key> *p->getKey()) p->setRight(nd);
      else p->setLeft(nd);
    }
    nd->setParent(p);
    n++;
  }

  void del(H key){
    _canc(root, key);
  }

  void print(){
    _inorder(root);
  }

  Tnodo<H> *getRoot(){return root;}
  int getSize(){return n;}
};

template<class H> bool operator == (const BST<H> &a, const BST<H> &b){
  BST<H> s1=a;
  BST<H> s2=b;

  if(s1.getSize() == s2.getSize()) return true;
  return false;
}

template<class H> class LOT{
private:
  Lista< BST<H> > *lot;
  int k;
public:
  LOT(int k){
    lot= new Lista<BST <H> >;
    this->k=k;
  }

  LOT<H> *ins(H key){
    Nodo< BST<H> >*tmp = lot->getHead();
    if(tmp==lot->getTrailer() || tmp->getKey()->getSize() == k){
      BST<H> *t = new BST<H>();
      t->insert(key);
      lot->ins(t);
    }else{
       tmp->getKey()->insert(key);
     }
    return this;
  }
  LOT<H> *del(H key){
    lot->reset();
    while(lot->has_next()){
      BST<H> *tmp = lot->next();
      tmp->del(key);
      if(tmp->getSize() == 0) lot->del(tmp);
    }
    return this;
  }
  void print(){
    lot->reset();
    while(lot->has_next()){
      BST<H> *tmp = lot->next();
      tmp->print();
      cout<<endl;
    }
  }
};

int main(){
LOT<int> *l = new LOT<int>(4);
  l->ins(2)->ins(3)->ins(1)->ins(5)->ins(3)->ins(7)->ins(6)->ins(1);
  l->ins(2)->ins(4)->ins(5)->ins(3)->ins(2)->ins(1);
  l->del(5)->del(1)->del(2)->print();
return 0;
}
