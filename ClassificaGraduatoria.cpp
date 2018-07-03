#include <iostream>

 using namespace std;

 class Candidato{
 private:
   int v, r, e;
   string cf;
 public:
   Candidato(string cf, int v, int r, int e){
     this->cf=cf;
     this->v=v;
     this->r=r;
     this->e=e;
   }

   void setCF(string cf){this->cf=cf;}
   void setV(int v){this->v=v;}
   void setR(int r){this->r=r;}
   void setE(int e){this->e=e;}

   string getCF(){return cf;}
   int getV(){return v;}
   int getR(){return r;}
   int getE(){return e;}
 };

 bool operator < (const Candidato&a, const Candidato&b){
   Candidato s1 = a;
   Candidato s2 = b;
   if(s1.getV()>s2.getV()) return true;
   if(s1.getV()==s2.getV() && s1.getR()>s2.getR()) return true;
   if(s1.getV()==s2.getV() && s1.getR()==s2.getR() && s1.getE()<s2.getE()) return true;
   return false;
 }

 bool operator > (const Candidato &a, const Candidato &b){
   Candidato s1 = a;
   Candidato s2 = b;
   return s2<s1;
 }

 bool operator == (const Candidato &a, const Candidato &b){
   Candidato s1 = a;
   Candidato s2 = b;
   return !(s1>s2) && !(s1<s2);
 }

 bool operator != (const Candidato &a, const Candidato &b){
   Candidato s1 = a;
   Candidato s2 = b;
   return !(s1==s2);
 }

 bool operator >= (const Candidato &a, const Candidato &b){
   Candidato s1 = a;
   Candidato s2 = b;
   return !(s1<s2);
 }

 bool operator <= (const Candidato &a, const Candidato &b){
   Candidato s1 = a;
   Candidato s2 = b;
   return !(s1>s2);
 }

 ostream &operator << (ostream &out, Candidato a){
   return out << a.getCF() << " ";
 }

 template<class H> class Nodo{
 private:
   H *key;
   Nodo<H> *next;
   Nodo();
 public:
   Nodo(H key){
     this->key=new H(key);
     next=NULL;
   }

   Nodo(H *key){
     this->key=new H(key);
     next=NULL;
   }

   void setKey(H key){this->key=new H(key);}
   void setNext(Nodo<H> *next){this->next=next;}
   H *getKey(){return key;}
   Nodo<H> *getNext(){return next;}
 };

 template<class H> class LList{
 protected:
   int n;
   Nodo<H> *head, *current;
 public:
   LList(){
     n=0;
     head=NULL;
   }

   LList<H> *ins(H key){
     Nodo<H> *tmp=head,
             *p=NULL,
             *nd= new Nodo<H>(key);
     while(tmp && *tmp->getKey()<key){
       p=tmp;
       tmp=tmp->getNext();
     }
     nd->setNext(tmp);
     if(!p) head=nd;
     else p->setNext(nd);
     n++;
     return this;
   }

   LList<H> *del(H key){
     Nodo<H> *tmp=head,
             *p=NULL;
     while(tmp && *tmp->getKey()!=key){
       p=tmp;
       tmp=tmp->getNext();
     }
     if(!tmp || *tmp->getKey()>key) return this;
     if(!p){head=tmp->getNext();}
     else {
       p->setNext(tmp->getNext());
     }
     n--;
     return this;
   }

   Nodo<H> *search(H key){
     Nodo<H> *tmp=head;
     while(tmp && *tmp->getKey()!=key) tmp=tmp->getNext();
     return tmp;
   }

   Nodo<H> *searchForGrade(int n){
     Nodo<H> *tmp=head;
     while(tmp && n>0) {
       tmp=tmp->getNext();
       n--;
     }
     return tmp;
   }

   void reset(){current=head;}
   H *next(){
     if(current){
       Nodo<H> *tmp=current;
       current=current->getNext();
       return tmp->getKey();
     }
     return NULL;
   }
   int has_next(){return current!=NULL;}

   void print(){
     reset();
     while(has_next()){
       cout<< *next() << " ";
     }
     cout<<endl;
   }
 };

 class Graduatoria : public LList<Candidato>{
 private:
 public:
   Graduatoria(){
     LList<Candidato>();
   }

   Candidato search(int n){
     Nodo<Candidato> *tmp= head;
     while(n>1){
       tmp=tmp->getNext();
       n--;
     }
     return *tmp->getKey();
   }
 };

 int main() {

   int v=89, r=60, e=27;
   Candidato *a = new Candidato("GTRSDF94SO3C351J", v, r ,e);
   Candidato *b = new Candidato("FGTSER95Y05H351T", 63, 63 ,24);
   Candidato *c = new Candidato("RYUASD93R12E353H", 89, 60 ,25);

   if(*a<*b) cout << "True" ; else cout << "False";
   cout<<endl;
   if(*a>=*b) cout << "True" ; else cout << "False";
   cout<<endl;
   if(*a==*c) cout << "True" ; else cout << "False";
   cout<<endl;
   if(*a<=*c) cout << "True" ; else cout << "False";
   cout<<endl;

   LList<int> *l =new LList<int>();
   l->ins(2)->ins(3)->ins(12)->ins(4)->ins(9)->ins(5);
   l->del(3)->del(6);
   l->print();

   Graduatoria *g =new Graduatoria();
   g->ins(*a)->ins(*b)->ins(*c);
   cout << g->search(2) << endl;
   g->print();




 return 0;
 }
