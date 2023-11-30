/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"

UnlimitedInt::UnlimitedInt() {
    size = 1;
    sign = 1;
    capacity = 10;
    unlimited_int = new int[capacity]();
    unlimited_int[0]=0;
}

UnlimitedInt::UnlimitedInt(string s) {
    UnlimitedInt* res=new UnlimitedInt(std::stoi(s));
    size=res->get_size();
    sign=res->get_sign();
    capacity=res->get_capacity();
    unlimited_int = new int[capacity]();
    for(int i=0;i<size;++i){
        unlimited_int[i]=res->get_array()[i];
    }

}

UnlimitedInt::UnlimitedInt(int i) {
    if(i==0){
        size=1;
        sign=1;
        capacity = max(2*size, 10);
        unlimited_int = new int[capacity]();
    }
    else if(i<0){
        sign=-1;
        int s=-1*i;
        int p=0;
        while(s>0){
            p++;
            s=s/10;
        }
        size=p;
        capacity= max(2*size, 10);
        unlimited_int = new int[capacity]();
        s=abs(i);
        int j=size-1;
        while(s>0){
            unlimited_int[j]=s%10;
            s=s/10;
            j--;
        }

    }
    else{
        sign=1;
        int s=i;
        int p=0;
        while(s>0){
            p++;
            s=s/10;
        }
        size=p;
        capacity= max(2*size, 10);
        unlimited_int = new int[capacity]();
        s=abs(i);
        int j=size-1;
        while(s>0){
            unlimited_int[j]=s%10;
            s=s/10;
            j--;
        }


    }

}

UnlimitedInt::~UnlimitedInt() {
    delete[] unlimited_int;
}

int UnlimitedInt::get_size() {
    return size;
}

int* UnlimitedInt::get_array() {
    return unlimited_int;
}

int UnlimitedInt::get_sign() {
    return sign;
}
int UnlimitedInt::get_capacity(){
    return max(2*size,10);
}

UnlimitedInt* UnlimitedInt::add(UnlimitedInt* i1, UnlimitedInt* i2) {
    int sign1 = i1->get_sign();
    int sign2 = i2->get_sign();

    int s1=i1->get_size();
    int s2=i2->get_size();

    UnlimitedInt* result;
    string s="";

    if(sign1==sign2){
        int i=s1-1;
        int j=s2-1;
        int c=0;
        int sum;
        while(i>=0 && j>=0){
            sum=c+i1->get_array()[i]+i2->get_array()[j];
            c=sum/10;
            s=std::to_string(sum%10)+s;
            i--;
            j--;
        }
        while(i>=0){
            sum=c+i1->get_array()[i];
            c=sum/10;
            s=std::to_string(sum%10)+s;
            i--;
        }
        while(j>=0){
            sum=c+i2->get_array()[j];
            c=sum/10;
            s=std::to_string(sum%10)+s;
            j--;
        }
        if(c!=0){
            s=std::to_string(c)+s;
        }
        if(sign1<0){
            s="-"+s;
        }
        result=new UnlimitedInt(s);
    }
    else{
        if(s1>s2){
            int i=s1-1;
            int j=s2-1;
            int sum;
            while(i>=0 && j>=0){
                if(i1->get_array()[i]>=i2->get_array()[j]){
                    sum=i1->get_array()[i]-i2->get_array()[j];
                    s=std::to_string(sum%10)+s;
                    i--;
                    j--;
                }
                else{
                    int k=i-1;
                    while(i1->get_array()[k]==0){
                        k=k-1;
                    }
                    while(k!=i){
                        i1->get_array()[k]=i1->get_array()[k]-1;
                        k++;
                        i1->get_array()[k]=i1->get_array()[k]+10;
                    }
                    sum=i1->get_array()[i]-i2->get_array()[j];
                    s=std::to_string(sum%10)+s;
                    i--;
                    j--;
                    
                }
            }
            while(i>=0){
                sum=i1->get_array()[i];
                s=std::to_string(sum%10)+s;
                i--;
            }
            if(sign1<1){
                s="-"+s;
            }
            result=new UnlimitedInt(s);
        }
        else if(s1==s2){
            bool b=true;
            for(int i=0;i<s1;i++){
                if(i1->get_array()[i]>i2->get_array()[i]){
                    int i=s1-1;
                    int j=s2-1;
                    int sum;
                    while(i>=0 && j>=0){
                        if(i1->get_array()[i]>=i2->get_array()[j]){
                            sum=i1->get_array()[i]-i2->get_array()[j];
                            s=std::to_string(sum%10)+s;
                            i--;
                            j--;
                        }
                        else{
                            int k=i-1;
                            while(i1->get_array()[k]==0){
                                k=k-1;
                            }
                            while(k!=i){
                                i1->get_array()[k]=i1->get_array()[k]-1;
                                k++;
                                i1->get_array()[k]=i1->get_array()[k]+10;
                            }
                            sum=i1->get_array()[i]-i2->get_array()[j];
                            s=std::to_string(sum%10)+s;
                            i--;
                            j--;
                        }
                    }
                    while(i>=0){
                        sum=i1->get_array()[i];
                        s=std::to_string(sum%10)+s;
                        i--;
                    }
                    if(sign1<0){
                        s="-"+s;
                    }
                    result=new UnlimitedInt(s);
                    b=false;
                    break;
                }
                else if(i1->get_array()[i]<i2->get_array()[i]){
                    int i=s1-1;
                    int j=s2-1;
                    int sum;
                    while(i>=0 && j>=0){
                        if(i1->get_array()[i]<=i2->get_array()[j]){
                            sum=-i1->get_array()[i]+i2->get_array()[j];
                            s=std::to_string(sum%10)+s;
                            i--;
                            j--;
                        }
                        else{
                            int k=j-1;
                            while(i2->get_array()[k]==0){
                                k=k-1;
                            }
                            while(k!=j){
                                i2->get_array()[k]=i2->get_array()[k]-1;
                                k++;
                                i2->get_array()[k]=i2->get_array()[k]+10;
                            }
                            sum=-i1->get_array()[i]+i2->get_array()[j];
                            s=std::to_string(sum%10)+s;
                            i--;
                            j--;
                        }
                    }
                    while(j>=0){
                        sum=i2->get_array()[j];
                        s=std::to_string(sum%10)+s;
                        j--;
                    }
                    if(sign2<0){
                        s="-"+s;
                    }
                    result=new UnlimitedInt(s);
                    b=false;
                    break;
                }
            }
            if(b){
                return new UnlimitedInt("0");
            }
        }
        else{
            return add(i2,i1);
        }
    }
    return result;
}


