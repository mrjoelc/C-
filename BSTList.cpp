#include<iostream>

using namespace std;

template<class H> class Lnodo{
private:
  H *key;
  Lnodo<H> *next, *prev;
  Lnodo();
public:
  Lnodo(H key){
    this->key=new H(key);
    next=prev=NULL;
  }

  Lnodo(H *key){
    this->key=key;
    next=prev=NULL;
  }

  void setKey(H key){this->key=new H(key);}
  void setNext(Lnodo<H> *x){next=x;}
  void setPrev(Lnodo<H> *x){prev=x;}

  H *getKey(){return key;}
  Lnodo<H> *getNext(){return next;}
  Lnodo<H> *getPrev(){return prev;}
};

template<class H> class DList{
private:
  int n;
  Lnodo<H> *header, *trailer, *current;

  void _insertAfter(Lnodo<H> *tmp, H key){
    Lnodo<H> *prev=tmp->getPrev(),
             *nd=new Lnodo<H>(key);
    prev->setNext(nd);
    nd->setPrev(prev);
    nd->setNext(tmp);
    tmp->setPrev(nd);
    n++;
  }

  Lnodo<H> *_rsearch(Lnodo<H> *tmp, H key){
    if(tmp==trailer) return NULL;
    if(*tmp->getKey() == key) return tmp;
    return _rsearch(tmp->getNext(), key);
  }

public:
  DList(){
    H *tmp=NULL;
    header=trailer=new Lnodo<H>(tmp);
    header->setNext(trailer);
    trailer->setPrev(header);
    n=0;
  }

  DList<H> *ins(H key){
    Lnodo<H> *tmp = header->getNext();
    while(tmp!=trailer && *tmp->getKey()<key) tmp=tmp->getNext();
    _insertAfter(tmp, key);
  }

  DList<H> *insOnTop(H key){
    _insertAfter(header->getNext(), key);
    return this;
  }

  DList<H> *del(H key){
    Lnodo<H> *tmp=_rsearch(header->getNext(), key);
    if(!tmp) return this;
    tmp->getPrev()->setNext(tmp->getNext());
    tmp->getNext()->setPrev(tmp->getPrev());
    n--;
    return this;
  }

  H *search(H key){
    Lnodo<H> *tmp = _rsearch(header->getNext(), key);
    if(!tmp) return NULL;
    return tmp->getKey();
  }

  void reset(){current=header->getNext();}
  H *next(){
    if(has_next()){
      Lnodo<H> *tmp=current;
      current=current->getNext();
      return tmp->getKey();
    }
    return NULL;
  }
  int has_next(){return current!=trailer;}
  void print(){
    reset();
    while(has_next()) cout << *next() << " ";
    cout<<endl;
  }
};

template<class H> class Tnodo{
private:
  H *key;
  Tnodo<H> *left, *right, *parent;
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
  void setLeft(Tnodo<H> *x){left=x;}
  void setRight(Tnodo<H> *x){right=x;}
  void setParent(Tnodo<H> *x){parent=x;}

  H *getKey(){return key;}
  Tnodo<H> *getLeft(){return left;}
  Tnodo<H> *getRight(){return right;}
  Tnodo<H> *getParent(){return parent;}
};

template<class H> class BST{
private:
  int n;
  Tnodo<H> *root, *current;

  void _inorder(Tnodo<H> *x){
    if(x){
      _inorder(x->getLeft());
      cout << *x->getKey() <<" ";
      _inorder(x->getRight());
    }
  }

  Tnodo<H> *_minimo(Tnodo<H> *x){
    while(x->getLeft()) x=x->getLeft();
    return x;
  }

  Tnodo<H> *_massimo(Tnodo<H> *x){
    while(x->getRight()) x=x->getRight();
    return x;
  }

  Tnodo<H> *_successore(Tnodo<H> *x){
    if(x->getRight()) return _minimo(x->getRight());
    Tnodo<H> *p=x->getParent();
    while(p!=NULL && *p->getKey()<*x->getKey()) p=p->getParent();
    return p;
  }

  Tnodo<H> *_rsearch(Tnodo<H> *x, H key){
    if(!x) return NULL;
    if(*x->getKey() == key) return x;
    if(key> *x->getKey()) return _rsearch(x->getRight(), key);
    return _rsearch(x->getLeft(), key);
  }

  void _canc(Tnodo<H> *nd, H key){
    Tnodo<H> *tmp=_rsearch(nd, key);
    if(!tmp) return;
    if(!tmp->getLeft() || !tmp->getRight()){
      n--;
      Tnodo<H> *figlio=tmp->getLeft(),
               *parent=tmp->getParent();
      if(tmp->getRight()) figlio=tmp->getRight();
      if(!parent) root=figlio;
      else{
        if(tmp == parent->getLeft()) parent->setLeft(figlio);
        else parent->setRight(figlio);
      }
      if(figlio) figlio->setParent(parent);
    }else{
      Tnodo<H> *succ=_successore(tmp);
      tmp->setKey(*succ->getKey());
      _canc(tmp->getRight(), *succ->getKey());
    }
  }
public:
  BST(){
    root=NULL;
    n=0;
  }

  BST<H> *ins(H key){
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
      if(key>*p->getKey()) p->setRight(nd);
      else p->setLeft(nd);
    }
    nd->setParent(p);
    n++;
    return this;
  }

  BST<H> *del(H key){
    _canc(root, key);
    return this;
  }

  H *search(H key){
    Tnodo<H> *tmp = _rsearch(root, key);
    if(!tmp) return NULL;
    return tmp->getKey();
  }

  H *minimo(){
    if(n==0) return NULL;
    Tnodo<H> *tmp = _minimo(root);
    return tmp->getKey();
  }

  int getSize(){return n;}

  H *successore(H key){
    Tnodo<H> *tmp=_rsearch(root, key);
    if(!tmp) return NULL;
    return _successore(tmp)->getKey();
  }

  void print(){
    _inorder(root);
  }
};

