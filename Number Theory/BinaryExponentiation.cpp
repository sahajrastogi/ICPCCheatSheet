//switch * to + for safe ll multiplication
int power(int b, int e, int m) {
    int res = 1; 
    while (e > 0) {
        if (e & 1){
            res = res * b;res%=m;
        } b = b * b;b%= m;e >>= 1;
    } return res;
}
int inv(int b, int m){ return power(b,m-2,m);}