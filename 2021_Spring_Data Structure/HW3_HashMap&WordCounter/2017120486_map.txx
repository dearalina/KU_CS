/** 
  * Assignment 3 for COSE213 Data Structures
  *
  * Won-Ki Jeong (wkjeong@korea.ac.kr)
  *
  * 2021. 5. 9
  *
  */

// destructor
template<class HashMapElemType>
HashMap<HashMapElemType>::~HashMap() {
    for (int i = 0; i < capacity; i++) {
        if (ht[i]) {
            HashMapElemType *pre = NULL;
            HashMapElemType *cur = ht[i];
            while (cur) {
                pre = cur;
                cur = cur->link;
                delete pre;
            }
        }
    }
    delete[] ht;
}

template<class HashMapElemType>
HashMapElemType *
HashMap<HashMapElemType>::find(const KeyType k) {
    int hash_val = hashfunction(k);
    HashMapElemType *temp = ht[hash_val];
    if (!temp) return NULL;
    while (temp && temp->key != k) {
        temp = temp->link;
    }
    return temp;
}

template<class HashMapElemType>
void
HashMap<HashMapElemType>::insert(const KeyType k, const ValType v) {
    HashMapElemType *p = new HashMapElemType;
    p->key = k;
    p->val = v;
    p->link = NULL;

    int hash_val = hashfunction(k);
    HashMapElemType *temp = ht[hash_val];
    if (!temp) {
        ht[hash_val] = p;
        mapsize++;
        return;
    }

    while (temp->link) {
        if (temp->key != k) {
            temp = temp->link;
            //mapsize++;
        } else {
            temp->val = v;
            return;
        }
    }

    if (temp->key == k) {
        temp->val = v;
    } else {
        temp->link = p;
        mapsize++;
    }
}

template<class HashMapElemType>
bool
HashMap<HashMapElemType>::remove(const KeyType k) {
    HashMapElemType *temp = ht[hashfunction(k)];

    if (!temp) return false;

    HashMapElemType *pre = NULL;
    while (temp && temp->key != k) {
        pre = temp;
        temp = temp->link;
    }

    // cannot find k
    if (!temp) return false;

    if (temp->key == k) {
        pre->link = temp->link;
        mapsize--;
        delete temp;
    }
    return true;
}

template<class HashMapElemType>
unsigned int
HashMap<HashMapElemType>::hashfunction(const KeyType k) {
    int hash_val = 0;
    for (int i = 0; i < k.size(); i++) {
        while (k[i]) {
            hash_val += k[i++];
            hash_val += ((int) k[i]) << 8;
        }
    }
    hash_val = hash_val % divisor;
    return hash_val;
}

template<class HashMapElemType>
void
HashMap<HashMapElemType>::print() {
    HashMapElemType *arr[mapsize];
    int j = 0;

    for (int i = 0; i < capacity; i++) {
        if (ht[i]) {
            HashMapElemType *temp = ht[i];
            while (temp) {
                arr[j++] = temp;
                temp = temp->link;
            }
        }
    }
    for (int p = 0; p < mapsize - 1; p++) {
        for (int q = 0; q < mapsize - p - 1; q++) {
            if (arr[q]->val < arr[q + 1]->val) {
                HashMapElemType *ptr = arr[q];
                arr[q] = arr[q + 1];
                arr[q + 1] = ptr;
            }
        }
    }

    for (int i = 0; i < mapsize; i++) {
        std::cout << arr[i]->key << ":" << arr[i]->val << "\n";
    }
}