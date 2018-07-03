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

  void setKey(H key){this->key=new H(key); }
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
public:
  Lista(){
    H *tmp=NULL;
    header=trailer=new Nodo<H>(tmp);
    header->setNext(trailer);
    trailer->setPrev(header);
    n=0;
  }

  Nodo<H> *ins(H key){
    Nodo<H> *tmp=header->getNext(),
            *prev=NULL,
            *nd=new Nodo<H>(key);
    while(tmp!=trailer && *tmp->getKey()<key) tmp=tmp->getNext();
    prev=tmp->getPrev();

    prev->setNext(nd);
    nd->setPrev(prev);
    nd->setNext(tmp);
    tmp->setPrev(nd);
    n++;
    return nd;
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
    while(has_next()) cout << *next() << " ";
    cout << endl;
  }
};

template<class H> class SDList : public Lista<H>{
private:
  int *A[10];

  Nodo<H> *_rsearch(Nodo<H> *tmp, H key){
    if(tmp==Lista<H>::trailer) return NULL;
    if(*tmp->getKey() == key) return tmp;
    return _rsearch(tmp->getNext(), key);
  }

public:
  SDList() : Lista<H>() {
    for(int i=0; i<10; i++) A[i]=NULL;
  };

  SDList<H> *insert(H key){
    Nodo<H> *nd = Lista<H>::ins(key);
    if(key%10!=0){
      H p = key/10;
      if(A[p]==NULL){
        A[p]= nd->getKey();
      }else{
        if(*A[p]>key) A[p]= nd->getKey();
      }
    }
    return this;
  }

  SDList<H> *del(H key){
    Nodo<H> *tmp= _rsearch(Lista<H>::header->getNext(), key);
    if(!tmp) return this;
    tmp->getNext()->setPrev(tmp->getPrev());
    tmp->getPrev()->setNext(tmp->getNext());
    if(key%10!=0){
      H p = key/10;
      if(*A[p]==key){
        A[p]= NULL;
      }
    }
    return this;
  }

  int search(H key){
    if(_rsearch(Lista<H>::header->getNext(), key)) return 1;
    else return 0;
  }

  void printShortcuts(){
    for(int i=0; i<10; i++) {
      if(A[i]==NULL) cout << "0 ";
      else cout << *A[i] << " ";
    }
  }
};


int main(){
  Lista<int> *l =new Lista<int>();
  l->ins(10);
  l->ins(4);
  l->ins(5);
  l->ins(6);
  l->print();

  SDList<int> *d= new SDList<int>();
  d->insert(7)->insert(13)->insert(2)->insert(6)->insert(9)->insert(10)->insert(21)->insert(32)->insert(4)->insert(12);
  d->print();
  d->del(7)->del(4)->del(32)->del(10)->print();
  d->printShortcuts();



  return 0;
}
