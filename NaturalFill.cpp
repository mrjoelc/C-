void naturalFill(H *V){
  int i=0;
  Nodo<H> *tmp=minimo(root);
  while(tmp){
    tmp->setKey(V[i++]);
    tmp=successore(tmp);
  }
}
