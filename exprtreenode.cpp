/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

ExprTreeNode::ExprTreeNode(){
    type=""; 
    val=NULL;
    evaluated_value=NULL;
    id="";
    left=NULL;
    right=NULL;
}

ExprTreeNode::ExprTreeNode(string t,UnlimitedInt* v){
    type=t;
    UnlimitedInt* p=new UnlimitedInt(1);
    val=new UnlimitedRational(v,p);
    evaluated_value=NULL;
    id="";
    left=NULL;
    right=NULL;
}

ExprTreeNode::ExprTreeNode(string t,UnlimitedRational* v){
    type=t;
    val=v;
    evaluated_value=NULL;
    id="";
    left=NULL;
    right=NULL;
}

ExprTreeNode::~ExprTreeNode(){
    delete val;
    delete evaluated_value;
    if(left!=NULL){
        delete left;
    }
    if(right!=NULL){
        delete right;
    }
}
