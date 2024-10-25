struct cc{
    bool operator()(const int &a, const int &b) const{return b<a;}
};
set<int,cc> S;