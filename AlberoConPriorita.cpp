#include<iostream>

using namespace std;

template<class H> class PBT{
public:
  virtual PBT<H> *ins(int priority, H key)=0;
  virtual H find(int priority)=0;
  virtual void print()=0;
};


template<class H> class Nodo{
private:
  H *key;
  Nodo<H> *left, *right, *parent;
  int priority;
public:
  Nodo(int p, H key){
    this->key=new H(key);
    priority=p;
    left=right=parent=NULL;
  }

  void setKey(H key){this->key=new H(key);}
  void setPriority(int p){priority=p;}
  void setLeft(Nodo<H> *x){left=x;}
  void setRight(Nodo<H> *x){right=x;}
  void setParent(Nodo<H> *x){parent=x;}

  H *getKey(){return key;}
  int getPriority(){return priority;}
  Nodo<H> *getLeft(){return left;}
  Nodo<H> *getRight(){return right;}
  Nodo<H> *getParent(){return parent;}

};

template<class H> class MyPBT{
private:
  int n;
  Nodo<H> *root, *current;

  void _revInOrder(Nodo<H> *x){
    if(x){
      _revInOrder(x->getRight());
      cout << *x->getKey() << " ";
      _revInOrder(x->getLeft());
    }
  }

  Nodo<H> *_rfind(Nodo<H> *x, int priority){
    if(!x) return NULL;
    if(x->getPriority() == priority) return x;
    if(priority>x->getPriority()) return _rfind(x->getRight(), priority);
    return _rfind(x->getLeft(), priority);
  }

  Nodo<H> *_minimo(Nodo<H> *x){
    while(x->getLeft()) x=x->getLeft();
    return x;
  }

  Nodo<H> *_successorePriority(Nodo<H> *x){
    if(x->getRight()) return _minimo(x->getRight());
    Nodo<H> *p=x->getParent();
    while(p && p->getPriority()<x->getPriority()) p=p->getParent();
    return p;
  }

  Nodo<H> *_itSearch(Nodo<H> *x, H key){
    Nodo<H> *tmp=_minimo(root);
    while(tmp){
      if(*tmp->getKey() == key) return tmp;
      tmp= _successorePriority(tmp);
    }
    return NULL;
  }

  void _canc(Nodo<H> *nd, H key){
    Nodo<H> *tmp=_itSearch(nd, key);
    if(!tmp) return;
    if(!tmp->getLeft() || !tmp->getRight()){
      n--;
      Nodo<H> *figlio=tmp->getRight(),
              *p=tmp->getParent();
      if(tmp->getLeft()) figlio=tmp->getLeft();
      if(!p) root=figlio;
      else{
        if(tmp == p->getLeft()) p->setLeft(figlio);
        else p->setRight(figlio);
      }
      if(figlio) figlio->setParent(p);
    }else{
      Nodo<H> *succ= _successorePriority(tmp);
      tmp->setKey(*succ->getKey());
      _canc(tmp->getRight(), *succ->getKey());
    }
  }

public:
  MyPBT(){
    root=NULL;
    n=0;
  }

  MyPBT<H> *ins(int priority, H key){
    Nodo<H> *tmp=root,
            *p=NULL,
            *nd=new Nodo<H>(priority,key);
    while(tmp){
      p=tmp;
      if(priority> tmp->getPriority()) tmp=tmp->getRight();
      else tmp=tmp->getLeft();
    }
    if(!p) root=nd;
    else{
      if(priority>p->getPriority()) p->setRight(nd);
      else p->setLeft(nd);
    }
    nd->setParent(p);
    n++;
    return this;
  }

  MyPBT<H> *del(H key){
    _canc(root, key);
    return this;
  }

  H find(int priority){
    Nodo<H> *tmp = _rfind(root, priority);
    if(!tmp) return 0;
    return *tmp->getKey();
  }

  void print(){
    _revInOrder(root);
    cout<<endl;
  }
};





int main(){
  MyPBT<int> *p=new MyPBT<int>();
  p->ins(10,5)->ins(7,3)->ins(8,13)->ins(13,1)->ins(6,2)->ins(9,7)->print();
  p->del(13)->del(1)->print();
  cout<<p->find(10);

  return 0;
}
