/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"

Evaluator::Evaluator(){
    symtable=new SymbolTable();
}

Evaluator::~Evaluator(){
    // for(ExprTreeNode* node:expr_trees){
    //     delete node;
    // }
    // delete symtable;
}


void Evaluator::parse(vector<string> code) {
    vector<ExprTreeNode*> parseStack;

    for (const string& token : code) {
        if (token == "(") {
            ExprTreeNode* n=new ExprTreeNode();
            n->left=NULL;
            n->right=NULL;
            n->type="PLACEHOLDER";
            n->evaluated_value=NULL;
            n->val=NULL;
            parseStack.push_back(n);
        } 
        else if (token == ")") {
            ExprTreeNode* n=new ExprTreeNode();
            while (!parseStack.empty() && parseStack[parseStack.size()-1]->type != "PLACEHOLDER") {
                if(parseStack[parseStack.size()-2]->type=="PLACEHOLDER"){
                    n=parseStack[parseStack.size()-1];
                    parseStack.pop_back();
                }
                else{
                    ExprTreeNode* rightOperand = parseStack[parseStack.size()-1];
                    parseStack.pop_back();
            
                    ExprTreeNode* operatorNode = parseStack[parseStack.size()-1];
                    parseStack.pop_back();

                    ExprTreeNode* leftOperand = parseStack[parseStack.size()-1];
                    parseStack.pop_back();

                    operatorNode->left = leftOperand;
                    operatorNode->right = rightOperand;
                    n=operatorNode;
                    UnlimitedRational* a=new UnlimitedRational();
                    UnlimitedRational* b=new UnlimitedRational();
                    if(leftOperand->type=="VAL" ||  leftOperand->type=="VAR"){
                        a=leftOperand->val;
                    }
                    else{
                        a=leftOperand->evaluated_value;
                    }
                    if(rightOperand->type=="VAL"  ||  rightOperand->type=="VAR"){
                        b=rightOperand->val;
                    }
                    else{
                        b=rightOperand->evaluated_value;
                    }

                    if(n->type=="ADD"){
                        n->evaluated_value=UnlimitedRational::add(a,b);
                    }
                    if(n->type=="SUB"){
                        n->evaluated_value=UnlimitedRational::sub(a,b);
                    }
                    if(n->type=="MUL"){
                        n->evaluated_value=UnlimitedRational::mul(a,b);
                    }
                    if(n->type=="DIV"){
                        n->evaluated_value=UnlimitedRational::div(a,b);
                    }
                }
            }
            
            parseStack.pop_back();
            parseStack.push_back(n);
        } 
        else {
            if (token == "+" || token == "-" || token == "*" || token == "/" || token == ":=" ) {
                ExprTreeNode* operatorNode=new ExprTreeNode();
                if(token=="+"){
                    operatorNode->type="ADD";
                }
                if(token=="-"){
                    operatorNode->type="SUB";
                }
                if(token=="/"){
                    operatorNode->type="DIV";
                }
                if(token=="*"){
                    operatorNode->type="MUL";
                }
                if(token==":="){
                    operatorNode->type="ROOT";
                }
                operatorNode->id="";
                operatorNode->left=NULL;
                operatorNode->right=NULL;
                operatorNode->evaluated_value=NULL;
                operatorNode->val=NULL;
                parseStack.push_back(operatorNode);
            } 
            else {
                ExprTreeNode* operandNode=new ExprTreeNode();
                bool isd=true;
                for(int i=0;i<token.size();i++){
                    if(isdigit(token[i])==false){
                        UnlimitedRational* value=symtable->search(token);
                        if(!value){
                            operandNode->id=token;
                            operandNode->left=NULL;
                            operandNode->right=NULL;
                            operandNode->type="VAR";
                            operandNode->evaluated_value=NULL;
                            operandNode->val=NULL;
                            isd=false;
                            break;
                        }
                        else{
                            for(int k=0;k<expr_trees.size();k++){
                                if(expr_trees[k]->left->id==token){
                                    operandNode=expr_trees[k]->left;
                                    break;
                                }

                            }
                            isd=false;
                            break;
                        }
                    }
                }
                if(isd){
                    // operandNode = new ExprTreeNode("VAL", new UnlimitedInt(token));
                    operandNode->id="";
                    operandNode->left=NULL;
                    operandNode->right=NULL;
                    operandNode->type="VAL";
                    operandNode->evaluated_value=new UnlimitedRational(new UnlimitedInt(token),new UnlimitedInt("1"));
                    operandNode->val=new UnlimitedRational(new UnlimitedInt(token),new UnlimitedInt("1")); 
                }
                parseStack.push_back(operandNode);
            }
        }
    }
    //expr_trees.push_back(parseStack[1]);
    if (!parseStack.empty()) {
        ExprTreeNode* root = parseStack[parseStack.size()-2];
        root->left=parseStack[parseStack.size()-3];
        root->right=parseStack[parseStack.size()-1];
        expr_trees.push_back(root);
        for(int i=0;i<3;i++){
            parseStack.pop_back();
        }
    }
    return;


}

void Evaluator::eval() {
    if (expr_trees.empty()) {
        return;
    }

    ExprTreeNode* r = expr_trees.back();

    r->left->evaluated_value=r->right->evaluated_value;
    r->left->val=r->right->evaluated_value;
    r->evaluated_value=r->right->evaluated_value;
    symtable->insert(r->left->id,r->left->evaluated_value);
    return;
}

