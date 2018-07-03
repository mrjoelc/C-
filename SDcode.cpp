#include<iostream>

using namespace std;

class Cab{
private:
  char cab[10];
  int fir;
public:
  Cab(char *a, int fir){
    for(int i=0; i<10; i++) cab[i]=a[i];
    this->fir=fir;
  }

  void setCab(char *a){for(int i=0; i<10; i++) cab[i]=a[i];}
  void setFir(int fir){this->fir=fir;}

  char *getCab(){return cab;}
  int getFir(){return fir;}

  void print(){
    cout <<"cab: ";
    for(int i=0; i<10; i++) cout << cab[i];
    cout<<endl;
    cout <<"fir: "<<fir;
  }
};

bool operator <(const Cab &a, const Cab&b){
  Cab s1=a;
  Cab s2=b;
  string sa=s1.getCab();
  string sb=s2.getCab();
  if(sa.compare(sb)<0) return true;
  if(sa.compare(sb)==0 && s1.getFir()<s2.getFir()) return true;
  return false;
}

bool operator >(const Cab &a, const Cab&b){
  Cab s1=a;
  Cab s2=b;
  return s2<s1;
}

bool operator ==(const Cab &a, const Cab&b){
  Cab s1=a;
  Cab s2=b;
  string sa=s1.getCab();
  string sb=s2.getCab();

  if(sa.compare(sb)==0 && s1.getFir() ==s2.getFir()) return true;
  return false;
}

bool operator !=(const Cab &a, const Cab&b){
  Cab s1=a;
  Cab s2=b;
  return !(s1==s2);
}

bool operator >=(const Cab &a, const Cab&b){
  Cab s1=a;
  Cab s2=b;
  return !(s1<s2);
}

bool operator <=(const Cab &a, const Cab&b){
  Cab s1=a;
  Cab s2=b;
  return !(s1>s2);
}

template<class H>class Nodo{
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
  void setNext(Nodo<H> *next){this->next=next;}
  void setPrev(Nodo<H> *prev){this->prev=prev;}

  H *getKey(){return key;}
  Nodo<H> *getNext(){return next;}
  Nodo<H> *getPrev(){return prev;}

};

template<class H> class Queue{
private:
  int n;
  Nodo<H> *header, *trailer, *current;
  void insertAfter(Nodo<H> *tmp, H key){
    Nodo<H> *nd=new Nodo<H>(key),
            *prev=tmp->getPrev();
    prev->setNext(nd);
    nd->setPrev(prev);
    nd->setNext(tmp);
    tmp->setPrev(nd);
    n++;
  }
public:
  Queue(){
    H *tmp=NULL;
    header=trailer=new Nodo<H>(tmp);
    header->setNext(trailer);
    trailer->setPrev(header);
    n=0;
  }

  Queue<H> *enqueue(H key){
    insertAfter(header->getNext(), key);
    return this;
  }

  Queue<H> *dequeue(){
    Nodo<H> *tmp=trailer->getPrev();
    tmp->getPrev()->setNext(trailer);
    trailer->setPrev(tmp->getPrev());
    n--;
    return this;
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
    while(has_next()) cout << *next() <<" ";
    cout <<endl;
  }
};

class SDset{
private:
  Queue<Cab> *l;
public:
  SDset(){
    l=new Queue<Cab>();
  }
  SDset *insert(Cab a){
    l->enqueue(a);
    return this;
  }
  SDset *dequeue(){
    l->dequeue();
    return this;
  }
  void print(){
    l->reset();
    while(l->has_next()){
      Cab *tmp = l->next();
      tmp->print();
      cout << endl;
    }
  }
};

int main(){
  char q[10]={'a','b','c','d','f','g','d','e','3','3'};
  char p[10]={'a','b','c','d','f','g','d','e','3','3'};
  int f=12345;
  int d=23456;
  Cab *a=new Cab(q,f);
  Cab *b=new Cab(p,d);
  // if(*a<=*b) cout <<"si!";else cout <<"no!";
  //
  // Queue<int> *coda=new Queue<int>();
  // coda->enqueue(5)->enqueue(6)->enqueue(7)->enqueue(8)->print();
  // coda->dequeue()->dequeue()->print();

  SDset *sd = new SDset();
  sd->insert(*a)->insert(*b)->dequeue();
  sd->print();


  return 0;
}
