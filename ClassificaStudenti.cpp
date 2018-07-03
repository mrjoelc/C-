#include <iostream>

 using namespace std;

 //****STUDENTE****//

 class Studente{
 private:
   int v, r, e;
   string matricola;
 public:
   Studente(string matricola, int v, int r, int e){
     this->matricola = matricola;
     this->v=v;
     this->r=r;
     this->e=e;
   }

   string getMatricola(){return matricola;}
   int getVoto(){return v;}
   int getRispCorrette(){return r;}
   int getEta(){return e;}

   void setMatricola(string matricola){this->matricola=matricola;}
   void setVoto(int v){this->v=v;}
   void setRispCorrette(int r){this->r=r;}
   void setEta(int e){this->e=e;}
 };

 bool operator < (const Studente& a, const Studente& b){
    Studente s1 = a;
    Studente s2 = b;

    if(s1.getVoto()>s2.getVoto()) return true;
    if(s1.getVoto()==s2.getVoto() && s1.getRispCorrette()>s2.getRispCorrette()) return true;
    if(s1.getVoto()==s2.getVoto() && s1.getRispCorrette()==s2.getRispCorrette() && s1.getEta()<s2.getEta()) return true;
    return false;
 }

 bool operator > (const Studente& a, const Studente& b){
    Studente s1 = a;
    Studente s2 = b;

    return (s2<s1);
 }

 bool operator == (const Studente& a, const Studente& b){
    Studente s1 = a;
    Studente s2 = b;

    return !(s1>s2) && !(s1<s2);
 }

 bool operator != (const Studente& a, const Studente& b){
    Studente s1 = a;
    Studente s2 = b;

    return !(s1==s2);
 }

 bool operator <= (const Studente& a, const Studente& b){
    Studente s1 = a;
    Studente s2 = b;

    return !(s1>s2);
 }

 bool operator >= (const Studente& a, const Studente& b){
    Studente s1 = a;
    Studente s2 = b;

    return !(s1<s2);
 }

 ostream &operator << (ostream &out, Studente x){
   return out << x.getMatricola();
 }


//****BST TREE****//
 template<class H> class Nodo{
 private:
   H *key;
   Nodo<H> *left, *right, *parent;
   Nodo();
 public:
   Nodo(H *key){
     this->key = key;
     left=right=parent=NULL;
   }
   Nodo(H key){
     this->key = new H(key);
     left=right=parent=NULL;
   }

   void setKey(H key){this->key= new H(key);}
   void setLeft(Nodo<H> *left){this->left=left;}
   void setRight(Nodo<H> *right){this->right=right;}
   void setParent(Nodo<H> *parent){this->parent=parent;}

   H *getKey(){return key;}
   Nodo<H> *getLeft(){return left;}
   Nodo<H> *getRight(){return right;}
   Nodo<H> *getParent(){return parent;}
 };

 template<class H> class BST{
 private:
   Nodo<H> *root;

   Nodo<H> *_search(Nodo<H> *tmp, H key){
     if(!tmp) return NULL;
     if(*tmp->getKey() == key) return tmp;
     if(key> *tmp->getKey()) return _search(tmp->getRight(), key);
     return _search(tmp->getLeft(), key);
   }

   void _inorder(Nodo<H> *x){
     if(x){
       _inorder(x->getLeft());
       cout << *x->getKey() <<" ";
       _inorder(x->getRight());
     }
   }

   Nodo<H> *_minimo(Nodo<H> *x){
     while(x->getLeft()) x= x->getLeft();
     return x;
   }

 public:
   BST(){
     root=NULL;
   }

   BST<H> *ins(H key){
     Nodo<H> *tmp =root,
             *p=NULL,
             *nd= new Nodo<H>(key);
     while(tmp){
       p=tmp;
       if(key>*tmp->getKey()) tmp=tmp->getRight();
       else tmp=tmp->getLeft();
     }
     if(!p){
       root=nd;
       return this;
     }
     if(key > *p->getKey()) p->setRight(nd);
     else p->setLeft(nd);
     nd->setParent(p);
     return this;
   }

   Nodo<H> *search(H key){
     return _search(root, key);
   }

   void print(){
     _inorder(root);
   }

   Nodo<H> *minimo(){
     return _minimo(root);
   }


 };

 //****VALUTAZIONE****//

 class Valutazione : public BST<Studente>{
 private:

 public:
   Valutazione(){
     BST<Studente>();
   }

   string search(int n){
     Nodo<Studente> *tmp = minimo();
     while(n>1){
       tmp=tmp->getParent();
       n--;
     }
     return tmp->getKey()->getMatricola();
   }


 };




 int main() {
   int v=89, r=60, e=27;
      Studente *a = new Studente("X81000123", v, r, e);
      Studente *b = new Studente("X81000452", 63, 63, 24);
      Studente *c = new Studente("X81000104", 89, 60, 25);
      if( *a < *b) cout << "True"; else cout << "False"; cout<<endl;
      if( *a >= *b) cout << "True"; else cout << "False"; cout<<endl;
      if( *a == *c) cout << "True"; else cout << "False"; cout<<endl;
      if( *a <= *c) cout << "True"; else cout << "False"; cout<<endl;

   BST<int> *t = new BST<int>();
   t->ins(2)->ins(3)->ins(12)->ins(4)->ins(9)->ins(5);
   t->print();

   cout << endl;

   Valutazione *vlt = new Valutazione();
   vlt->ins(*a)->ins(*b)->ins(*c);
   cout << vlt->search(2);
   cout<<endl;
   vlt->print();




 return 0;
 }
