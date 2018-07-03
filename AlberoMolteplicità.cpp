#include<iostream>
using namespace std;

template<class H> class Nodo{
private:
  H *key;
  int mul;
  Nodo<H> *left, *right, *parent;

public:
  Nodo(H key){
    this->key=new H(key);
    left=right=parent=NULL;
    mul=1;
  }

  Nodo(H *key){
    this->key=key;
    left=right=parent=NULL;
    mul=1;

  }

  void setKey(H key){this->key=new H(key);}
  void setLeft(Nodo<H> *x){left=x;}
  void setRight(Nodo<H> *x){right=x;}
  void setParent(Nodo<H> *x){parent=x;}
  void setMul(int n){mul=n;}
  void incMul(){mul++;}
  void decMul(){mul--;}


  H *getKey(){return key;}
  int getMul(){return mul;}
  Nodo<H> *getLeft(){return left;}
  Nodo<H> *getRight(){return right;}
  Nodo<H> *getParent(){return parent;}

};

template<class H> class MultiBST{
public:
  virtual MultiBST<H> *ins(H x)=0;
  virtual int search(H key)=0;
  virtual void print()=0;
};

template<class H> class MyMultiBST{
private:
  int n;
  Nodo<H> *root, *current;

  void _inorder(Nodo<H> *x){
    if(x){
      _inorder(x->getLeft());
      int k=x->getMul();
       cout << "[" <<*x->getKey() <<", " << x->getMul()<<"] ";
      _inorder(x->getRight());
    }

  }
  Nodo<H> *_rsearch(Nodo<H> *tmp, H key){
    if(!tmp) return NULL;
    if(*tmp->getKey() == key) return tmp;
    if(*tmp->getKey() < key) return _rsearch(tmp->getRight(), key);
    return _rsearch(tmp->getLeft(), key);
  }
  Nodo<H> *_minimo(Nodo<H> *x){
    while(x->getLeft()) x=x->getLeft();
    return x;
  }
  Nodo<H> *_massimo(Nodo<H> *x){
    while(x->getRight()) x=x->getRight();
    return x;
  }
  Nodo<H> *_successore(Nodo<H> *tmp){
    if(tmp->getRight()) return _minimo(tmp->getRight());
    Nodo<H> *p=tmp->getParent();
    while(p!=NULL && *p->getKey()<*tmp->getKey()) p=p->getParent();
    return p;
  }
  Nodo<H> *_predecessore(Nodo<H> *tmp){
    if(tmp->getLeft()) return _massimo(tmp->getLeft());
    Nodo<H> *p=tmp->getParent();
    while(p!=NULL && *p->getKey()>*tmp->getKey()) p=p->getParent();
    return p;
  }
  void _canc(Nodo<H> *nd, H key){
    Nodo<H> *tmp=_rsearch(nd, key);
    if(!tmp) return;
    if(!tmp->getLeft() || !tmp->getRight()){
        n--;
        Nodo<H> *p=tmp->getParent(),
                *figlio=tmp->getLeft();
        if(tmp->getRight()) figlio=tmp->getRight();
        if(!p) root=figlio;
        else{
          if(tmp == p->getLeft()) p->setLeft(figlio);
          else p->setRight(figlio);
        }
        if(figlio) figlio->setParent(p);
      }else{
        Nodo<H> *succ = _successore(tmp);
        tmp->setKey(*succ->getKey());
        tmp->setMul(succ->getMul());
        _canc(tmp->getRight(), *succ->getKey());
      }
    }
public:
  MyMultiBST(){
    root=NULL;
    n=0;
  }
  MyMultiBST<H> *ins(H key){
    Nodo<H> *tmp=_rsearch(root, key);
    if(tmp) tmp->incMul();
    else{
      tmp=root;
      Nodo<H> *nd= new Nodo<H>(key),
              *p=NULL;
      while(tmp){
        p=tmp;
        if(key>*tmp->getKey()) tmp=tmp->getRight();
        else tmp=tmp->getLeft();
      }
      if(!p) root=nd;
      else{
        if(key < *p->getKey()) p->setLeft(nd);
        else p->setRight(nd);
      }
      nd->setParent(p);
      n++;
    }
    return this;
  }
  MyMultiBST<H> *del(H key){
    Nodo<H> *tmp= _rsearch(root, key);
    if(!tmp) return this;
    tmp->decMul();
    cout << "mul of: "<<*tmp->getKey() << " is "<<tmp->getMul()<<endl;
    if(tmp->getMul() == 0) _canc(tmp, key);
    return this;
  }
  int rank(H key){
    Nodo<H> *tmp= _rsearch(root, key);
    if(!tmp) return 0;
    int r=1;
    while(_predecessore(tmp)){
      for(int i=0; i<tmp->getMul(); i++) r++;
      tmp=_predecessore(tmp);
    }
    return r+1;
  }

  int multeplicity(H key){
    Nodo<H> *tmp=_rsearch(root, key);
    if(tmp) return tmp->getMul();
    return 0;
  }

  void print(){
    _inorder(root);
    cout<<endl;

  }
};


int main(){
  MyMultiBST<int> *t =new MyMultiBST<int>();
  t->ins(10)->ins(7)->ins(7)->ins(23)->ins(30)->ins(4)->ins(1)->ins(5)->ins(9)->ins(5)->ins(1)->ins(7)->ins(1)->ins(9)->print();
  cout << t->multeplicity(9)<<endl;

  t->del(7)->del(4)->del(23)->del(7)->del(7);
  t->print();

  cout <<t->rank(5) <<endl;
  cout <<t->rank(9) <<endl;
  cout <<t->rank(30) <<endl;







  return 0;
}
