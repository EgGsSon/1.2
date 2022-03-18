#include <stdio.h>
//#include <stlib.h>
#include <math.h>

int power(int n, int x) {
    int res = 1;
    for(int i = 0; i < x; i++)
        res = res * n;
    return res;
}

typedef struct Uint1024_t{
    unsigned int ls[35];
    int index;
} uint1024_t;

void clean_int(uint1024_t *x) {
    for(int g = 0; g < 35; g++) {
        x->ls[g] = 0;
    }
}

uint1024_t from_uint(unsigned int x) {
    uint1024_t a;
    a.index = 34;
    
    clean_int(&a);
    
    if(x / power(10,9) != 0) {
        a.ls[33] = x / power(10,9);
        a.index = 33;
    }
    a.ls[34] = x % power(10,9);
    return a;
}

void scanf_value(uint1024_t* x) {
    
    char text[310];
    printf("Enter your number:\n");
    scanf("%s", text);
    int i = 0;
    int z = 34;
    
    while(text[i] != '\0') {
        i++;
    }
    
    clean_int(x);
    
    
    i--;
    for(int k = i; k >= 0; k--) {
        int p = i - k;
        x->ls[z] += (text[k] - '0') * power(10,p);
        
        if( (i - k) % 8 == 0 && (i - k) != 0) {
            z--;
            i = k - 1;
        }
    }
    
    if(x->ls[z] != 0)
        x->index = z;
    else
        x->index = z + 1;
}


void printf_value(uint1024_t a) {
    while(a.ls[a.index] == 0 && a.index != 34)
        a.index += 1;
    for(int i = a.index; i < 35; i++) {
        int k = 8;
        while( (a.ls[i] / power(10,k) == 0) && k > 0 && i != a.index) {
            printf("0");
            k--;
        }
        printf("%d", a.ls[i]);
    }
    printf("\n");
}

uint1024_t add_op(uint1024_t x, uint1024_t y) {
    uint1024_t res;
    int max_index;
    int remainder = 0;
    
    clean_int(&res);
    
    if(x.index < y.index)
        max_index = x.index;
    else
        max_index = y.index;
    for(int i = 34; i >= max_index; i--) {
        int adding = x.ls[i] + y.ls[i] + remainder;
        remainder = 0;
        if(adding / power(10,9) != 0)
            remainder = adding / power(10,9);
        res.ls[i] = adding % power(10,9);
    }
    
    if(max_index != 0) {
        res.index = max_index - 1;
        res.ls[res.index] = remainder;
    }
    else
        res.index = max_index;
    return res;
}

uint1024_t subtr_op(uint1024_t x, uint1024_t y) {
    uint1024_t res;
    int max_index = x.index;
    int remainder = 0;
    
    clean_int(&res);
    
    
    for(int i = 34; i >= max_index; i--) {
        int subtraction = x.ls[i] - y.ls[i] - remainder;
        remainder = 0;
        if(subtraction < 0) {
            subtraction += power(10,9) ;
            remainder = 1;
        }
        res.ls[i] = subtraction;
    }
    
    if(max_index != 0) {
        res.index = max_index - 1;
        res.ls[res.index] = remainder;
    }
    else
        res.index = max_index;
    return res;
}

uint1024_t mult_op(uint1024_t x, uint1024_t y) {
    uint1024_t res;
    clean_int(&res);
    long long value;
    int index;
    
    for(int i = 34; i >= x.index; i--) {
        for(int k = 34; k >= y.index; k--) {
            
            index = i - (34 - k);
            
            if(index >= 0) {
                value = (long long)x.ls[i] * (long long)y.ls[k] + (long long)res.ls[index];
                res.ls[index] = value % (long long)power(10, 9);
                if(index > 0)
                    res.ls[index - 1] += value / (long long)power(10, 9);
                
            }
        }
    }
    
    int z = 0;
    while(res.ls[z] == 0 && z <= 34) {
        z++;
    }
    
    res.index = z;
    
    return res;
}

int main(int argc, const char * argv[]) {
    uint1024_t a;
    uint1024_t d;
    uint1024_t b;
    d = from_uint(1);
    scanf_value(&a);
    scanf_value(&b);
    uint1024_t r = mult_op(a, b);
    printf("RESULT %d\n", r.index);
    printf_value(r);
    
    return 0;
}
