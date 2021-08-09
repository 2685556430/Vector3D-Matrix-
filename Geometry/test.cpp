#include<iostream>
#include<vector>
#include<graphics.h>
#include<stdlib.h>
#include<time.h>
#include"Matrix.h"
#include"Vector3D.h"
using namespace std;

int main() {
	{
	srand((unsigned int)time(NULL));
	Mat a(5, 5), b = Mat(3, 4);
	double arr[25], arr1[12] = { 2,1,1,1,6,2,1,-1,-2,2,1,7 };
	for (int i = 0; i < 25; i++) {//随机生成一个 10*10 的矩阵
		arr[i] = -rand() % 5;
	}
	a = arr;
	b = arr1;
	cout << "a矩阵：\n";
	a.Show();
	cout << "a矩阵行列式的值: " << a.det() << '\n';
	cout << "a矩阵的逆: \n";
	a.Inv();
	cout << "检验A*A-1 = E：\n";
	(a.Inv()*a).Show();
	cout << '\n';
	cout << "b矩阵的解(b是由方程组构成的矩阵)：\n";
	Mat x;
	b.Solve(x);
	x.Show();
	cout << '\n';
	cout << "b的转置：\n";
	b.T().Show();
	cout << '\n';
	Mat p(2, 2);
	cout << "请输入一个2*2的矩阵：\n";
	cin >> p;
	cout << p;
}
	cout << "**********\n";
	Mat a(3, 3), t;
	double arr[9];
	for (int i = 0; i < 9; i++) {
		arr[i] = rand() % 5;
	}
	a = Mat(3, 3, arr);
	t = a;
	cout << a << '\n';
	int n = 30;
	t.Normalizing(3, 3);//将t转为n*n的单位矩阵
	t = a.matPow(n);	//求矩阵的n次幂
	cout << a << '\n';
	cout << t << '\n';
	system("pause");
	return 0;
}