template<class H> bool operator>(const BST<H> &a, const BST<H> &b){
  BST<H> s1=a;
  BST<H> s2=b;
  if(s1.getSize()> s2.getSize()) return true;
  if(s1.getSize()== s2.getSize() && *s1.minimo()>*s2.minimo()) return true;
  return false;
}

template<class H> bool operator<(const BST<H> &a, const BST<H> &b){
  BST<H> s1=a;
  BST<H> s2=b;
  return s2>s1;
}

template<class H> bool operator==(const BST<H> &a, const BST<H> &b){
  BST<H> s1=a;
  BST<H> s2=b;
  if(s1.getSize()== s2.getSize() && *s1.minimo()==*s2.minimo()) return true;
  return false;
}

template<class H> class BSTList{
private:
  DList< BST<H> > *l;
  int k;
public:
  BSTList(int k){
    l=new DList< BST<H> >();
    this->k=k;
  }

  BSTList<H> *ins(H key){
    l->reset();
    BST<H> *tmp= l->next();
    if(tmp && tmp->getSize()>0 && tmp->getSize() < k){
      tmp->ins(key);
      l->del(*tmp);
      l->ins(*tmp);
    }else{
      BST<H> *newtree= new BST<H>();
      newtree->ins(key);
      l->insOnTop(*newtree);
    }
    return this;
  }

  BSTList<H> *canc(H key){
    l->reset();
    while(l->has_next()){
      BST<H> *tmp=l->next();
      tmp->del(key);
      l->del(*tmp);
      if(tmp->getSize()!=0) l->ins(*tmp);
    }
    return this;
  }

  void print(){
    l->reset();
    while(l->has_next()){
      BST<H> *tmp=l->next();
      tmp->print();
    }

  }
};

int main(){
  DList<int> *l=new DList<int>();
  l->ins(3)->ins(7)->ins(1)->ins(8)->ins(2)->ins(4)->print();
  l->del(3)->del(9)->del(5)->del(1)->ins(10)->ins(5)->print();
  if(l->search(5)) cout <<"L'elemento 5 è presente"; else cout <<"L'elemento 5 non è presente";
  cout<<endl;
  if(l->search(3)) cout <<"L'elemento 3 è presente"; else cout <<"L'elemento 3 non è presente";
  cout<<endl;

  BST<int> *t=new  BST<int>();
  t->ins(3)->ins(7)->ins(1)->ins(8)->ins(2)->ins(4)->print();
  t->del(3)->del(9)->del(5)->del(1);
  t->ins(10)->ins(5)->print();
  if(t->search(5)) cout <<"L'elemento 5 è presente"; else cout <<"L'elemento 5 non è presente";
  cout<<endl;
  if(t->search(3)) cout <<"L'elemento 3 è presente"; else cout <<"L'elemento 3 non è presente";
  cout<<endl;
  int *r=t->minimo();
  if(r) cout << "il val piu piccolo e': " << *r<<endl;
  r=t->successore(5);
  if(r) cout << "il successore di 5 e': " << *r<<endl;
  r=t->successore(3);
  if(r) cout << "il successore di 3 e': " << *r<<endl;

  BSTList<int> *b = new BSTList<int>(4);
  b->ins(3)->ins(7)->ins(1)->ins(8)->ins(3)->ins(4)->print();
  cout<<endl;
  b->ins(8)->ins(6)->ins(2)->ins(4)->ins(6)->ins(3)->print();
  cout<<endl;
  b->canc(3)->canc(9)->canc(5)->canc(1)->ins(10)->ins(5)->print();
  cout<<endl;




  return 0;
}
