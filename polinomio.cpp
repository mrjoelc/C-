#include<iostream>

using namespace std;

class Monomio{
private:
  int d, c;
  Monomio *next, *prev;
public:
  Monomio(int d, int c){
    this->d=d;
    this->c=c;
    next=prev=NULL;
  }

  void setNext(Monomio *next){this->next=next;}
  void setPrev(Monomio *prev){this->prev=prev;}
  void setCoeff(int c){this->c=c;}
  void setGrade(int d){this->d=d;}

  Monomio *getPrev(){return prev;}
  Monomio *getNext(){return next;}
  int getCoeff(){return c;}
  int getGrade(){return d;}

  int valuta(int x){
    int val=1;
    for(int i=0; i<d; i++) val*=x;
    return c*val;
  }

  void print(){
    cout << c;
    if(d!=0) cout<< "x";
    if(d>1) cout<<"(" << d <<")";
  }
};

class Polinomio{
private:
  Monomio *header, *trailer, *current;
  int n;
public:
  Polinomio(int *a, int dim){
    n=0;
    header = new Monomio(1,1);
    trailer = new Monomio(1,1);
    header->setNext(trailer);
    trailer->setPrev(header);
    for(int i=0; i<dim; i++){
      Monomio *tmp = new Monomio(dim-i-1, a[i]);
      add(tmp);
    }
  }
  Polinomio *add(Monomio *m){
    Monomio *tmp=header->getNext(),
            *prev=NULL;
    int d=m->getGrade();
    while(tmp!=trailer && tmp->getGrade()>=m->getGrade()) {
      //controlla se già esiste un monomio dello stesso grade,eventualmente somma i coeff
      if(tmp->getGrade()==m->getGrade()){
        tmp->setCoeff(tmp->getCoeff() + m->getCoeff());
        //se il risultato della somma e' zero allora il monomio non deve più esistere
        if(tmp->getCoeff() == 0){
          tmp->getPrev()->setNext(tmp->getNext());
          tmp->getNext()->setPrev(tmp->getPrev());
        }
        return this;
      }
      tmp=tmp->getNext();
    }
    //aggiungi il nuovo nodo
    prev=tmp->getPrev();
    prev->setNext(m);
    m->setPrev(prev);
    m->setNext(tmp);
    tmp->setPrev(m);
    return this;
  }
  Polinomio *add(Polinomio *p){
    p->reset();
    while(p->has_next()){
      Monomio *tmp= p->next();
      add(tmp);
    }
  }
  void resetPolinomio(){
    header->setNext(trailer);
    trailer->setPrev(header);
  }
  Polinomio *mult(Polinomio *p){
    int w[0];
    Polinomio *q=new Polinomio(w,0);
    reset();
    while(has_next()){
      Monomio *a=next();
      int gradeA=a->getGrade();
      int coefA=a->getCoeff();
      p->reset();
      while(p->has_next()){
        Monomio *b=p->next();
        int gradeB=b->getGrade();
        int coefB=b->getCoeff();
        Monomio *c = new Monomio(gradeA+gradeB, coefA*coefB);
        q->add(c);
      }
    }
    resetPolinomio();
    add(q);
    return this;
  }


  int valuta(int x){
    reset();
    int val=0;
    while(has_next()){
       Monomio *m= next();
       val+=m->valuta(x);
     }
     return val;
  }

  void reset(){current=header->getNext();}
  Monomio *next(){
    if(has_next()){
      Monomio *m=current;
      current=current->getNext();
      return m;
    }
    return NULL;
  }
  int has_next(){return current!=trailer;}

  void print(){
    reset();
    while(has_next()){
       Monomio *m= next();
       m->print();
       if(m->getNext()!=trailer)cout<<" + ";
     }
     cout<<endl;
  }


};

int main(){

  Monomio *a =new Monomio(2,3);
  Monomio *b =new Monomio(1,-2);

  a->print();
  cout<<endl;
  b->print();

  cout<<endl;

  int c[3]={1,2,3};
  Polinomio *p = new Polinomio(c,3);
  p->add(a);
  p->add(b);
  cout<<endl;
  p->print();
  // cout<< p->valuta(2) <<endl;
  //
  int d[4]={1,-2,3,-2};
   Polinomio *q = new Polinomio(d,4);
   q->print();
   p->add(q);
   p->print();
  // cout<< p->valuta(1) <<endl;

  int A[2]={1,2};
  int B[2]={2,-2};

  Polinomio *t = new Polinomio(A,2);
  Polinomio *r = new Polinomio(B,2);
  t->mult(r);
  t->print();
  t->mult(r);
  t->print();



  return 0;
}
