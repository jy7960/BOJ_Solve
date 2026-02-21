#include <iostream>
#include <cmath>
#include <vector>
#define ld long double
using namespace std;

struct Point{
    ld x, y;
};

ld xa, ya, xb, yb, xc, yc;

ld ccw(Point a, Point b, Point c){
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

ld dist(Point a, Point b){
    ld x = a.x - b.x;
    ld y = a.y - b.y;
    return sqrtl(x * x + y * y);
}

ld getRound(ld a, ld b){
    return 2 * (a + b);
}

int main(){
    cout.precision(14);
    cout << fixed;
    
    Point a, b, c;
    cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
    if(ccw(a, b, c) == 0){
        cout << -1;
    }
    else{
        ld ab = dist(a, b);
        ld bc = dist(b, c);
        ld ac = dist(a, c);
        
        vector<ld> v;
        v.push_back(getRound(ab, ac));
        v.push_back(getRound(ab, bc));
        v.push_back(getRound(ac, bc));
        
        ld maxValue = 0;
        ld minValue = 40000;
        for(auto i : v){
            if(i > maxValue) maxValue = i;
            if(i < minValue) minValue = i;
            //cout << i << '\n';
        }

        cout << maxValue - minValue;
    }
    return 0;
}