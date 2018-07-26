//#include "stdafx.h"
#include <cmath>
#include <cstdlib>

#include "Matrix.h"
////////////////////////
/////�������///////////
////////////////////////

Matrix MatrixAdd(Matrix M1, Matrix M2)
{
	int m1 = M1.row;
	int n1 = M1.col;
	int m2 = M2.row;
	int n2 = M2.col;//��þ������������

	//if ((m1 != m2) || (n1 != n2))
	//{
	//	//ע��ѧϰC++����׳��쳣���Ժ��ϡ�
	//}
	Matrix Mc(m1, n1);
	vector< vector<double> > &c = Mc.A;
	vector< vector<double> > &a = M1.A;
	vector< vector<double> > &b = M2.A;//����һ��Ҫע�ⰴ��ַ���ݻ��ߴ����ã������ڵ��ú���ʱ�Ͳ��ܵó���ȷ�����
	
	for (int i = 0; i < m1; i++)
	{
		for (int j = 0; j < n1; j++)
		{
			c[i][j] = a[i][j] + b[i][j];
		}
	}
	return Mc;
}


////////////////////////
/////�������///////////
////////////////////////
Matrix MatrixSub(Matrix M1, Matrix M2)
{
	int m1 = M1.row;
	int n1 = M1.col;
	int m2 = M2.row;
	int n2 = M2.col;//��þ������������

	//if ((m1 != m2) || (n1 != n2))
	//{
	//	//ע��ѧϰC++����׳��쳣���Ժ��ϡ�
	//}
	Matrix Mc(m1, n1);
	vector< vector<double> > &c = Mc.A;
	vector< vector<double> > &a = M1.A;
	vector< vector<double> > &b = M2.A;//����һ��Ҫע�ⰴ��ַ���ݻ��ߴ����ã������ڵ��ú���ʱ�Ͳ��ܵó���ȷ�����

	for (int i = 0; i < m1; i++)
	{
		for (int j = 0; j < n1; j++)
		{
			c[i][j] = a[i][j] - b[i][j];
		}
	}
	return Mc;
}

////////////////////////
/////�������///////////
////////////////////////
Matrix MatrixMulti(Matrix M1, Matrix M2)
{
	int m1 = M1.row;
	int n1 = M1.col;
	int m2 = M2.row;
	int n2 = M2.col;//��þ������������

	//�ж�M1,M2�Ƿ�������
	Matrix Mc(m1, n2);
	vector< vector<double> > &c = Mc.A;
	vector< vector<double> > &a = M1.A;
	vector< vector<double> > &b = M2.A;//����һ��Ҫע�ⰴ��ַ���ݻ��ߴ����ã������ڵ��ú���ʱ�Ͳ��ܵó���ȷ�����

	for (int i = 0; i < m1; i++)
	{
		for (int j = 0; j < n2; j++)
		{
			c[i][j] = 0;
			for (int k = 0; k < m2; k++)	//ԭ���Ĵ���������k<n2����� 
			{
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	return Mc;
}



////////////////////////
/////��������///////////
////////////////////////
Matrix MatrixSimpleMulti(double k, Matrix M1)
{
	int m = M1.row;
	int n = M1.col;
	Matrix Mc(m, n);
	vector< vector<double> > &c = Mc.A;
	vector< vector<double> > &a = M1.A;

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			c[i][j] = k * a[i][j];
		}
	}

	return Mc;
}


////////////////////////
/////����ת��///////////
////////////////////////
Matrix MatrixTrans(Matrix M1)
{
	int m = M1.row;
	int n = M1.col;

	Matrix Mc(n,m);

	vector< vector<double> > &c = Mc.A;
	vector< vector<double> > &a = M1.A;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			c[i][j] = a[j][i];
		}
	}
	return Mc;
}


////////////////////////
/////��������///////////
////////////////////////
Matrix MatrixInv(Matrix Ma)
{
	int m = Ma.row;
	int n = Ma.col;

	Matrix Mc(m, n);

	vector< vector<double> > &a0 = Ma.A;
	vector< vector<double> > a = a0;
	vector< vector<double> > &b = Mc.A;

	int i, j, R, k;
	double max, temp;

	//����һ����λ��
	for (i = 0; i < n; i++)
	{
		b[i][i] = 1;
	}
	for (k = 0; k < n; k++)
	{
		max = 0; R = k;
		//Ѱ����Ԫ������¼���к�R
		for (i = k; i < n; i++)
		{
			temp = abs(a[i][k]);
			if (max < temp)
			{
				max = temp;
				R = i;
			}
		}
		//if (max == 0)//�����ԪΪ�㣬���ʾ����Ϊ�����󣬲�����
		//{
		//}

		//����k��R��
		if (R != k)
		{
			for (j = 0; j < n; j++)
			{
				temp = a[R][j];
				a[R][j] = a[k][j];
				a[k][j] = temp;

				temp = b[R][j];
				b[R][j] = b[k][j];
				b[k][j] = temp;
			}
		}

		//����Ԫ��Ϊ1
		for ( j = k + 1; j < n; j++)
		{
			a[k][j] /= a[k][k];
		}
		for (j = 0; j < n; j++)
		{
			b[k][j] /= a[k][k];
		}

		a[k][k] = 1;

		//k�л�Ϊ0
		//��a����
		for (j = k + 1; j < n; j++)
		{
			for (i = 0; i < k; i++)
			{
				a[i][j] -= a[i][k] * a[k][j];
			}
			for (i = k + 1; i < n; i++)
			{
				a[i][j] -= a[i][k] * a[k][j];
			}
		}

		//��b����
		for (j = 0; j < n; j++)
		{
			for (i = 0; i < k; i++)
			{
				b[i][j] -= a[i][k] * b[k][j];
			}
			for (i = k + 1; i < n; i++)
			{
				b[i][j] -= a[i][k] * b[k][j];
			}
		}
		for (i = 0; i < n; i++)
		{
			a[i][k] = 0;
		}
		a[k][k] = 1;
	}
	return Mc;
}

////////////////////////
/////��������ʽ/////////
////////////////////////
double det(Matrix M1, int n1)//n1Ϊ����M1�Ľ���
{
	int i_1, j_1, c;
	Matrix b(n1, n1);
	int p = 0, q = 0;
	double sum = 0;

	if (n1 == 1) return M1.A[0][0];
	for (i_1 = 0; i_1 < n1; i_1++)
	{
		for (c = 0; c < n1 - 1; c++)
		{
			if (c < i_1) p = 0;
			else p = 1;
			for (j_1 = 0; j_1 < n1 - 1; j_1++)
			{
				b.A[c][j_1] = M1.A[c + p][j_1 + 1];
			}
		}
		if(i_1 % 2 == 0) q = 1;
		else q = (-1);
		sum += M1.A[i_1][0] * q * det(b, n1 - 1);
	}
	return sum;
}

////////////////////////
/////��������ʽ/////////
////////////////////////
Matrix MatrixYuzishi(Matrix Ma,int r, int c)
{
	int m = Ma.row - 1;
	Matrix Mc(m,m);
	vector< vector<double> > aaa;
	
	for (int i = 0; i < Ma.row; i++)
	{
		for (int j = 0; j < Ma.row; j++)
		{
			if (j == c)
			{
				auto it = Ma.A[i].begin();//����A��һ��ά�ȣ����洢����һ����vector,����Զ�����ÿһ��һάԪ�ؽ������е�vector������
				Ma.A[i].erase(it + j);
			}
		}
		if (i != r)
		{
			aaa.push_back(Ma.A[i]);
		}
	}

	Mc.A = aaa;
	return Mc;
}

