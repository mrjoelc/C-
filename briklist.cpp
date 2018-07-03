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
  Nodo<H> *trailer, *header, *current;

  Nodo<H> *_rsearch(Nodo<H> *tmp, H key){
    if(tmp == trailer ) return NULL;
    if(*tmp->getKey() == key) return tmp;
    return _rsearch(tmp->getNext(), key);
  }

  void _insertAfter(Nodo<H> *tmp, H key){
    Nodo<H> *prec=tmp->getPrev(),
            *nd = new Nodo<H>(key);
    prec->setNext(nd);
    nd->setPrev(prec);
    nd->setNext(tmp);
    tmp->setPrev(nd);
    n++;
  }

public:
  Lista(){
    n=0;
    H *tmp=NULL;
    header= new Nodo<H>(tmp);
    trailer=new Nodo<H>(tmp);
    header->setNext(trailer);
    trailer->setPrev(header);
  }

  Nodo<H> *getHead(){return header->getNext();}

  Lista<H> *ins(H key){
    Nodo<H> *tmp=header->getNext();
    while(tmp!=trailer && key>*tmp->getKey()) tmp=tmp->getNext();
    _insertAfter(tmp,key);
    return this;
  }

  Lista<H> *canc(H key){
    Nodo<H> *tmp = _rsearch(header->getNext(), key);
    if(!tmp) return this;
    tmp->getPrev()->setNext(tmp->getNext());
    tmp->getNext()->setPrev(tmp->getPrev());
    n--;
  }

  Lista<H> *cancPrimo(){
    Nodo<H> *primo = header->getNext();
    primo->getPrev()->setNext(primo->getNext());
    primo->getNext()->setPrev(header);
    n--;
    return this;
  }

  void reset(){current=header->getNext();}
  H *next(){
    if(hasnext()){
      Nodo<H> *tmp = current;
      current=current->getNext();
      return tmp->getKey();
    }
    return NULL;
  }
  int hasnext(){return current!=trailer;}

  void print(){
    reset();
    while(hasnext()) cout << *next() << " ";
    cout << endl;
  }

};

template<class H> class Coda : public Lista<H>{
private:
  H somma;
  int quantita;

public:
  Coda(){
    Lista<H>();
    somma=0;
    quantita=0;
  }

  Coda<H> *push(H key){
    Lista<H>::_insertAfter(Lista<H>::trailer, key);
    somma+=key;
    quantita++;
    return this;
  }

  H *pop(){
    Nodo<H> *primo = Lista<H>::header->getNext();
    Lista<H>::cancPrimo();
    somma-= *primo->getKey();
    quantita--;
    return primo->getKey();
  }

  H getSomma(){return somma;}
  int getQuantita(){return quantita;}
  H getTesta(){return *Lista<H>::header->getNext()->getKey();}
};

template<class H> bool operator >(const Coda<H> &a, const Coda<H> &b){
  Coda<H> s1=a;
  Coda<H> s2=b;

  if(s1.getSomma() > s2.getSomma()) return true;
  if(s1.getSomma() == s2.getSomma() && s1.getQuantita() > s2.getQuantita()) return true;
  if(s1.getSomma() == s2.getSomma() && s1.getQuantita() == s2.getQuantita() && s1.getTesta()>s2.getTesta()) return true;
  return false;
}

template<class H> bool operator ==(const Coda<H> &a, const Coda<H> &b){
  Coda<H> s1=a;
  Coda<H> s2=b;

  if(s1.getSomma() == s2.getSomma() && s1.getQuantita() == s2.getQuantita() && s1.getTesta()==s2.getTesta()) return true;
  return false;
}

template<class H> class BrikList{
private:
  Lista< Coda<H> > *bl;
public:
  BrikList(){
    bl = new Lista<Coda<H> >();
  }

  BrikList<H>* ins(H x){
    Coda<H>* c=new Coda<H>();
    c->push(x);
    bl->ins(*c);
    return this;
  }

  BrikList<H>* push(H x){
    Nodo< Coda<H> >* head=bl->getHead();
    head->getKey()->push(x);
    Coda<H>* tmp= head->getKey();
    bl->canc(*head->getKey());
    bl->ins(*tmp);
    return this;
  }

  H* pop(){
    Nodo< Coda<H> >* head=bl->getHead();
    H* val=head->getKey()->pop();
    if(head->getKey()->getQuantita() == 0){
      bl->cancPrimo();
    }
    return val;
  }

  void print(){
    bl->reset();
    while(bl->hasnext()){
      Coda<H> *c = bl->next();
      c->print();
    }
  }

};

int main(){
  Lista<int> *l = new Lista<int>();
  l->ins(1)->ins(2)->ins(3)->ins(5)->ins(6)->print();

  Coda<int> *c = new Coda<int>();
  c->push(1)->push(2)->push(3)->push(4)->push(5)->push(6)->print();
  c->pop();
  c->pop();
  c->pop();
  c->print();

  cout<<endl<<endl;
  BrikList<int> *br = new BrikList<int>();
  br->ins(15)->ins(12)->ins(6)->ins(9)->ins(10)->ins(4)->ins(2)->ins(30)->ins(23)->ins(11)->print();
  cout << endl;
  br->push(*br->pop());
  br->push(*br->pop());
  br->push(*br->pop());
  br->push(*br->pop())->print();

return 0;
}
