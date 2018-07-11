#include <bits/stdc++.h>
using F = double;
using Int = int64_t;

struct Point {
   F x, y, z;
   Point()
      : x(0), y(0), z(0) {}
   Point(F x_, F y_, F z_)
      : x(x_), y(y_), z(z_) {}
};

F square_dist(Point a, Point b) {
   F dx = a.x - b.x;
   F dy = a.y - b.y;
   F dz = a.z - b.z;
   F d = dx * dx + dy * dy + dz * dz;
   return d;
}

F dist(Point a, Point b) {
   return sqrt(square_dist(a, b));
}

F norm(F dx, F dy, F dz) {
   return sqrt(dx*dx + dy*dy + dz*dz);
}

std::vector<Point> gen_chain(Int len, Int seed) {
   std::vector<Point> res;
   std::mt19937 mt(seed);
   std::uniform_real_distribution<> rd(-1.0,1.0);
   for(Int i = 0; i < len; ++i) {
      F x = rd(mt);
      F y = rd(mt);
      F z = rd(mt);
      res.push_back(Point(x, y, z));
   }
   return res;
}

std::vector<std::vector<F>> gen_dist_matrix(std::vector<Point> ps) {
   std::vector<std::vector<F>> res;
   Int n = ps.size();
   res.resize(n);
   for(Int i = 0; i < n; ++i) {
      for(Int k = 0; k < n; ++k) {
         F d = square_dist(ps[i], ps[k]);
         res[i].push_back(d);
      }
   }
   return res;
}

std::vector<Point> gen_instance(std::vector<std::vector<F>> mat) {
   Int n = mat.size();
   std::vector<Point> ps;
   for(Int i = 0; i < n; ++i) {
      ps.push_back(Point(0.0,0.0,0.0));
   }
   std::mt19937 mt(12345);
   std::uniform_real_distribution<> rd(-1.0, 1.0);
   for(Int i = 1; i < n; ++i) {
      // printf("%ld\n", i);
      F x = rd(mt);
      F y = rd(mt);
      F z = rd(mt);
      for(Int t = 0; t < 100000; ++t) {
         F dx = 0.0, dy = 0.0, dz = 0.0;
         for(Int k = 0; k < i; ++k) {
            F d = dist(Point(x,y,z), ps[k]);
            F d_norm = norm(x-ps[k].x, y-ps[k].y, z-ps[k].z);
            dx -= (x-ps[k].x) / d_norm * (d-sqrt(mat[i][k]));
            dy -= (y-ps[k].y) / d_norm * (d-sqrt(mat[i][k]));
            dz -= (z-ps[k].z) / d_norm * (d-sqrt(mat[i][k]));
         }
         F norm_2 = norm(dx, dy, dz);
         if( norm_2 <= 0.00000001 ) {
            break;
         }
         dx /= norm_2;
         dy /= norm_2;
         dz /= norm_2;
         x += dx * 0.0001;
         y += dy * 0.0001;
         z += dz * 0.0001;
      }
      ps[i] = Point(x, y, z);
   }
   return ps;
}

int main() {
   auto n = 10;
   auto seed = 31415;
   auto ps = gen_chain(n, seed);
   auto mat = gen_dist_matrix(ps);
   puts("target");
   for(Int i = 0; i < n; ++i) {
      for(Int k = 0; k < n; ++k) {
         printf("%.3lf ", mat[i][k]);
      }
      printf("\n");
   }
   auto qs = gen_instance(mat);
   auto mat2 = gen_dist_matrix(qs);
   puts("instance");
   for(Int i = 0; i < n; ++i) {
      for(Int k = 0; k < n; ++k) {
         printf("%.3lf ", mat2[i][k]);
      }
      printf("\n");
   }
   for(Int i = 0; i < n; ++i) {
      printf("qs[%ld] = (%.3lf, %.3lf, %.3lf)\n", i, qs[i].x, qs[i].y, qs[i].z);
   }
}
