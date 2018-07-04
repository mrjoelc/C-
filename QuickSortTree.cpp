#include<iostream>

using namespace std;

template<class H> class Nodo{
private:
  H *in, *out;
  int dim_out, dim_in;
  Nodo<H> *parent, *left, *right;

public:
  Nodo(H *i, int nin, H *o=0, int nout=0, Nodo<H> *p=0, Nodo<H> *l=0, Nodo<H> *r=0){
    in=i;
    dim_in=nin;
    dim_out=nout;
    out=o;
    parent=p;
    left=l;
    right=r;
  }

  void setParent(Nodo<H> *parent){this->parent=parent;}
  void setRight(Nodo<H> *right){this->right=right;}
  void setLeft(Nodo<H> *left){this->left=left;}
  Nodo<H> *getParent(){return parent;}
  Nodo<H> *getLeft(){return left;}
  Nodo<H> *getRight(){return right;}

  //Metodi get per array input e output con rispettive dim
  H *getIn(){return in;}
  H *getOut(){return out;}
  int getDimIn(){return dim_in;}
  int getDimOut(){return dim_out;}

  //Metodi set per input  e output
  void setIn(H *i, int nin){in=i; dim_in=nin;}
  void setOut(H *o, int nout){out=o; dim_out=nout;}

};

template<class H> class MySQTree{
private:
  Nodo<H> *root;
  int _comp;

  //suddivide un arrai A in due e copia una parte in un arrai B e l'altra in C
  void dividi(H *A, int na, int center, H* &B, int &nb, H* &C, int &nc){
    nb= center+1;
    nc=na-nb;
    B=new H[nb];
    C=new H[nc];
    for(int i=0; i<nb; i++)B[i]=A[i];
    for(int i=nb; i<na; i++)C[i-nb]=A[i];
  }

  //unisce due array in un unico array
  void unisci(H *A, int na, H *B, int nb, H* &C, int &nc){
    nc=na+nb;
    C=new H[nc];
    int ia=0;
    int ib=0;
    int ic=0;
    while(ia<na) C[ic++]=A[ia++];
    while(ib<nb) C[ic++]=B[ib++];
  }

  //costruisce l'albero a partire della root sull'array passato in input
  Nodo<H> * costruisciAlbero(H *A, int na){
    if(na>1){
      H *B, *C;
      H *tmp=copiaArray(A, na);
      int nb, nc;
      int piv=partiziona(tmp, 0, na-1);
      dividi(tmp, na, piv, B, nb, C, nc );
      //costruisci sottoalbero a dx e sx
      Nodo<H> *left_subtree = costruisciAlbero(B, nb);
      Nodo<H> *right_subtree = costruisciAlbero(C, nc);
      Nodo<H> *r;
      r=new Nodo<H>(A, na, 0,0,0,left_subtree,right_subtree);
      left_subtree->setParent(r);
      right_subtree->setParent(r);
      return r;
    }
    else return new Nodo<H>(A,na);
  }
  //riempie gli output
  void riempiOutput(Nodo<H> *r){
    if(r!=0){
      if(r->getLeft()&& r->getRight()){
        riempiOutput(r->getLeft());
        riempiOutput(r->getRight());
        H *A = r->getLeft()->getOut();
        int na=r->getLeft()->getDimOut();

        H *B = r->getRight()->getOut();
        int nb=r->getRight()->getDimOut();

        H *C;
        int nc;
        unisci(A,na,B,nb,C,nc);
        r->setOut(C,nc);
      }else r->setOut(r->getIn(), r->getDimIn());
    }
  }

  //partiziona l'array
  int partiziona(H v[], int bottom, int top){
    H x=v[bottom];
    int i=bottom-1;
    int j= top+1;
    do{
      do{
        j--;
        _comp++;
      }while(x<v[j]);
      do{
        i++;
        _comp++;
      }while(x>v[i]);
      if(i<j) scambia(v,i,j);
    }while(i<j);
    return j;
  }

  H *copiaArray(H v[], int nv){
    H *copia=new H[nv];
    for(int i=0; i<nv; i++) copia[i]=v[i];
    return copia;
  }

  void scambia(H v[], int x, int y){
    H t=v[x];
    v[x]=v[y];
    v[y]=t;
  }

  int _altezza(Nodo<H> *nodo){
    if(nodo==0) return -1;
    int h1=_height(nodo->getLeft());
    int h2=_height(nodo->getRight());
    int max = (h1<h2)?h1:h2;
    return max+1;
  }

  int _contaNodi(Nodo<H> *nodo){
    if(nodo==0) return 0;
    int n1= _countNodes(nodo->getLeft());
    int n2= _countNodes(nodo->getRight());
    return n1+n2+1;
  }

public:
  MySQTree(H *A, int na){
    _comp=0;
    root=costruisciAlbero(A, na);
    riempiOutput(root);
  }

  void printOutput(){
    H *in = root->getOut();
    int nin = root->getDimOut();
    for(int i=0; i<nin; i++) cout << in[i] << " ";
    cout<<endl;
  }

  void printInput(){
    H *in = root->getIn();
    int nin = root->getDimIn();
    for(int i=0; i<nin; i++) cout << in[i] << " ";
    cout<<endl;
  }

  int height(){return _altezza(root);}
  int calls(){return _contaNodi(root);}
  int comparison(){return _comp;}


};

int main(){
  int A[14]={7,9,1,2,8,4,10,3,5,12,15,11,23,6};
  MySQTree<int> *t = new MySQTree<int>(A, 14);
  t->printInput();
  t->printOutput();

  return 0;
}
