#include <iostream>

 using namespace std;

 template<class H> class MSCall{
 private:
   int n;
   H *input, *output;
 public:
   MSCall(H *input, int n){
     this->input =input;
     this->n = n;
     output = NULL;
   }
   H *getInput(){return input;}
   H *getOutput(){return output;}
   void setOutput(H *output){this->output=output;}
   int getSize(){return n;}
 };

 template<class H> class Nodo{
 private:
   H *key;
   Nodo<H> *left, *right, *parent;
   Nodo();
 public:
   Nodo(H *key){
     this->key=key;
     left=right=parent=NULL;
   }
   void setKey(H *key){this->key=key;}
   void setLeft(Nodo<H> *left){this->left=left;}
   void setRight(Nodo<H> *right){this->right=right;}

   H *getKey(){return key;}
   Nodo<H> *getLeft(){return left;}
   Nodo<H> *getRight(){return right;}
 };

 template<class H> class MergeSortTree{
 private:
   int n,nrc;
   Nodo<MSCall<H> > *root;

   void _preorder(Nodo<MSCall<H> > *x){
     if(x){
       int n = x->getKey()->getSize();
       H *input = x->getKey()->getInput();
       H *output = x->getKey()->getOutput();
       for(int i=0; i<n; i++) cout << input[i] << " ";
        cout<<": ";
        for(int i=0; i<n; i++) cout << output[i] << " ";
        cout<<endl;
       _preorder(x->getLeft());
       _preorder(x->getRight());
     }
   }
   void _printInput(Nodo<MSCall<H> > *x){
     if(x){
       int n = x->getKey()->getSize();
       H *input = x->getKey()->getInput();
       for(int i=0; i<n; i++) cout << input[i] << " ";
       cout<<endl;
     }
   }
   void _printOutput(Nodo<MSCall<H> > *x){
     if(x){
       int n = x->getKey()->getSize();
       H *output = x->getKey()->getOutput();
       for(int i=0; i<n; i++) cout << output[i] << " ";
       cout<<endl;
     }
   }

 public:
   MergeSortTree(H *input, int n){
     nrc=0;
     MSCall<H> *fc = new MSCall<H>(input,n);
     root = new Nodo<MSCall<H> >(fc);
     insertRecCall(root);
   }
   void insertRecCall(Nodo<MSCall<H> > *x){
     nrc++;
     H *input = x->getKey()->getInput();
     int n = x->getKey()->getSize();
     if(n > 1){
         int mid = n/2;
         H *inp_left = new H[mid];

         //Lavora a sx
         for(int i=0; i<mid; i++) inp_left[i] = input[i];
         MSCall<H> *left_call = new MSCall<H>(inp_left, mid);
         Nodo<MSCall<H> > *left=new Nodo<MSCall<H> >(left_call);
         x->setLeft(left);
         insertRecCall(x->getLeft());

         //Lavora a dx
         H *inp_right = new H[mid];
         for(int i=0; i<n-mid; i++) inp_right[i] = input[mid+i];
         MSCall<H> *right_call = new MSCall<H>(inp_right, n-mid);
         Nodo<MSCall<H> > *right=new Nodo<MSCall<H> >(right_call);
         x->setRight(right);
         insertRecCall(x->getRight());

         //prendi dal nodo x gli output di sx e dx mergili e impostalo output del nodo x
         H* out_left = x->getLeft()->getKey()->getOutput();
         H* out_right = x->getRight()->getKey()->getOutput();
         H *output = new H[n];
         merge(output, n, out_left, mid, out_right, n-mid);
         x->getKey()->setOutput(output);
       }else{
         H *output = new H[1];
         output[0] = input[0];
         x->getKey()->setOutput(output);
       }
   }

   void merge(H* out, int n, H *left, int n_left, H *right, int n_right){
     int i=0;
     int j=0;
     int h=0;
     while(i<n_left && j<n_right){
       if(left[i]<=right[j]) out[h]=left[i++];
       else out[h]=right[j++];
       h++;
     }
     while(i<n_left) out[h++] = left[i++];
     while(j<n_right) out[h++] = right[j++];
   }
   void printInput(){
     _printInput(root);
   }
   void printOutput(){
     _printOutput(root);
   }
   int NumeroChiamateRicorsive(){return nrc;}
 };

 int main() {
   int a[14] = {7,9,1,2,8,4,10,3,5,12,15,11,23,6};
   MergeSortTree<int> *mst = new MergeSortTree<int>(a,14);
   mst->printInput();
   mst->printOutput();
   cout << mst->NumeroChiamateRicorsive();
return 0;
 }
