#include <iostream>
#include <fstream>

using namespace std;

const int n = 3; //степень простого числа
const int q = 8; // q = 2^n - количество элементов в Омега
const int m = (q-1) * q; // m = (q^2 - q)
const int K = 4; // Ограничение k сверху

int g[] = {0, 1, 2, 3, 4, 5, 6, 7};
int Nk_Gi[K]; // количество перестановок h, для которых матрица P становится положительной при минимальном k
int nu, _k;
ofstream myfile("used");

void swap (int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}

void Nu_positivity (int a, int b, int c, int d, int *H, int k) {
	if ((_k == k) && (nu > 0)) return; // нет смысла искать "минимальное k" среди >= уже найденного
	if (k < K) {
		k++;
		if (k > 2) {
			for (int r = 0; r < q; r++) {
				if ((g[(H[a] + r) % q] == c) && (g[(H[b] + r) % q] == d)) {
					if (_k == 0) _k = k;
					if (_k > k) _k = k;
					nu++;
					break;
				}
			}
		}
		for (int r = 0; r < q; r++) Nu_positivity(g[(H[a] + r) % q], g[(H[b] + r) % q], c, d, H, k);
	}
}

void result () {
	for (int i = 0; i < K; i++) cout << Nk_Gi[i] << " ";
}

void P_positivity (int H[]) {
	int bi_iind_switch = 0;
	int k_max = 0;
	for (int i = 0; i < m; i++) {
		int bi_jind_switch = 0;
		// если индексы совпадают, добавляем единицу, так как в матрице нет строк с номерами (i,i)
		if (((i + bi_iind_switch)/q) == ((i + bi_iind_switch)%q)) bi_iind_switch++;
		for (int j = 0; j < m; j++) {
			if (((j + bi_jind_switch)/q) == ((j + bi_jind_switch)%q)) bi_jind_switch++;
			int a = ((i + bi_iind_switch) / q);
			int b = ((i + bi_iind_switch) % q);
			int c = ((j + bi_jind_switch) / q);
			int d = ((j + bi_jind_switch) % q);
			int k = 0;
			nu = 0;
			_k = 0;
			Nu_positivity(a, b, c, d, H, k); // ищется мнимальное k, при котором элемент матрицы будет > 0
			if (nu == 0) {
				myfile << endl;
				return; //прекращение расчетов матрицы, так как она уже неположительная
			}
			if (k_max < _k) k_max = _k; //среди минимальных выбирается макимальное, при котором P > 0
		}
	}
	Nk_Gi[k_max-3]++;
	myfile << "Nk_Gi[" << k_max-3 << "] = " << Nk_Gi[k_max-3] << endl;
}

void perm_gen (int *H, int l) {
	//порождаем q! перестановок
	if (l == 1) {
		P_positivity(H);
	}
	else {
		for(int i = 0; i < l; i++) {
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
	for (int i = 0; i < K-2; i++) {
		Nk_Gi[i] = 0;
	}
	perm_gen(h, q);
}

int main () {
	h();
	result();
	myfile.close();
	return 0;
}
