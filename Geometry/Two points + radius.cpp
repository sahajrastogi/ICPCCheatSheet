#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;
struct point{
 double x,y;
 int id;
 point(){}
 point(double a,double b):x(a),y(b){}
 double dot(point p){
    return x*p.x + y*p.y;
 }
 point operator+(const point &p){
    return point(x + p.x,y+p.y);
 }
 point operator-(const point &p){
    return point(x - p.x,y-p.y);
 }
 point operator*(const int p){
    return point(x*p,y*p);
 }
};
vector<point> find_center(point a,point b,long double r){
    point d=(a-b)*0.5;
    if(d.dot(d)>r*r){
    return vector<point>();
    }
    point e=b+d;
    long double fac=sqrt(r*r-d.dot(d));
    vector<point>ans;
    point x=point(-d.y,d.x);
    long double l=sqrt(x.dot(x));
    x=x*(fac/l);
    ans.push_back(e+x);
    x= point(d.y,-d.x);
    x=x*(fac/l);
    ans.push_back(e+x);
    return ans;
}