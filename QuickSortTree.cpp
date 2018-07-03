#include <iostream>

 using namespace std;

 template <class H> class Node{
  private:
    H* in;
    H* out;
    int n_in, n_out; //dimensioni array
    Node<H> *parent, *left, *right;
  public:
    Node(H* i, int nin, H* o=0, int nout=0,
         Node<H> *p = 0, Node<H> *l = 0, Node<H> *r = 0)
 		     : in(i), n_in(nin), out(o), n_out(nout),
         parent(p), left(l), right(r) {}

    Node<H>* getParent() {return parent;}
    Node<H>* getLeft() {return left;}
    Node<H>* getRight() {return right;}
    void setParent(Node<H>* p) {parent=p;}
    void setLeft(Node<H>* l) {left=l;}
    void setRight(Node<H>* r) {right=r;}

    H* getIn() {return in;}
    H* getOut() {return out;}
    int getNIn() {return n_in;}
    int getNOut() {return n_out;}

    void setIn(H* i, int nin) {in=i; n_in=nin;}
    void setOut(H* o, int nout) {out=o; n_out=nout;}
 };

 template <class H> class MyQSTree : public QSTree{
  private:
    Node<H> *root;
    int _comp;
    void split(H* A, int na, int center,
               H* &B, int &nb, H* &C, int &nc){
        //Passare puntatore per riferimento e posizione pivot
        nb = center+1;
        nc = na-nb;
        B = new H[nb];
        C = new H[nc];
        //copio meta' di A in B l'altra in C
        for(int i=0;i<nb;i++) B[i]=A[i];
        for(int i=nb;i<na;i++) C[i-nb]=A[i];
    }
    void merge(H* A, int na, H* B, int nb, H* &C, int &nc){
        nc = na+nb;
        C = new H[nc];
        int ia = 0;
        int ib = 0;
        int ic = 0;
        while(ia<na) C[ic++]=A[ia++];
        while(ib<nb) C[ic++]=B[ib++];
    }
    //Metodo per popolare l'albero (solo input)
    Node<H>* buildInputTree(H* A, int na){
      //Se c'e un elemento (o meno)
      if(na>1){
        H *B, *C;
    	  H *tmp=cloneArray(A,na);
        int nb, nc;
    	  int piv=partition(tmp,0,na-1);
        split(tmp, na, piv, B, nb, C, nc);
        Node<H>* left_subtree = buildInputTree(B,nb);
        Node<H>* right_subtree = buildInputTree(C,nc);
        Node<H> *r;
        r = new Node<H>(A,na,0,0,0,left_subtree,right_subtree);
        left_subtree->setParent(r);
        right_subtree->setParent(r);
        return r;
      }
      else return new Node<H>(A,na);
    }

    //Metodo per inserire array di output nei nodi
    void fillOutputs(Node<H> *r){
      //Controlliamo che il nodo non sia null
      if(r!=0){
        //Controllo se sono foglie
        if(r->getLeft() && r->getRight()){
            fillOutputs(r->getLeft());
            fillOutputs(r->getRight()); //sinistro e destro
            //ottieni l'output del sottoalbero destro
            //(versione ordinata dell'array in input)
            H *A = r->getLeft()->getOut();
            int na = r->getLeft()->getNOut();
            //output del sottoalbero sinitro
            H *B = r->getRight()->getOut();
            int nb = r->getRight()->getNOut();
            H *C;
            int nc;
            //effettua un merge degli array
            //ordinati A e B
            merge(A,na,B,nb,C,nc);
            //aggiorna il valore di output del nodo corrente
            r->setOut(C,nc);
          }
    	  else{
            //nel caso in cui l'array contenga un solo valore
            //esso sia gi� ordinato. Aggiorniamo il valore in output
            r->setOut(r->getIn(),r->getNIn());
            }
        }
    }

    //Metodi richiesti
    int _height(Node<H> *node){
      if(node==0) return -1;
      int h1 = _height(node->getLeft());
      int h2 = _height(node->getRight());
      int max = (h1>h2)?h1:h2;
      return max+1;
    }

    int _countNodes(Node<H> *node){
      if(node==0) return 0;
      //conta nodi sottoalberi
      int n1 = _countNodes(node->getLeft());
      int n2 = _countNodes(node->getRight());
      //Restituisco somma
      return n1+n2+1;
    }

 	  int _comparison(Node<H> *node){
      if(node==0) return 0;
      int n1 =_comparison(node->getLeft());
      int n2 =_comparison(node->getRight());
      return n1+n2+node->getNIn();
    }

 	  //Metodi supporto QuickSort
 	  int partition(H v[], int bottom, int top){
    	H x = v[bottom];
    	int i = bottom - 1;
    	int j = top + 1;
    	do{
    		do{
          j--;
          _comp++;
        }while (x < v[j]);
    		do{
          i++;
          _comp++;
        }while (x > v[i]);
        if(i<j) scambia(v, i, j);
    	}while(i<j);
    	return j;
    }

 	  H* cloneArray(H v[], int nv){
    	H* copia=new H[nv];
    	for(int i=0; i<nv ;i++) copia[i]=v[i];
    	return copia;
    }

 	  void scambia(H v[], int x, int y){
    	H t = v[x];
    	v[x] = v[y];
    	v[y] = t;
    }

    void stampa(H v[], int n){
    	for(int i=0; i<n; i++) cout << v[i] << " ";
    	cout << endl << endl;
    }

  public:
    MyQSTree(H *A, int na){
      _comp=0;
      root = buildInputTree(A,na);
      fillOutputs(root);
    }
    void printInput(){
      H *in = root->getIn();
      int nin = root->getNIn();
      for (int i=0; i<nin; i++) cout << in[i] << " ";
      cout << endl;
    }

    void printOutput(){
      H *in = root->getOut();
      int nin = root->getNOut();
      for (int i=0; i<nin; i++) cout << in[i] << " ";
      cout << endl;
    }

    int height(){return _height(root);}
    int calls(){return _countNodes(root);}
 	  int comparison(){return _comp;}
 };


 int main() {
   int A[] = {7,9,1,2,8,4,10,3,5,12,15,11,23,6};

   MyQSTree<int> *qs = new MyQSTree<int>(A,14);

   cout << "Array in input: ";
   qs->printInput();
   cout << "Array in output: ";
   qs->printOutput();

   cout << "Altezza albero: " << qs->height() <<endl;
   cout << "Numero di chiamate: " << qs->calls() << endl;
   cout << "Numero di confronti: " << qs->comparison() << endl;

 return 0;
 }
