/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"

UnlimitedRational::UnlimitedRational(){
    p=new UnlimitedInt(0);
    q=new UnlimitedInt(1);
}


UnlimitedRational::UnlimitedRational(UnlimitedInt* num, UnlimitedInt* den){
    UnlimitedInt* n;
    UnlimitedInt* d;
    
    if(num->to_string()[0]!='-'){
        n=new UnlimitedInt(num->to_string());
    }
    else{
        string s1=num->to_string().substr(1,num->to_string().size());
        n=new UnlimitedInt(s1);
    }
    
    if(den->to_string()[0]!='-'){
        d=new UnlimitedInt(den->to_string());
    }
    else{
        string s2=den->to_string().substr(1,den->to_string().size());
        d=new UnlimitedInt(s2);
    }
    
    bool b=true;
    if(n->get_size()>=d->get_size()){
        if(n->get_size()==d->get_size()){
            for(int i=0;i<n->get_size();i++){
                if(n->get_array()[i]>d->get_array()[i]){
                    b=false;
                    break;
                }
            }
        }
        else{
            b=false;
        }
       
    }
    if(b){
        UnlimitedInt* c=new UnlimitedInt(n->to_string());
        UnlimitedInt* u=new UnlimitedInt(1);
        while(c->to_string()!=u->to_string()){
            if(UnlimitedInt::mod(n,c)->to_string()[0]=='0' && UnlimitedInt::mod(d,c)->to_string()[0]=='0'){
                n=UnlimitedInt::div(n,c);
                d=UnlimitedInt::div(d,c);
                break;
            }
            else{
                c=UnlimitedInt::sub(c,u);
            }

        }
    }
    else{
        UnlimitedInt* c=new UnlimitedInt(d->to_string());
        UnlimitedInt* u=new UnlimitedInt(1);
        while(c->to_string()!=u->to_string()){
            if(UnlimitedInt::mod(n,c)->to_string()=="0" && UnlimitedInt::mod(d,c)->to_string()=="0"){
                n=UnlimitedInt::div(n,c);
                d=UnlimitedInt::div(d,c);
                break;
            }
            else{
                c=UnlimitedInt::sub(c,u);
            }
        }

    }
    p=UnlimitedInt::mul(n,new UnlimitedInt(num->get_sign()));
    q=UnlimitedInt::mul(d,new UnlimitedInt(den->get_sign()));
}

UnlimitedRational::~UnlimitedRational(){
    delete p;
    delete q;
}

UnlimitedInt* UnlimitedRational::get_p(){
    return p;
    
}

UnlimitedInt* UnlimitedRational::get_q(){
    return q;
    
}

string UnlimitedRational::get_p_str(){
    return p->to_string();
    
} 

string UnlimitedRational::get_q_str(){
    return q->to_string();
    
}

string UnlimitedRational::get_frac_str(){
    return p->to_string()+"/"+q->to_string();
    
} // Return the rational as "p/q"

// Rational arithmetic operations
UnlimitedRational* UnlimitedRational::add(UnlimitedRational* i1, UnlimitedRational* i2){
    UnlimitedInt* num1=new UnlimitedInt(i1->get_p_str());
    UnlimitedInt* num2=new UnlimitedInt(i2->get_p_str());
    UnlimitedInt* den1=new UnlimitedInt(i1->get_q_str());
    UnlimitedInt* den2=new UnlimitedInt(i2->get_q_str());

    UnlimitedInt* num=UnlimitedInt::add(UnlimitedInt::mul(num1,den2),UnlimitedInt::mul(num2,den1));
    UnlimitedInt* den=UnlimitedInt::mul(den1,den2);

    UnlimitedRational* result=new UnlimitedRational(num,den);

    return result;
}

UnlimitedRational* UnlimitedRational::sub(UnlimitedRational* i1, UnlimitedRational* i2){
    UnlimitedInt* num1=new UnlimitedInt(i1->get_p_str());
    UnlimitedInt* num2=new UnlimitedInt(i2->get_p_str());
    UnlimitedInt* den1=new UnlimitedInt(i1->get_q_str());
    UnlimitedInt* den2=new UnlimitedInt(i2->get_q_str());

    
    UnlimitedInt* num=UnlimitedInt::sub(UnlimitedInt::mul(num1,den2),UnlimitedInt::mul(num2,den1));
    UnlimitedInt* den=UnlimitedInt::mul(den1,den2);

    UnlimitedRational* result=new UnlimitedRational(num,den);

    return result;


}
UnlimitedRational* UnlimitedRational::mul(UnlimitedRational* i1, UnlimitedRational* i2){
    UnlimitedInt* num1=new UnlimitedInt(i1->get_p_str());
    UnlimitedInt* num2=new UnlimitedInt(i2->get_p_str());
    UnlimitedInt* den1=new UnlimitedInt(i1->get_q_str());
    UnlimitedInt* den2=new UnlimitedInt(i2->get_q_str());

    UnlimitedInt* num=UnlimitedInt::mul(num1,num2);
    UnlimitedInt* den=UnlimitedInt::mul(den1,den2);

    UnlimitedRational* result=new UnlimitedRational(num,den);

    return result;

}
UnlimitedRational* UnlimitedRational::div(UnlimitedRational* i1, UnlimitedRational* i2){
    UnlimitedInt* num1=new UnlimitedInt(i1->get_p_str());
    UnlimitedInt* num2=new UnlimitedInt(i2->get_p_str());
    UnlimitedInt* den1=new UnlimitedInt(i1->get_q_str());
    UnlimitedInt* den2=new UnlimitedInt(i2->get_q_str());

    UnlimitedInt* num=UnlimitedInt::mul(num1,den2);
    UnlimitedInt* den=UnlimitedInt::mul(den1,num2);

    UnlimitedRational* result=new UnlimitedRational(num,den);

    return result;
}
