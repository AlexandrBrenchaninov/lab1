#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

void printMatrix(vector<vector<double>> v) {//Вывод в консоль матрицы
	for (int i = 0; i < v.size(); i++) {
		for (int j = 0; j < v[i].size(); j++) {
			cout << v[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void printVector(vector<double> v) {//Вывод в консоль вектора 
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << endl;
	}
	cout << endl;
}

vector<double> gaussMethod(vector<vector<double>> v) {//Метод гаусса
	int n = v.size();

	for (int i = 0; i < n; i++) {
		int max = i;
		for (int j = i + 1; j < n; j++)
			if (abs(v[j][i]) > abs(v[max][i]))
				max = j;
		swap(v[max], v[i]);

		for (int j = i + 1; j < n; j++)
			for (int k = n; k >= i; k--)
				v[j][k] -= v[i][k] * v[j][i] / v[i][i];
	}

	vector<double> vSolve(n);

	for (int i = n - 1; i >= 0; i--) {
		vSolve[i] = v[i][n] / v[i][i];
		for (int j = i - 1; j >= 0; j--)
			v[j][n] -= v[j][i] * vSolve[i];
	}
	return vSolve;
}

vector<double> findVectorF(vector<vector<double>> vAB, vector<double> vX) {//Вектор невязки
	vector<double> vAX = { 0, 0, 0 };
	for (int i = 0; i < vAB.size(); i++) {
		double sum = 0;
		for (int j = 0; j < vAB[i].size() - 1; j++) {
			sum += vAB[i][j] * vX[j];
		}
		vAX[i] = sum;
	}
	vector<double> vF = { 0, 0, 0 };
	for (int i = 0; i < vAB.size(); i++) {
		vF[i] = vAX[i] - vAB[i][vAB[i].size() - 1];
	}
	return vF;
}

vector<vector<double>> makeVectorToSolve(vector<vector<double>> vAB, vector<double> vX) {//Вспомогательная система для 3-его пункта
	vector<double> vAX = { 0, 0, 0 };
	for (int i = 0; i < vAB.size(); i++) {
		double sum = 0;
		for (int j = 0; j < vAB[i].size() - 1; j++) {
			sum += vAB[i][j] * vX[j];
		}
		vAX[i] = sum;
	}
	vector<vector<double>> vAB2 = {
		{0,0,0,0},
		{0,0,0,0},
		{0, 0, 0, 0}
	};
	for (int i = 0; i < vAB.size(); i++) {
		for (int j = 0; j < vAB[i].size(); j++) {
			if (j == 3) {
				vAB2[i][j] = vAX[i];
				break;
			}
			vAB2[i][j] = vAB[i][j];
		}
	}
	return vAB2;
}

double findDelta(vector<double> vX1, vector<double> vX2) {
	double maxChisl = 0;
	for (int i = 0; i < vX2.size(); i++) {
		for (int j = 0; j < vX1.size(); j++) {
			if ((vX2[i] - vX1[j]) > maxChisl) {
				maxChisl = vX2[i] - vX1[j];
			}
		}
	}

	double maxZnam = 0;
	for (int i = 0; i < vX1.size(); i++) {
		if (vX1[i] > maxZnam) {
			maxZnam = vX1[i];
		}
	}

	return maxChisl / maxZnam;
}

int main() {
	vector<vector<double>> vAB = {
		{8.64, 1.71, 5.42, 10.21},
		{-6.39, 4.25, 1.84, 3.41},
		{4.21, 7.92, -3.41, 12.29}
	};

	printMatrix(vAB);

	vector<double> vX = gaussMethod(vAB);
	cout << "Vector x : " << endl;
	printVector(vX);

	vector<double> vF = findVectorF(vAB, vX);
	cout << "Vector f : " << endl;
	printVector(vF);

	vector<vector<double>>vAB2 = makeVectorToSolve(vAB, vX);
	printMatrix(vAB2);
	vector<double> vX2 = gaussMethod(vAB2);

	double delta = findDelta(vX, vX2);
	cout << "Delta = " << delta << endl;

}
