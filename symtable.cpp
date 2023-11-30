/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

SymEntry* insertRec(SymEntry* node,string k,UnlimitedRational* v);
SymEntry* removeRec(SymEntry* node, string k);
SymEntry* succussor(SymEntry* node);
SymEntry* searchRec(SymEntry* node, string k);

SymbolTable::SymbolTable(){
    size=0;
}

SymbolTable::~SymbolTable(){
    delete root;
}


void SymbolTable::insert(string k, UnlimitedRational* v) {
    root = insertRec(root, k, v);
    size++;
    return;
}

void SymbolTable::remove(string k){
    if(searchRec(root,k)->key==""){
        return;
    }
    root=removeRec(root,k);
    size--;
    return;
}

UnlimitedRational* SymbolTable::search(string k){
    SymEntry* node=searchRec(root,k);
    if(node->key==""){
        return NULL;
    }
    return node->val;
}

int SymbolTable::get_size(){
    return size;
}

SymEntry* SymbolTable::get_root(){
    return root;
}


SymEntry* insertRec(SymEntry* node,string k,UnlimitedRational* v){
    if(!node){
        return new SymEntry(k, v);
    }
    if(k<node->key){
        node->left=insertRec(node->left,k,v);
    }
    else if(k>node->key){
        node->right=insertRec(node->right,k,v);
    }
    return node;
}

SymEntry* removeRec(SymEntry* node, string k){
    if(searchRec(node,k)->key==""){
        return new SymEntry();
    }
    else{
        if (k<node->key){
            node->left=removeRec(node->left,k);
        } 
        else if(k>node->key){
            node->right=removeRec(node->right,k);
        }
        else{
            if(!node->left){
                return node->right;
            }
            else if(!node->right){
                return node->left;
            }
            else{
                SymEntry* s=succussor(node);
                node->key=s->key;
                node->val=s->val;
                node->right=removeRec(node->right,s->key);
            }
        }
        return node;
    }
}
SymEntry* succussor(SymEntry* node){
    node=node->right;
    while(node->left){
        node=node->left;
    }
    return node;
}

SymEntry* searchRec(SymEntry* node, string k){
    if(!node){
        return new SymEntry();
    }
    else if(k<node->key){
        return searchRec(node->left,k);
    } 
    else if (k>node->key){
        return searchRec(node->right,k);
    }
    else{
        return node;
    }
}





