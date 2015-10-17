//
//  main.c
//  bigint
//
//  Created by Chris Johnson on 9/26/15.
//  Copyright (c) 2015 Chris Johnson. All rights reserved.
//
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define _maxval(a,b) ((a)>(b)?(a):(b))

int _ctoi(char c ) {
    return c - '0';
}
char * _to_ascii( char * m, unsigned long len) {
    unsigned long t=0,z;
    for( z=0;m[z]==0;++z) {}
    if( z > 0 ) {
        memmove( m, m+z, len-z);
    }
    for( ;t<len-z;++t) {
        m[t]+='0';
    }
    m[t] = 0;
    return m;
}

char * _mul_str(char * a, char * b, unsigned long p, unsigned long q) {
    unsigned long len = p+q;
    char * m = malloc(len);
    int carry=0;
    unsigned long ai,bi;
    memset(m,0,len);
    for( bi = q-1; bi != -1; --bi ) {
        for( ai = p-1; ai != -1; --ai ) {
            m[ai + bi+1] += carry + _ctoi(a[ai]) * _ctoi(b[bi]);
            carry = m[ai + bi+1] / 10;
            m[ai + bi+1] %= 10;
        }
        m[bi] += carry;
        carry=0;
    }
    return _to_ascii(m, len);
}
char * _add_str(char * a, char * b, unsigned long p, unsigned long q) {
    unsigned long len = _maxval(p,q)+1;
    char * m = malloc(len);
    int carry=0;
    unsigned long ai,bi,t;
    memset(m,0,len);
    bi = q-1;
    ai = p-1;

    for( t=len-1;t!=0;--t) {
        if( ai != -1 && bi != -1 ) {
            m[t] = _ctoi(a[ai--]) + _ctoi(b[bi--]) + carry;
        } else if( ai != -1 ) {
            m[t] = _ctoi(a[ai--]) + carry;
        } else if( bi != -1 ) {
            m[t] = _ctoi(b[bi--]) + carry;
        } else {
            break;
        }
        if( m[t] >= 10 ) {
            carry = m[t]/10;
            m[t] -= 10;
        } else {
            carry = 0;
        }
    }
    if( carry > 0 ) {
        m[0] = carry;
    }
    return _to_ascii(m, len);
}

char * multiply( char * a, char * b ) {
    unsigned long a_len,b_len;
    a_len = strlen(a);
    b_len = strlen(b);
    
    return _mul_str( b, a, b_len, a_len);
}
char * add( char * a, char * b ) {
    unsigned long a_len,b_len;
    a_len = strlen(a);
    b_len = strlen(b);
    
    return _add_str( a, b, a_len, b_len);
}

int main(int argc, const char * argv[]) {
    int i=2;
    char n[1000];
    char *r;
    char f[1000] = "1";
    for(;i<100;++i) {
        sprintf( n, "%d", i );
        r  = multiply( n, f );
        memcpy(f, r, sizeof(f));
        free(r);
    }
    printf("%s\n", f );
    printf("%s\n", multiply("2", "123"));
    printf("%s\n", add("7", "8"));
    return 0;
}
