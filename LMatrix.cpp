#include<iostream>

using namespace std;

template<class H> class LMatrix{
public:
  virtual  LMatrix<H> *set(int i, int j , H x) = 0;
  virtual  H get(int i, int j)=0;
  virtual  void reset(int i, int j)=0;
  virtual  void print()=0;
};

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
  void setNext(Nodo<H> *next){this->next=next;}
  void setPrev(Nodo<H> *prev){this->prev=prev;}

  H *getKey(){return key;}
  Nodo<H> *getNext(){return next;}
  Nodo<H> *getPrev(){return prev;}

};

template<class H> class Lista{
private:
  int n,size;
  Nodo<H> *header, *trailer, *current;

public:
  Lista(){
    H *tmp=NULL;
    header = trailer =new Nodo<H>(tmp);
    header->setNext(trailer);
    trailer->setPrev(header);
    current=NULL;
    size=0;
  }

  Lista<H> *ins(int pos, H key){
    Nodo<H> *tmp =header->getNext(),
            *nd= new Nodo<H>(key),
            *prev=NULL;
    int k = pos;
    while(tmp!=trailer && k>0) {
      tmp=tmp->getNext();
      k--;
    }
    prev=tmp->getPrev();

    prev->setNext(nd);
    nd->setPrev(prev);
    nd->setNext(tmp);
    tmp->setPrev(nd);
    size++;
    return this;
  }

  Lista<H> *set(int pos, H key){
    Nodo<H> *tmp =header->getNext(),
            *prev=NULL;
    int k = pos;
    while(k!=0) {
      tmp=tmp->getNext();
      k--;
    }
    tmp->setKey(key);
    return this;
  }

  Nodo<H> *getElement(int pos){
    Nodo<H> *tmp = header->getNext();
    for(int i=0; i!=pos; i++) tmp=tmp->getNext();
    return tmp;
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

template<class H> class MyLMatrix{
private:
  int righe, colonne;
  Lista< Lista<H> > *m;

public:
  MyLMatrix(int righe, int colonne, H init){
    this->righe=righe;
    this->colonne = colonne;
    m = new Lista< Lista<H> >();
    //creo la matrice e assegno valore init
    for(int i=0; i<righe; i++){
      //creo una nuova riga
      Lista<H> *riga = new Lista<H>();
      //la popolo
      for(int j=0; j<colonne; j++) riga->ins(j, init);
      //la inserisco
      m->ins(i, *riga);
    }
  }
  MyLMatrix<H> *set(int i, int j, H x){
    m->reset();
    Lista<H> *riga = m->next();
    for(int k=0; k!=i; k++) riga = m->next();
      riga->reset();
      riga->set(j,x);
      return this;
    }
    MyLMatrix<H> *reset(int i, int j){
      m->reset();
      Lista<H> *riga = m->next();
      for(int k=0; k!=i; k++) riga = m->next();
        riga->reset();
        riga->set(j,0);
        return this;
      }
    MyLMatrix<H> *multiply(MyLMatrix *a){
      if(colonne != a->righe) return this;
      MyLMatrix<H> *c = new MyLMatrix<H>(righe, a->colonne, 0);
      for(int i=0; i<righe; i++){
        for(int j=0; j<a->colonne; j++){
          //calcolare elemento posizone i,j
          H val=0;
          for(int k=0; k<colonne; k++){
            val+= get(i,k) * (a->get(k,j));
          }
          c->set(i,j, val);
        }
      }
      return c;
    }
   H get(int i, int j){
      m->reset();
      Lista<H> *riga = m->next();
      for(int k=0; k!=i; k++) riga = m->next();
      riga->reset();
      return *riga->getElement(j)->getKey();
   }
  int search(H key){
    int s=0;
    m->reset();
    while(m->has_next()){
      Lista<H> *riga = m->next();
      riga->reset();
      for(int i=0; riga->has_next(); i++){
        if(*riga->next() == key) s+=1;
      }
    }
    return s;
  }
  void print(){
    m->reset();
    while(m->has_next()){
      Lista<H> *riga = m->next();
      riga->reset();
      while(riga->has_next()){
        cout << *riga->next() << " ";
      }
      cout<<endl;
    }
  }
};

int main(){
  MyLMatrix<int> *m = new MyLMatrix<int>(3,4,0);
  m->set(0,0,7)->set(0,1,9)->set(0,2,1)->set(0,3,0);
  m->set(1,0,0)->set(1,1,0)->set(1,2,2)->set(1,3,3);
  m->set(2,0,6)->set(2,1,0)->set(2,2,8)->set(2,3,0);
  m->print();
  cout << m->search(0) << endl;
  cout << m->search(9) << endl;
  cout << m->search(5) << endl;

  MyLMatrix<int> *a = new MyLMatrix<int>(4,2,0);
  a->set(0,0,1)->set(0,1,2);
  a->set(1,0,0)->set(1,1,0);
  a->set(2,0,3)->set(2,1,0);
  a->set(3,0,7)->set(3,1,1);

  MyLMatrix<int> *c = m->multiply(a);
  c->print();

  return 0;
}
