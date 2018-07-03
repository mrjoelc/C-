#include <iostream>

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

   void setKey(H *key){this->key=key;}
   void setNext(Nodo<H> *x){ next=x;}
   void setPrev(Nodo<H> *x){ prev=x;}

   H *getKey(){return key;}
   Nodo<H> *getNext(){return next;}
   Nodo<H> *getPrev(){return prev;}

 };

 template<class H> class Lista{
 private:
   int n;
   Nodo<H> *header, *trailer, *current;

   void _insertAfter(Nodo<H> *nodo, H key){
     Nodo<H> *nd = new Nodo<H>(key),
             *prev = nodo->getPrev();
     prev->setNext(nd);
     nd->setPrev(prev);
     nd->setNext(nodo);
     nodo->setPrev(nd);
     n++;
   }

   Nodo<H> *_rsearch(Nodo<H> *tmp, H key){
     if(tmp==trailer) return NULL;
     if(*tmp->getKey() == key) return tmp;
     return _rsearch(tmp->getNext(), key);
   }
 public:
   Lista(){
     n=0;
     H *tmp=NULL;
     header=new Nodo<H>(tmp);
     trailer=new Nodo<H>(tmp);
     header->setNext(trailer);
     trailer->setPrev(header);
   }

   Lista<H> *insert(H key){
     Nodo<H> *tmp= header->getNext();
     while(tmp!=trailer && *tmp->getKey()<key) tmp=tmp->getNext();
     _insertAfter(tmp, key);
     return this;
   }

   Lista<H> *append(H key){
     _insertAfter(trailer, key);
     return this;
   }

   Lista<H> *insertOnTop(H key){
     _insertAfter(header->getNext(), key);
     return this;
   }

   Lista<H> *remove(H key){
     Nodo<H> *tmp= _rsearch(header->getNext(), key);
     if(!tmp) return this;
     tmp->getPrev()->setNext(tmp->getNext());
     tmp->getNext()->setPrev(tmp->getPrev());
     n--;
     return this;
   }

   Lista<H> *truncate(){
     Nodo<H> *tmp= header->getNext();
     while(tmp!=trailer) tmp=tmp->getNext();
     tmp=tmp->getPrev();
     tmp->getPrev()->setNext(tmp->getNext());
     tmp->getNext()->setPrev(tmp->getPrev());
     n--;
     return this;
   }

   H *getLast(){
     Nodo<H> *tmp= header->getNext();
     while(tmp!=trailer) tmp=tmp->getNext();
     tmp=tmp->getPrev();
     return tmp->getKey();
   }

   void reset(){current=header->getNext();}
   H *next(){
     if(has_next()){
       Nodo<H> *tmp= current;
       current= current->getNext();
       return tmp->getKey();
     }
     return NULL;
   }
   int has_next(){return current!=trailer;}

   void print(){
     reset();
     while(has_next()){
       cout << *next() << ", ";
     }
     cout<<endl;
   }
 };

 class Disco{
 private:
   int d;
 public:
   Disco(int d){this->d=d;}
   int getD(){return d;}
 };

 ostream &operator << (ostream &out, Disco a){
   return out << a.getD();
 }

 bool operator ==(Disco &a, Disco &b){
   return a.getD() == b.getD();
 }

 class Paletto{
 private:
   Lista<Disco> *l;
   int n;

 public:
   Paletto(){
     l=new Lista<Disco>();
     n=0;
   }

   Paletto *add(Disco key){
     l->insertOnTop(key);
     n++;
     return this;
   }

   Disco *del(){
     Disco *d = l->getLast();
     l->remove(*d);
     n--;
     return d;
   }

   int getNumDisc(){return n;}

   Paletto *moveTo(Paletto *d){
     d->add(*del());
     return this;
   }

   void print(){
     l->print();
   }
 };

 class Hanoi{
 private:
   int n;
   Paletto *a, *b, *c;
 public:
   Hanoi(int n){
     this->n=n;
     a=new Paletto();
     b=new Paletto();
     c=new Paletto();
   }
   void moves(){
     int m=2;
     for(int i=0; i<n-1; i++) m*=2;
     cout << "il numero minimo di mosse e': " << m-1;
   }
   void solve(){
    hanoi(n,'A','B','C');
   }
   void hanoi(int m, char a, char b, char c){
      if(m == 1)  cout << "Muovi disco " << m << " da " << a << " a " << c << endl;
      else{
        hanoi(m-1, a,c,b);
        cout << "Muovi disco " << m << " da " << a << " a " << c << endl;
        hanoi(m-1,b,a,c);
      }
    }
 };


 int main() {
   Lista<float> *l = new Lista<float>();
   l->insert(4.5)->insert(2.6)->insert(5.2)->insert(3.7)->insert(1.0)->print();
   l->append(7.2)->remove(2.6)->remove(3.5)->append(7.3)->print();
   l->truncate()->truncate()->append(6.3)->remove(1.0)->print();

   Disco *d1 = new Disco(1);
   Disco *d2 = new Disco(2);
   Disco *d3 = new Disco(3);
   Paletto *a = new Paletto();
   Paletto *b = new Paletto();
   Paletto *c = new Paletto();

   a->add(*d1)->add(*d2)->add(*d3)->print();
   a->moveTo(b)->moveTo(c)->print();
   b->print();
   c->print();


   Hanoi *h = new Hanoi(3);
   h->moves();
   cout<<endl;
   h->solve();


 return 0;
 }
