//
// Implementation
//
template <typename E>         // constructor
  AVLTree<E>::AVLTree() : ST() { }

template <typename E>         // destructor
  AVLTree<E>::~AVLTree(){ }

template <typename E>                    // node height utility
  int AVLTree<E>::height(const TPos& v) const
    { return (v.isExternal() ? 0 : (*v).height()); }

template <typename E>                    // set height utility
  void AVLTree<E>::setHeight(TPos v) {
    int hl = height(v.left());
    int hr = height(v.right());
    (*v).setHeight(1 + std::max(hl, hr));            // max of left & right
  }

template <typename E>                    // is v balanced?
  bool AVLTree<E>::isBalanced(const TPos& v) const {
    int bal = height(v.left()) - height(v.right());
    return ((-1 <= bal) && (bal <= 1));
  }

template <typename E>                    // get tallest grandchild
  typename AVLTree<E>::TPos AVLTree<E>::tallGrandchild(const TPos& z) const {
    TPos zl = z.left();
    TPos zr = z.right();
    if (height(zl) >= height(zr))            // left child taller
      if (height(zl.left()) >= height(zl.right()))
        return zl.left();
      else
        return zl.right();
    else                         // right child taller
      if (height(zr.right()) >= height(zr.left()))
        return zr.right();
      else
        return zr.left();
  }


//
// ToDo
//

template <typename E>                    // remove key k entry
  void AVLTree<E>::erase(const K& k) {
    TPos v = this->finder(k, ST::root());
    if (v.isExternal()) return;
    TPos w = this->eraser(v);
    rebalance(w);
  }

template <typename E>                    // insert (k,x)
  typename AVLTree<E>::Iterator AVLTree<E>::insert(const K& k, const V& x) {
    TPos v = this->inserter(k, x);
    setHeight(v);
    rebalance(v);
    return Iterator(v);
  }
  
template <typename E>                    // rebalancing utility
  void AVLTree<E>::rebalance(const TPos& v) {
    TPos z = v;
    while (!(z == ST::root())) {
      z = z.parent();
      setHeight(z);
      if (!isBalanced(z)) {
        TPos x = tallGrandchild(z);
        z = restructure(x);
        setHeight(z.left());
        setHeight(z.right());
        setHeight(z);
      }
    }
  }

template <typename E>                // Binary Search Tree Rotation
  typename AVLTree<E>::TPos AVLTree<E>::restructure(const TPos& v) {
    AVLTree<E>::TPos c = v;
    AVLTree<E>::TPos b = c.parent();
    AVLTree<E>::TPos a = b.parent();
    AVLTree<E>::TPos temp1 = a;
    AVLTree<E>::TPos temp2 = a.parent();

    K a_key = a.v->elt.key();
    K b_key = b.v->elt.key();
    K c_key = c.v->elt.key();
    
    if(a_key < b_key){
        if(b_key < c_key)   // RR: a < b < c -> single rotation
        {
          AVLTree<E>::TPos t1;
          b.v->par = a.v->par;
          a.v->right = t1.v = b.v->left;
          b.v->left = a.v;
          a.v->par = b.v;
          c.v->par = b.v;
          t1.v->par = a.v;

          if (temp2.v->left == temp1.v)
            temp2.v->left = b.v;
          else if (temp2.v->right == temp1.v)
            temp2.v->right = b.v;
          else {
            cout << "Error:" << v.v->elt.value()<< endl;
          }
          return b;
        }else{
          AVLTree<E>::TPos t5, t6;
          c.v->par = a.v->par;
          a.v->right = t6.v = c.v->left;
          b.v->left = t5.v = c.v->right;
          c.v->left = a.v;
          c.v->right = b.v;
          a.v->par = c.v;
          b.v->par = c.v;
          t6.v->par = a.v;
          t5.v->par = b.v;

          if (temp2.v->left == temp1.v)
            temp2.v->left = c.v;
          else if (temp2.v->right == temp1.v)
            temp2.v->right = c.v;
          else {
            cout << "Error:" << v.v->elt.value()<< endl;
          }
          return c;
        }
    }else{
        if(b_key > c_key){  // LL: c < b < a
            AVLTree<E>::TPos t2;
            b.v->par = a.v->par;
            a.v->left = t2.v = b.v->right;
            b.v->right = a.v;
            a.v->par = b.v;
            c.v->par = b.v;
            t2.v->par = a.v;

            if (temp2.v->left == temp1.v)
              temp2.v->left = b.v;
            else if (temp2.v->right == temp1.v)
              temp2.v->right = b.v;
            else {
              cout << "Error:" << v.v->elt.value()<< endl;
            }
            return b;
        }else{
            AVLTree<E>::TPos t3, t4;
            c.v->par = a.v->par;
            a.v->left = t3.v = c.v->right;
            b.v->right = t4.v = c.v->left;
            c.v->right = a.v;
            c.v->left = b.v;
            b.v->par = c.v;
            a.v->par = c.v;
            t3.v->par = a.v;
            t4.v->par = b.v;

            if (temp2.v->left == temp1.v)
              temp2.v->left = c.v;
            else if (temp2.v->right == temp1.v)
              temp2.v->right = c.v;
            else {
              cout << "Error:" << v.v->elt.value()<< endl;
            }
            return c;
        }
    }
}


