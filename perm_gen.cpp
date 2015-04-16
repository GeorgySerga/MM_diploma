#include <fstream>
#include "iomanip"

using namespace std;

ofstream myfile("permutations");

void swap (int &a, int &b) {
  int temp = a;
  a = b;
  b = temp;
}

// int z = 0;
void perm_gen (int *H, int l) {
  //recursive permutations generation
  if (l == 1) {
    // if (z == ) { //uncomment to print perm with specific number
      for (int j = 0; j < 8; j++) {
        myfile << H[j] << " ";
      }
      myfile << endl;
    // }
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
