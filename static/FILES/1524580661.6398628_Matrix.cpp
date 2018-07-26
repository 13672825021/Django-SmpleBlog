//#include "stdafx.h"
#include <cmath>
#include <cstdlib>

#include "Matrix.h"
////////////////////////
/////矩阵相加///////////
////////////////////////

Matrix MatrixAdd(Matrix M1, Matrix M2)
{
	int m1 = M1.row;
	int n1 = M1.col;
	int m2 = M2.row;
	int n2 = M2.col;//获得矩阵的行列数量

	//if ((m1 != m2) || (n1 != n2))
	//{
	//	//注意学习C++如何抛出异常，以后补上。
	//}
	Matrix Mc(m1, n1);
	vector< vector<double> > &c = Mc.A;
	vector< vector<double> > &a = M1.A;
	vector< vector<double> > &b = M2.A;//这里一定要注意按地址传递或者传引用，否则在调用函数时就不能得出正确结果。
	
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
/////矩阵相减///////////
////////////////////////
Matrix MatrixSub(Matrix M1, Matrix M2)
{
	int m1 = M1.row;
	int n1 = M1.col;
	int m2 = M2.row;
	int n2 = M2.col;//获得矩阵的行列数量

	//if ((m1 != m2) || (n1 != n2))
	//{
	//	//注意学习C++如何抛出异常，以后补上。
	//}
	Matrix Mc(m1, n1);
	vector< vector<double> > &c = Mc.A;
	vector< vector<double> > &a = M1.A;
	vector< vector<double> > &b = M2.A;//这里一定要注意按地址传递或者传引用，否则在调用函数时就不能得出正确结果。

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
/////矩阵相乘///////////
////////////////////////
Matrix MatrixMulti(Matrix M1, Matrix M2)
{
	int m1 = M1.row;
	int n1 = M1.col;
	int m2 = M2.row;
	int n2 = M2.col;//获得矩阵的行列数量

	//判断M1,M2是否可以相乘
	Matrix Mc(m1, n2);
	vector< vector<double> > &c = Mc.A;
	vector< vector<double> > &a = M1.A;
	vector< vector<double> > &b = M2.A;//这里一定要注意按地址传递或者传引用，否则在调用函数时就不能得出正确结果。

	for (int i = 0; i < m1; i++)
	{
		for (int j = 0; j < n2; j++)
		{
			c[i][j] = 0;
			for (int k = 0; k < m2; k++)	//原来的代码这里是k<n2，真坑 
			{
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	return Mc;
}



////////////////////////
/////矩阵数乘///////////
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
/////矩阵转置///////////
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
/////矩阵求逆///////////
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

	//定义一个单位阵
	for (i = 0; i < n; i++)
	{
		b[i][i] = 1;
	}
	for (k = 0; k < n; k++)
	{
		max = 0; R = k;
		//寻找主元，并记录其行号R
		for (i = k; i < n; i++)
		{
			temp = abs(a[i][k]);
			if (max < temp)
			{
				max = temp;
				R = i;
			}
		}
		//if (max == 0)//如果主元为零，则表示矩阵为奇异阵，不可逆
		//{
		//}

		//交换k与R行
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

		//将主元变为1
		for ( j = k + 1; j < n; j++)
		{
			a[k][j] /= a[k][k];
		}
		for (j = 0; j < n; j++)
		{
			b[k][j] /= a[k][k];
		}

		a[k][k] = 1;

		//k列化为0
		//对a矩阵
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

		//对b矩阵
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
/////矩阵行列式/////////
////////////////////////
double det(Matrix M1, int n1)//n1为矩阵M1的阶数
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
/////矩阵余子式/////////
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
				auto it = Ma.A[i].begin();//对于A的一次维度，他存储的是一个个vector,则可以对他的每一个一维元素进行所有的vector操作。
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

