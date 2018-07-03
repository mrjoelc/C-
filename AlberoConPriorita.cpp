#include <iostream>

 using namespace std;

 template<class H> class Nodo{
 private:
   H *key;
   int p;
   Nodo<H> *left, *right, *parent;
   Nodo();
 public:
   Nodo(int p,H key){
     this->key=new H(key);
     this->p=p;
     parent=right=left=NULL;
   }

   void setKey(H key){this->key=new H(key);}
   void setLeft(Nodo<H> *x){left=x;}
   void setRight(Nodo<H> *x){right=x;}
   void setParent(Nodo<H> *x){parent=x;}
   void setPriority(int x){p=x;}

   H *getKey(){return key;}
   Nodo<H> *getLeft(){return left;}
   Nodo<H> *getRight(){return right;}
   Nodo<H> *getParent(){return parent;}
   int getPriority(){return p;}
 };

 template<class H> class PBT{
 private:
   int n;
   Nodo<H> *root, *current;

   void _inoderReverse(Nodo<H> *x){
     if(x){
       _inoderReverse(x->getRight());
       cout << *x->getKey() << ", ";
       _inoderReverse(x->getLeft());
     }
   }

   Nodo<H> *_rfind(int p, Nodo<H> *tmp){
     if(!tmp) return NULL;
     if(p == tmp->getPriority()) return tmp;
     if(p > tmp->getPriority()) return _rfind(p, tmp->getRight());
     return _rfind(p, tmp->getLeft());
   }

   Nodo<H> *_rsearch(H key, Nodo<H> *tmp){
     if(!tmp) return NULL;
     if(key == *tmp->getKey()) return tmp;
     if(key > *tmp->getKey()) return _rsearch(key, tmp->getRight());
     return _rsearch(key, tmp->getLeft());
   }

   Nodo<H> *_minimo(Nodo<H> *tmp){
     while(tmp->getLeft()) tmp=tmp->getLeft();
     return tmp;
   }

   Nodo<H>* _successore(Nodo<H>* tmp) {
     if(tmp->getRight())
       return _minimo(tmp->getRight());
     Nodo<H> *p = tmp->getParent();
     while(p!=NULL && *p->getKey()<*tmp->getKey())
       p = p->getParent();
     return p;
   }

   void _canc(Nodo<H> *nd, H key){
     Nodo<H> *tmp = _rsearch(key, nd);
     if(!tmp) return;
     if(!tmp->getLeft() || !tmp->getRight()){
       n--;
       Nodo<H> *parent = tmp->getParent(),
               *figlio = tmp->getLeft();
       if(tmp->getRight()) figlio= tmp->getRight();
      if(!parent) root = figlio;
      else{
        if(tmp == parent->getLeft()) parent->setLeft(figlio);
        else parent->setRight(figlio);
      }
      if(figlio) figlio->setParent(parent);
    }else{
      Nodo<H> *succ = _successore(tmp);
      tmp->setKey(*succ->getKey());
      tmp->setPriority(succ->getPriority());
      _canc(tmp->getRight(), *succ->getKey());

    }
    return;
   }

 public:
   PBT(){
     root=NULL;
     n=0;
   }

   PBT<H> *insert(int p, H key){
     Nodo<H> *tmp=root,
             *parent=NULL,
             *nd=new Nodo<H>(p,key);
     while(tmp){
       parent=tmp;
       if(p == tmp->getPriority()) return this;
       if(p>tmp->getPriority()) tmp=tmp->getRight();
       else tmp=tmp->getLeft();
     }
     if(!parent){
       root=nd;
     }else{
       if(p > parent->getPriority()) parent->setRight(nd);
       else parent->setLeft(nd);
     }
     n++;
     return this;
   }

   PBT<H> *del(H key){
     _canc(root, key);
     return this;
   }

   void print(){
     _inoderReverse(root);
     cout << endl;
   }

   H find(int p){
     Nodo<H> *tmp = _rfind(p, root);
     if(!tmp) return 0;
     return *tmp->getKey();
   }



 };


 int main() {
   PBT<int>  *p= new PBT<int>();
   p->insert(10,5)->insert(7,3)->insert(8,13)->insert(13,1)->insert(6,2)->insert(9,7)->print();
   p->del(13)->del(1)->print();

 return 0;
 }
