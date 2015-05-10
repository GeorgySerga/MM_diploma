#include <fstream>
#include "cmath"

using namespace std;

const int n = 3; //степень простого числа
const int q = 8; // q = 2^n - количество элементов в Омега
const int m = (q-1) * q; // m = (q^2 - q)
const int K = 7; // Ограничение k сверху

int g[] = {0, 1, 2, 3, 4, 5, 6, 7};
int Nk_Gi[K];
int nu, _k;
ofstream myfile("z2z4_exceptions");

void swap (int &a, int &b) {
  int temp = a;
  a = b;
  b = temp;
}

int sum_mod_2_4 (int x, int y) {
  int x_set[2], y_set[2];
  int mod_elem;
  for (int j = 1; j > -1; j--) {
    x_set[j] = x % 4;
    x /= 4;
    y_set[j] = y % 4;
    y /= 4;
  }
  mod_elem = ((x_set[0] + y_set[0]) % 2) * 4;
  mod_elem += (x_set[1] + y_set[1]) % 4;
  return mod_elem;
}

void excepts(int H[]) {
  double Q[q][q];
  double Q_2[q][q];
  double Q_3[q][q];
  double Q_p3[q][q];
  double Q_p4[q][q];
  double Q_p5[q][q];
  double Q_sq[q][q];
  int mu;
  for (int i = 1; i < q; i++) {
    for (int j = 1; j < q; j++) {
      mu = 0;
      for (int x = 0; x < q; x++) {
        if (H[sum_mod_2_4(x,i)] == sum_mod_2_4(H[x],j)) mu++;
      }
      Q[i][j] = (1.0/q) * mu;
      Q_2[i][j] =  Q[i][j];
      Q_3[i][j] = 0;
      Q_p3[i][j] = 0;
      Q_p4[i][j] = 0;
      Q_p5[i][j] = 0;
      Q_sq[i][j] = 0;
    }
  }
  int s = 0;
  int matrixTimes = 20;
  while (s < matrixTimes) {
    for (int i = 1; i < q; i++) {
      for (int j = 1; j < q; j++) {
        for (int l = 1; l < q; l++) {
          Q_3[i][j] += Q_2[i][l] * Q[l][j];
        }
      }
    }
    if (s != (matrixTimes - 1)) {
      for (int i = 1; i < q; i++) {
        for (int j = 1; j < q; j++) {
          Q_2[i][j] = Q_3[i][j];
          Q_3[i][j] = 0;
        }
      }
    }
    if (s == (matrixTimes - 3)) { // период 2
      for (int i = 1; i < q; i++) {
        for (int j = 1; j < q; j++) {
          Q_p3[i][j] = Q_2[i][j];
        }
      }
    }
    if (s == (matrixTimes - 4)) { // период 3
      for (int i = 1; i < q; i++) {
        for (int j = 1; j < q; j++) {
          Q_p4[i][j] = Q_2[i][j];
        }
      }
    }
    if (s == (matrixTimes - 5)) { // период 4
      for (int i = 1; i < q; i++) {
        for (int j = 1; j < q; j++) {
          Q_p5[i][j] = Q_2[i][j];
        }
      }
    }
    // возведение в квадрат
    if (s == (matrixTimes - 1)) {
      for (int i = 1; i < q; i++) {
        for (int j = 1; j < q; j++) {
          for (int l = 1; l < q; l++) {
            Q_sq[i][j] += Q_3[i][l] * Q_3[l][j];
          }
        }
      }
    }
    s++;
  }

  // проверяем матрицу на наличие нулей
  int zero = 0;
  for (int i = 1; i < q; i++) {
    for (int j = 1; j < q; j++) {
      if (Q_3[i][j] == 0) {
        zero = 1;
        break;
      }
    }
    if (zero == 1) break;
  }

  //Если предыдущая матрица отличается ставим 1, если нет, то 0.
  if (zero == 1) {
    mu = -1;
    for (int i = 1; i < q; i++) {
      for (int j = 1; j < q; j++) {
        if (abs(Q_3[i][j] - Q_2[i][j]) > 0.01) {
            mu = 1;
            break;
        }
      }
      if (mu == 1) break;
    }
    if (mu == -1) mu = 0;
  // А к-й прообраз нет
    if (mu == 1) {
      for (int i = 1; i < q; i++) {
        for (int j = 1; j < q; j++) {
          if (abs(Q_3[i][j] - Q_p3[i][j]) > 0.01) {
            mu = -1;
            break;
          }
        }
        if (mu == -1) break;
      }
      if (mu == -1) {
        mu = 1;
        for (int i = 1; i < q; i++) {
          for (int j = 1; j < q; j++) {
            if (abs(Q_3[i][j] - Q_p4[i][j]) > 0.01) {
              mu = -1;
              break;
            }
          }
          if (mu == -1) break;
        }
      }
      if (mu == -1) {
        mu = 1;
        for (int i = 1; i < q; i++) {
          for (int j = 1; j < q; j++) {
            if (abs(Q_3[i][j] - Q_p5[i][j]) > 0.01) {
              mu = -1;
              break;
            }
          }
          if (mu == -1) break;
        }
      }
    }
    if (mu == 1) {
      myfile << "periodical: ";
      for (int j = 0; j < 8; j++) {
        myfile << H[j] << " ";
      }
    }
    if (mu == 0) {
      for (int i = 1; i < q; i++) {
        for (int j = 1; j < q; j++) {
          if (abs(Q_3[i][j] - Q_sq[i][j]) > 0.01) {
            mu = -1;
            break;
          }
        }
        if (mu == -1) break;
      }
      if (mu == 0) {
        myfile << "idemp: ";
        for (int j = 0; j < 8; j++) {
          myfile << H[j] << " ";
        }
      } else {
        myfile << "symmetry: ";
        for (int j = 0; j < 8; j++) {
          myfile << H[j] << " ";
        }
      }
    }
  }
}


void perm_gen (int *H, int l) {
  //порождаем q! перестановок
  if (l == 1) {
    excepts(H);
    myfile << endl;
  }
  else {
    for (int i = 0; i < l; i++) {
      swap(H[i], H[l-1]);
      perm_gen(H, l-1);
      swap(H[i], H[l-1]);
    }
  }
}

void h () {
  int h[q];
  for (int i = 0; i < q; i++) {
    h[i] = i;
  }
  perm_gen(h, q);
}

int main () {
  h();
  myfile.close();
  return 0;
}
