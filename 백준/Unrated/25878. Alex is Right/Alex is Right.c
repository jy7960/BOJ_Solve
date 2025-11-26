#include <stdio.h>
#include <math.h>

#define R 6371.0
#define PI 3.14159265358979323846

typedef struct {
    double x, y, z;
} Vec3;

double d2r(double deg){
    return deg * PI / 180.0;
}

Vec3 latlon_to_xyz(double lat_deg, double lon_deg){
    double lat = d2r(lat_deg);
    double lon = d2r(lon_deg);
    Vec3 v;
    v.x = R * cos(lat) * cos(lon);
    v.y = R * cos(lat) * sin(lon);
    v.z = R * sin(lat);
    return v;
}

double dot(Vec3 a, Vec3 b){
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 cross(Vec3 a, Vec3 b){
    Vec3 c;
    c.x = a.y * b.z - a.z * b.y;
    c.y = a.z * b.x - a.x * b.z;
    c.z = a.x * b.y - a.y * b.x;
    return c;
}

double norm(Vec3 v){
    return sqrt(dot(v, v));
}

Vec3 normalize(Vec3 v){
    double n = norm(v);
    Vec3 res = {v.x / n, v.y / n, v.z / n};
    return res;
}

Vec3 vec_sub(Vec3 a, Vec3 b){
    Vec3 res = {a.x - b.x, a.y - b.y, a.z - b.z};
    return res;
}

Vec3 vec_scale(Vec3 v, double s){
    Vec3 res = {v.x * s, v.y * s, v.z * s};
    return res;
}

double dist(Vec3 a, Vec3 b){
    return sqrt((a.x - b.x)*(a.x - b.x)
              + (a.y - b.y)*(a.y - b.y)
              + (a.z - b.z)*(a.z - b.z));
}

int is_between(Vec3 A, Vec3 B, Vec3 Q){
    double AB = acos(dot(A,B)/(R*R));
    double AQ = acos(dot(A,Q)/(R*R));
    double QB = acos(dot(Q,B)/(R*R));
    double EPS = 1e-12;
    return fabs((AQ + QB) - AB) < EPS;
}

int main(){
    int T;
    scanf("%d", &T);
    Vec3 P = {0.0, 0.0, R};

    for(int t=0; t<T; t++){
        double lat1, lon1, lat2, lon2;
        scanf("%lf %lf", &lat1, &lon1);
        scanf("%lf %lf", &lat2, &lon2);

        Vec3 A = latlon_to_xyz(lat1, lon1);
        Vec3 B = latlon_to_xyz(lat2, lon2);

        Vec3 n = cross(A, B);
        double n_norm = norm(n);

        double dot_nP = dot(n, P);
        double d_plane = fabs(dot_nP) / n_norm;

        Vec3 n_scaled = vec_scale(n, dot_nP / (n_norm * n_norm));
        Vec3 proj = vec_sub(P, n_scaled);

        Vec3 Q = normalize(proj);
        Q = vec_scale(Q, R);

        double min_dist;

        if(is_between(A, B, Q)){
            min_dist = dist(Q, P);
        }
        else{
            double distA = dist(A, P);
            double distB = dist(B, P);
            min_dist = (distA < distB) ? distA : distB;
        }

        double dist_start = dist(A, P);
        double dist_end = dist(B, P);

        if(min_dist < dist_start && min_dist < dist_end)
            printf("Alex\n");
        else
            printf("Timothy\n");

        printf("%.6f\n\n", min_dist);
    }

    return 0;
}