UnlimitedInt* UnlimitedInt::sub(UnlimitedInt* i1, UnlimitedInt* i2){
    UnlimitedInt* result;
    string s=i2->to_string();
    if(s[0]=='-'){
        s=s.substr(1,s.length());
    }
    else{
        s="-"+s;
    }
    result=new UnlimitedInt(s);
    return add(i1,result);
}

UnlimitedInt* UnlimitedInt::mul(UnlimitedInt* i1, UnlimitedInt* i2){
    UnlimitedInt* result=new UnlimitedInt(0);
    int sign1 = i1->get_sign();
    int sign2 = i2->get_sign();
    
    int sig = sign1 * sign2;
    
    int shift=0;
    
    for(int i=i2->get_size()-1;i>=0;i--){
        UnlimitedInt* r;
        string s="";
        int c=0;
        for(int j=i1->get_size()-1;j>=0;j--){
            int a=c+i1->get_array()[j]*i2->get_array()[i];
            c=a/10;
            s=std::to_string(a%10)+s;
        }
        if(c!=0){
            s=std::to_string(c)+s;
        }
        for(int k=0;k<shift;k++){
            s=s+"0";
        }
        shift++;
        r=new UnlimitedInt(s);
        
        result=add(result,r);
    }
    string s=result->to_string();
    if(sig<0){
        s="-"+s;
    }
    result=new UnlimitedInt(s);

    return result;
}

UnlimitedInt* UnlimitedInt::div(UnlimitedInt* i1, UnlimitedInt* i2){
    UnlimitedInt* result;
    int sign1 = i1->get_sign();
    int sign2 = i2->get_sign();

    int sig = sign1 * sign2;
    
    int quotient=0;

    if(i1->get_array()[0]==0){
        result=new UnlimitedInt(0);
        //result->sign=1;
        return result;
    }
    UnlimitedInt* divisor;
    UnlimitedInt* dividend;



    if(i1->to_string()[0]!='-'){
        dividend=new UnlimitedInt(i1->to_string());
    }
    else{
        string s1=i1->to_string().substr(1,i1->to_string().size());
        dividend=new UnlimitedInt(s1);
    }

    if(i2->to_string()[0]!='-'){
        divisor=new UnlimitedInt(i2->to_string());
    }
    else{
        string s2=i2->to_string().substr(1,i2->to_string().size());
        divisor=new UnlimitedInt(s2);
    }

    if(i2->get_array()[0]==0){
        result=new UnlimitedInt(0);
        return result;
    }
    
    while(dividend->get_sign()>=0){
        dividend=sub(dividend,divisor);
        quotient++;
    }
    quotient--;
    if(sig<0){
        if(add(dividend,divisor)->to_string()!="0"){
            quotient++;
        }
        quotient=-quotient;
    }
    result=new UnlimitedInt(quotient);
    return result;
}

UnlimitedInt* UnlimitedInt::mod(UnlimitedInt* i1, UnlimitedInt* i2){
    int sign1 = i1->get_sign();
    int sign2 = i2->get_sign();
    
    int sig = sign1 * sign2;
    
    int quotient=0;

    if(i1->get_array()[0]==0){
        return new UnlimitedInt(0);
    }
    
    UnlimitedInt* divisor;
    UnlimitedInt* dividend;
    
    if(i1->to_string()[0]!='-'){
        dividend=new UnlimitedInt(i1->to_string());
    }
    else{
        string s1=i1->to_string().substr(1,i1->to_string().size());
        dividend=new UnlimitedInt(s1);
    }

    if(i2->to_string()[0]!='-'){
        divisor=new UnlimitedInt(i2->to_string());
    }
    else{
        string s2=i2->to_string().substr(1,i2->to_string().size());
        divisor=new UnlimitedInt(s2);
    }



    if(i2->get_array()[0]==0){
        return new UnlimitedInt(0);
    }
    while(dividend->get_sign()>=0){
        dividend=sub(dividend,divisor);
        quotient++;
    }
    quotient--;
    dividend=add(dividend,divisor);
    if(sig<0 && dividend->to_string()!="0"){
        dividend=sub(divisor,dividend);
    }
    return dividend;
}

string UnlimitedInt::to_string() {
    if (unlimited_int[0] == 0) {
        return "0";
    }
    string result="";

    if (sign == -1) {
        result += "-";
    }
    for (int i = 0; i<size; ++i) {
        int r=unlimited_int[i];
        result=result+std::to_string(unlimited_int[i]);
    }
    return result;
}