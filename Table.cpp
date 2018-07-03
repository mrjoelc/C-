#include<iostream>

using namespace std;

template<class H> class Nodo{
private:
  H *key;
  Nodo<H> *next, *prev;
  Nodo();

public:
  Nodo(H key){
    this->key=new H(key);
    next=prev=NULL;
  }

  Nodo(H *key){
    this->key=key;
    next=prev=NULL;
  }

  void setKey(H key){this->key=new H(key);}
  void setNext(Nodo<H> *x){next=x;}
  void setPrev(Nodo<H> *x){prev=x;}

  H *getKey(){return key;}
  Nodo<H> *getNext(){return next;}
  Nodo<H> *getPrev(){return prev;}
};

template<class H> class Lista{
protected:
  int n;
  Nodo<H> *header, *trailer, *current;

  void _insertAfter(Nodo<H> *tmp, H key){
    Nodo<H> *nd=new Nodo<H>(key),
            *prev=tmp->getPrev();
    prev->setNext(nd);
    nd->setPrev(prev);
    nd->setNext(tmp);
    tmp->setPrev(nd);
    n++;
  }

  Nodo<H> *_rsearchFromTop(Nodo<H> *tmp, H key){
    if(tmp==trailer) return NULL;
    if(*tmp->getKey() == key) return tmp;
    return _rsearchFromTop(tmp->getNext(), key);
  }

  Nodo<H> *_rsearchFromBottom(Nodo<H> *tmp, H key){
    if(tmp==header) return NULL;
    if(*tmp->getKey() == key) return tmp;
    return _rsearchFromBottom(tmp->getPrev(), key);
  }

public:
  Lista(){
    n=0;
    H *tmp=NULL;
    header=trailer=new Nodo<H>(tmp);
    header->setNext(trailer);
    trailer->setPrev(header);
  }

  Lista<H> *ins(H key){
    _insertAfter(trailer, key);
    return this;
  }

  Lista<H> *OrderedIns(H key){
    Nodo<H> *tmp=header->getNext();
    while(tmp!=trailer && *tmp->getKey()<key) tmp=tmp->getNext();
    _insertAfter(tmp, key);
    return this;
  }

  Lista<H> *del(H key){
    Nodo<H> *tmp=_rsearchFromBottom(trailer->getPrev(), key);
    if(!tmp) return this;
    tmp->getPrev()->setNext(tmp->getNext());
    tmp->getNext()->setPrev(tmp->getPrev());
    n--;
  }

  H *max(){
    if(n>0){
      Nodo<H> *tmp=header->getNext();
      H *key = tmp->getNext()->getKey();

      while(tmp!=trailer){
        if(*tmp->getKey()>*key) key=tmp->getKey();
        tmp=tmp->getNext();
      }
      return key;
    }else return NULL;
  }

  H *min(){
    if(n>0){
      Nodo<H> *tmp=header->getNext();
      H *key = tmp->getNext()->getKey();

      while(tmp!=trailer){
        if(*tmp->getKey()<*key) key=tmp->getKey();
        tmp=tmp->getNext();
      }
      return key;
    }else return NULL;
  }

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
    cout << "[ " ;
    while(has_next()) cout << *next() << " ";
    cout << " ]" <<endl;
  }

};

template<class H> class MyTable : public Lista<H>{
public:
  MyTable() : Lista<H>() {}
  MyTable<H> *insert(H key){
    Lista<H>::ins(key);
    return this;
  }
};

template<class H> class OrderedTable : public Lista<H>{
public:
  OrderedTable() : Lista<H>() {}
  OrderedTable<H> *insert(H key){
    Lista<H>::OrderedIns(key);
    return this;
  }
};

template<class H> class CircularTable{
private:
  int n;
  Nodo<H> *header, *current;

  void _insertAfter(Nodo<H> *tmp, H key){
    Nodo<H> *nd=new Nodo<H>(key),
            *prev=tmp->getPrev();
    prev->setNext(nd);
    nd->setPrev(prev);
    nd->setNext(tmp);
    tmp->setPrev(nd);
    n++;
  }

  Nodo<H> *_rsearch(Nodo<H> *tmp, H key){
    if(tmp==header) return NULL;
    if(*tmp->getKey() == key) return tmp;
    return _rsearch(tmp->getNext(), key);
  }

public:
  CircularTable(){
    n=0;
    H *tmp=NULL;
    header=new Nodo<H>(tmp);
    header->setNext(header);
    header->setPrev(header);
  }
  CircularTable<H> *insert(H key){
    Nodo<H> *nd=new Nodo<H>(key);
    Nodo<H> *tmp=header->getNext();
    int k=n;
    while(k>1) {
      tmp=tmp->getNext();
      k--;
    }
    tmp->setNext(nd);
    nd->setPrev(tmp);
    nd->setNext(header);
    header->setPrev(nd);
    n++;
    return this;
  }
  CircularTable<H> *del(H key){
    Nodo<H> *tmp=_rsearch(header->getNext(), key);
    if(!tmp) return this;
    tmp->getPrev()->setNext(tmp->getNext());
    tmp->getNext()->setPrev(tmp->getPrev());
    n--;
  }
  void reset(){current=header->getNext();}
  H *next(){
    if(has_next()){
      Nodo<H> *tmp=current;
      current=current->getNext();
      return tmp->getKey();
    }
    return NULL;
  }
  int has_next(){return current!=header;}
  void print(){
    reset();
    cout << "[ " ;
    while(has_next()) cout << *next() << " ";
    cout << " ]" <<endl;
  }
};

int main(){
  MyTable<int> *l = new MyTable<int>;
  l->insert(3)->insert(7)->insert(1)->insert(8);
  l->insert(5)->insert(2)->insert(6)->insert(1)->insert(8);
  l->del(8)->del(7)->del(1);
  cout << *l->max()<<endl;
  cout << *l->min()<<endl;
  l->print();

  cout << "_____________"<<endl;
  OrderedTable<int> *r = new OrderedTable<int>;
  r->insert(3)->insert(7)->insert(1)->insert(8);
  r->insert(5)->insert(2)->insert(6)->insert(1)->insert(8);
  r->del(8)->del(7)->del(1);
  cout << *r->max()<<endl;
  cout << *r->min()<<endl;
  r->print();

  cout << "_____________"<<endl;
  CircularTable<int> *c = new CircularTable<int>;
  c->insert(3)->insert(7)->insert(1)->insert(8);
  c->insert(5)->insert(2)->insert(6)->insert(1)->insert(8);
  c->del(8)->del(7)->del(1);
  c->print();



  return 0;
}
