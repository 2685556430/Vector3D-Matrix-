#pragma once
#include <cmath>
#include <iostream>
using namespace std;
namespace ddwl {
	const double PI = 3.14159265358979323846;
	//ת�Ƕ�
	double Deg(double rad) { return rad * 180.0 / PI; }
	//ת����
	double Rad(double deg) { return deg / 180.0 * PI; }
	/*������нǶ�������*/
	double COS(double angles) { return cos(Rad(angles)); }
	double SIN(double angles) { return sin(Rad(angles)); }
	double ACOS(double vals) { return Deg(acos(vals)); }
	double ASIN(double vals) { return Deg(asin(vals)); }
	void Esp(double &val) { if (fabs(val) < 1e-8) val = 0; };
	/*3D����ͷ*/
	class Vector3D {
	public:
		Vector3D(double px = 1, double py = 0, double pz = 0) :x(px), y(py), z(pz) {};
		~Vector3D() {};
		double x, y, z;
		Vector3D operator = (const Vector3D &b) {
			this->x = b.x, this->y = b.y, this->z = b.z;
			return *this;
		}
		Vector3D operator + (const Vector3D &b)const {			//�ӷ�
			return Vector3D(this->x + b.x, this->y + b.y, this->z + b.z);
		}
		Vector3D operator - (const Vector3D &b)const {			//����
			return Vector3D(this->x - b.x, this->y - b.y, this->z - b.z);
		}
		Vector3D operator += (const Vector3D &b) {				//�ӷ�
			this->x += b.x, this->y += b.y, this->z += b.z;
			return Vector3D(this->x + b.x, this->y + b.y, this->z + b.z);
		}
		Vector3D operator -= (const Vector3D &b) {				//����
			this->x -= b.x, this->y -= b.y, this->z -= b.z;
			return Vector3D(this->x - b.x, this->y - b.y, this->z - b.z);
		}
		Vector3D operator () (double px, double py, double pz) {
			this->x = px, this->y = py, this->z = pz;
			return *this;
		}

		double operator * (const Vector3D &b)const {			//�����ڻ� ����
			return (this->x * b.x + this->y * b.y + this->z*b.z);
		}
		Vector3D operator * (const double &k)const {			//��������
			return Vector3D(this->x * k, this->y * k, this->z * k);
		}
		Vector3D operator *= (const double &k) {				//��������
			this->x *= k, this->y *= k, this->z *= k;
			return *this;
		}

	public:																//��Ա����

		friend Vector3D cross(const Vector3D &a, const Vector3D &b);	//�����Ϊ��Ԫ�������

		double norm()const {											//������ģ
			return sqrt(this->x*this->x + this->y*this->y + this->z*this->z);
		}
		double norm2()const {
			return (this->x*this->x + this->y*this->y + this->z*this->z);
		}
		void Normalizing() {
			//��λ��
			double k = (*this).norm();
			if (k == 0) return;
			this->x /= k, this->y /= k, this->z /= k;
		}
		void RotateByVector(double angles, Vector3D stdv = Vector3D(0, 0, 1)) {//�ռ�����ĳһ������תһ���Ƕ�
			stdv.Normalizing();//�Ƚ���������λ��
			{
				//Vector3D t = *this;
				//x = (stdv.x * stdv.x * (1 - COS(angles)) + COS(angles)) * t.x +
				//	(stdv.y * stdv.x * (1 - COS(angles)) - stdv.z * SIN(angles)) * t.y +
				//	(stdv.z * stdv.x * (1 - COS(angles)) + stdv.y * SIN(angles)) * t.z;

				//y = (stdv.x * stdv.y * (1 - COS(angles)) + stdv.z * SIN(angles)) * t.x +
				//	(stdv.y * stdv.y * (1 - COS(angles)) + COS(angles)) * t.y +
				//	(stdv.z * stdv.y * (1 - COS(angles)) - stdv.x * SIN(angles)) * t.z;

				//z = (stdv.x * stdv.z * (1 - COS(angles)) - stdv.y * SIN(angles)) * t.x +
				//	(stdv.y * stdv.z * (1 - COS(angles)) + stdv.x * SIN(angles)) * t.y +
				//	(stdv.z * stdv.z * (1 - COS(angles)) + COS(angles)) * t.z;
				//Esp(x), Esp(y), Esp(z);//�����������
			}
			/*�޵����ʽ������ת����*/
			*this = (*this) * COS(angles) +
				(stdv * (stdv * (*this)) * (1 - COS(angles))) +
				(cross(*this, stdv) * SIN(angles));

		}
	};

	double Angle(const Vector3D &a, const Vector3D &b) {					//���������н�
		if (a.norm() == 0) return 0;
		return ACOS(a*b / (a.norm()*b.norm()));
	}
	Vector3D cross(const Vector3D &a, const Vector3D &b) {//������� ʸ��
		return Vector3D(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
	}
	istream& operator >> (istream &in, Vector3D &a) {
		in >> a.x >> a.y >> a.z;
		return in;
	}
	ostream& operator<<(ostream &out, const Vector3D &a) {
		out << "(" << a.x << ", " << a.y << ", " << a.z << ")";
		return out;
	}
	bool Parallel(const Vector3D &a, const Vector3D &b) {
		Vector3D t = cross(a, b);
		if (t.x == 0 && t.y == 0 && t.z == 0) return true;
		return false;
	}
}