const double EPS = 1e-9;

bool inCircle(const pair<pair<double,double>,double>& C,
              const pair<double,double>& p) {
    double dx = p.first - C.first.first;
    double dy = p.second - C.first.second;
    return (dx*dx + dy*dy) <= C.second * C.second + EPS;
}
 
pair<pair<double,double>,double> circleFrom1(const pair<double,double>& p) {
    return { p, 0.0 };
}
 
pair<pair<double,double>,double> circleFrom2(const pair<double,double>& a,
                                              const pair<double,double>& b) {
    double cx = (a.first + b.first) / 2.0;
    double cy = (a.second + b.second) / 2.0;
    double r = sqrt((a.first - b.first)*(a.first - b.first) +
                    (a.second - b.second)*(a.second - b.second)) / 2.0;
    return { {cx, cy}, r };
}
 
pair<pair<double,double>,double> circleFrom3(const pair<double,double>& A,
                                              const pair<double,double>& B,
                                              const pair<double,double>& C) {
    double D = 2 * ( A.first * (B.second - C.second) +
                     B.first * (C.second - A.second) +
                     C.first * (A.second - B.second) );
    if (fabs(D) < EPS) { // collinear – return the circle that covers them (using the farthest two)
         pair<pair<double,double>,double> c1 = circleFrom2(A, B);
         pair<pair<double,double>,double> c2 = circleFrom2(A, C);
         pair<pair<double,double>,double> c3 = circleFrom2(B, C);
         if(c1.second >= c2.second && c1.second >= c3.second)
             return c1;
         else if(c2.second >= c1.second && c2.second >= c3.second)
             return c2;
         else
             return c3;
    }
    double Ux = ((A.first*A.first + A.second*A.second) * (B.second - C.second) +
                 (B.first*B.first + B.second*B.second) * (C.second - A.second) +
                 (C.first*C.first + C.second*C.second) * (A.second - B.second)) / D;
    double Uy = ((A.first*A.first + A.second*A.second) * (C.first - B.first) +
                 (B.first*B.first + B.second*B.second) * (A.first - C.first) +
                 (C.first*C.first + C.second*C.second) * (B.first - A.first)) / D;
    double r = sqrt((A.first - Ux)*(A.first - Ux) + (A.second - Uy)*(A.second - Uy));
    return { {Ux, Uy}, r };
}
 
pair<pair<double,double>,double> circleFromBoundary(const vector<pair<double,double> >& R) {
    if (R.empty())
        return { {0, 0}, 0 };
    else if (R.size() == 1)
        return circleFrom1(R[0]);
    else if (R.size() == 2)
        return circleFrom2(R[0], R[1]);
    else
        return circleFrom3(R[0], R[1], R[2]);
}
 
pair<pair<double,double>,double> welzl(vector<pair<double,double> > &pts,
                                        vector<pair<double,double> > &bounds) {
    pair<pair<double,double>,double> D;
    D = circleFrom1(pts[0]);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    shuffle(all(pts),rng);
    for (size_t i = 0; i < pts.size(); i++) {
         if (!inCircle(D, pts[i])) {
              vector<pair<double,double> > R1 = bounds;
              if (R1.size() < 3)
                  R1.push_back(pts[i]);
              D = circleFromBoundary(R1);
              for (size_t j = 0; j < i; j++) {
                   if (!inCircle(D, pts[j])) {
                        vector<pair<double,double> > R2 = R1;
                        if (R2.size() < 3)
                            R2.push_back(pts[j]);
                        D = circleFromBoundary(R2);
                        for (size_t k = 0; k < j; k++) {
                             if (!inCircle(D, pts[k])) {
                                  vector<pair<double,double> > R3 = R2;
                                  if (R3.size() < 3)
                                      R3.push_back(pts[k]);
                                  D = circleFromBoundary(R3);
                             }
                        }
                   }
              }
         }
    }
    return D;
}
