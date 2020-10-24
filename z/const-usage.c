
void test(const char * const p);

char *  str0 __attribute__((used)) = "aaaa";
const char * str1 __attribute__((used)) = "bbbb";
char * const str2 __attribute__((used)) = "cccc";
const char * const str3 __attribute__((used)) = "dddd";

void test(const char * const p)
{
    int a;
    int b;
    
    const int c;
    int const d;
    const int const e;
    
    /* p0: R/W, *p0: R/W */
    int *p0;
    
    /* p1: R/W, *p1: R */
    const int *p1;
    
    /* p2: R/W, *p2: R (the same as p1) */
    int const *p2;
    
    /* p3: R/W, *p3: R (the same as p1, #83-D: type qualifier specified more than once) */
    const int const *p3;        
    
    /* p4: R, *p4: R */
    const int *const p4 = &a;
    
    /* p5: R, *p4: R */
    const int const * const p5 = &a;

    p0 = &a;
    b = *p0;
    *p0 = 0;
    
    p1 = &a;
    b = *p1;
    //*p1 = 2;      // error

    p2 = &a;
    b = *p2;
    //*p2 = 0;      // error
    
    p3 = &a;
    b = *p3;
    //*p3 = 0;      // error
    
    //p4 = &a;
    b = *p4;
    //*p4 = 0;      // error
    
    (void)a;    
    (void)b;
    (void)c;
    (void)d;
    (void)e;
}
