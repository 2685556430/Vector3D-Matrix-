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
	for (int i = 0; i < 25; i++) {//�������һ�� 10*10 �ľ���
		arr[i] = -rand() % 5;
	}
	a = arr;
	b = arr1;
	cout << "a����\n";
	a.Show();
	cout << "a��������ʽ��ֵ: " << a.det() << '\n';
	cout << "a�������: \n";
	a.Inv();
	cout << "����A*A-1 = E��\n";
	(a.Inv()*a).Show();
	cout << '\n';
	cout << "b����Ľ�(b���ɷ����鹹�ɵľ���)��\n";
	Mat x;
	b.Solve(x);
	x.Show();
	cout << '\n';
	cout << "b��ת�ã�\n";
	b.T().Show();
	cout << '\n';
	Mat p(2, 2);
	cout << "������һ��2*2�ľ���\n";
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
	t.Normalizing(3, 3);//��tתΪn*n�ĵ�λ����
	t = a.matPow(n);	//������n����
	cout << a << '\n';
	cout << t << '\n';
	system("pause");
	return 0;
}