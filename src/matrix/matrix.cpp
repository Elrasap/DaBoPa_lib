#include <iostream>
#include <string>
#include <vector>
#include <assert.h>

#include "lib.hpp"

using namespace::std;


double matrix::entry (unsigned int Im, unsigned int In)
{
	return entry_v.at(Im).at(In);
}

void matrix::add (matrix mat)
{
	assert ((mat.m - m)*(mat.n - n));
	int x, y;
	for (x = 0; x < m; x++)
	{
		for (y = 0; y < n; y++)
		{
			entry_v.at(x).at(y) += mat.entry_v.at(x).at(y);
		}
	}
}

void matrix::scale (double sc)
{
	int x, y;
	for (x = 0; x < m; x++)
	{
		for (y = 0; y < n; y++)
		{
			entry_v.at(x).at(y) = sc * entry_v.at(x).at(y);
		}
	}
}


void matrix::times (matrix mat)
{
	assert (m == n && n == mat.n && mat.n == mat.m);

/*	cout << "ASDASDASD" << endl;
	print ();
	mat.print ();*/

	matrix m1 (m, m);
	m1 = matmul (*this, mat);
	matrix_cp (m1, *this);

/*	print ();
	cout << "ASDASDASD" << endl;*/
}

/*void matrix::times (matrix mat)
{
	assert (n == mat.m);
	matrix mret(m, mat.n);

	int x, y, i;
	for (x = 0; x < m; x++)
	{
		for (y = 0; y < mat.n; y++)
		{
			for (i = 0; i < n; i++)
			{
	mret.entry_v.at(x).at(y) += entry_v.at(x).at(i) * mat.entry_v.at(i).at(y);
			}
		}
	}
	matrix_cp (mret, *this);
}*/

void matrix::transpose ()
{
	int x, y;
	double d;

	// first we expand the matrix to be max(m,n) by max(m,n)

	vector<double> nullv(n, 0); // adding more rows if neccessary
	for (x = m; x < n; x++)
	{
		entry_v.push_back(nullv);
		for (y = n; y < m; y++)
		{
	entry_v.at(x).push_back(entry_v.at(y).at(x)); // transposing the "non-square part"
		}
	}

	for (x = 0; x < n; x++)
	{
		for (y = n; y < m; y++)
		{
			entry_v.at(x).push_back(0); // transposing the "non-square part"
		}
	}

	// transposing the "square part"
	for (x = 0; x < m && x < n; x++)
	{
		for (y = 0; y < x; y++)
		{
			// exchanging the entries
			d = entry_v.at(x).at(y);
			entry_v.at(x).at(y) = entry_v.at(y).at(x);
			entry_v.at(y).at(x) = d;
		}
	}

	// now we collapse the matrix into n by m
	for (x = m; x > n; x--)
	{
		entry_v.pop_back();
	}

	for (; x >= 0; x--) // starts at x == n
	{
		for (y = n; y > m; y--)
		{
			entry_v.at(x).pop_back();
		}
	}

	// and finally we switch m and n
	m += n;
	n -= m;
	m += n;
	n = -n;
}

void matrix::transpose_old ()
{
	matrix tr(n,m);
	int x, y, i, ii;
	for (x = 0; x < m; x++)
	{
		for (y = 0; y < n; y++)
		{
			tr.entry_v.at(y).at(x) = entry_v.at(x).at(y);
		}
	}


	if (m > n)
	{
		for (i = m; i > n; i--) // removing the last m-n rows
		{
			entry_v.pop_back();
		}

		for (i = 0; i < n; i++) // appending each row by m-n
		{
			for (ii = 0; ii < m-n; ii++)
			{
				entry_v.at(i).push_back(0);
			}
		}
	}
	if (m < n)
	{
		vector<double> vnull(m, 0);
		for (i = m; i > n; i--) // adding m-n rows
		{
			entry_v.push_back(vnull);
		}

		for (i = 0; i < n; i++) // removing m-n entries from the first n rows
		{
			for (ii = 0; ii < m - n; ii++)
			{
				entry_v.at(i).pop_back();
			}
		}

	}

	// switching m and n
	m += n;
	n -= m;
	m += n;
	n = -n;

	matrix_cp(tr, *this);
}

void matrix::print ()
{
	int x, y;
	for (x = 0; x < m; x++)
	{
		for (y = 0; y < n; y++)
		{
			cout << entry_v.at(x).at(y);
			cout << ' ';
		}
		cout << endl;
	}
}

matrix** matrix::lpu()
{
	matrix **out;
	matrix l(m,m), p(m,m), u(m,n);

	matrix_cp (*this, u);

	out[0] = &l;
	out[1] = &p;
	out[2] = &u;
	return out;
}

matrix matrix::inverse()
{
	return *this;
}


void matrix::resize (long Im, long In)
{
	int x, y;
	vector<double> dummy;

	if (n < In)
	{
		for (x = 0; x < m; x++)
		{
			for (y = n; y < In; y++)
			{
				entry_v.at(x).push_back (0);
			}
		}
	} else if (n > In)
	{
		for (x = 0; x < m; x++)
		{
			for (y = n; y > In; y--)
			{
				entry_v.at(x).pop_back ();
			}
		}
	}

	n = In;

	for (x = 0; x < n; x++)
	{
		dummy.push_back (0);
	}

	if (m < Im)
	{
		for (x = m; x < Im; x++)
		{
			entry_v.push_back (dummy);
		}
	} else if (m > Im)
	{
		for (x = Im; x < m; x++)
		{
			entry_v.pop_back ();
		}
	}
	
	m = Im;
}

void matrix::be_i ()
{
	assert (!(m - n));
	int x,y;
	for (x = 0; x < m; x++)
	{
		for (y = 0; y < n; y++)
		{
			if (x == y)
			{
				entry_v.at(x).at(y) = 1;
			} else
			{
				entry_v.at(x).at(y) = 0;
			}
		}
	}

}

void matrix::be_i (long Im, long In)
{
	resize (Im, In);
	be_i ();
}

void matrix::be_null ()
{
	int x,y;
	for (x = 0; x < m; x++)
	{
		for (y = 0; y < n; y++)
		{
			entry_v.at(x).at(y) = 0;
		}
	}
}

#ifdef __DBPL_MATRIX_HPP_OPTION_EXCHANGE_ROWS_1
__attribute__((always_inline)) inline void matrix::exchange_rows (long x, long y)
{
	double cp;
	int i;

	for (i = 0; i < n; i++)
	{
		cp = entry_v.at(x).at(i);
		entry_v.at(x).at(i) = entry_v.at(y).at(i);
		entry_v.at(y).at(i) = cp;
	}
}
#endif /* __DBPL_MATRIX_HPP_OPTION_EXCHANGE_ROWS_1 */

#ifdef __DBPL_MATRIX_HPP_OPTION_EXCHANGE_ROWS_2
/*__attribute__((always_inline)) */ inline void matrix::exchange_rows (long x, long y)
{
	int i;

	for (i = 0; i < n; i++)
	{
		entry_v.at(x).at(i) += entry_v.at(y).at(i);
		entry_v.at(y).at(i) -= entry_v.at(x).at(i);
		entry_v.at(x).at(i) += entry_v.at(y).at(i);
		entry_v.at(y).at(i) = -1 * entry_v.at(y).at(i);
	}
}
#endif /* __DBPL_MATRIX_HPP_OPTION_EXCHANGE_ROWS_2 */

void matrix::be_null (long Im, long In)
{
	be_null ();
	resize (Im, In);
}



int matrix::is_square ()
{
	return !(m - n);
}

int matrix::is_symmetric ()
{
	assert (m == n);
	int x, y, out;
	out = 1;
	for (x = 0; x < m; x++)
	{
		for (y = 0; y < x; y++) // No need to check the diagonal
		{
			if (entry(x,y) != entry(y,x))
			{
				out = 0;
			}
		}
	}
	return out;
}

int matrix::is_skew_symmetric ()
{
	assert (m == n);
	int x, y, out;
	out = 1;
	for (x = 0; x < m; x++)
	{
		for (y = 0; y <= x; y++) // Must also check the diagonal!
		{
			if (entry(x,y) != -entry(y,x))
			{
				out = 0;
			}
		}
	}
	return out;
}

matrix::matrix (unsigned int Im, unsigned int In)
{
	assert(Im*In);
//	cout << "A matrix object has been created.\n" << endl;
	m = Im;
	n = In;

	vector<double> init_v(n, 0);
	for (int i = 1; i <= m; i++)
	{
		entry_v.push_back (init_v);
	}
}

matrix::~matrix ()
{
//	cout << "A matrix object has been deleted.\n" << endl;
}


void matrix_cp (matrix m1, matrix m2)
{
	/*cout << "m1 ";
	cout << m1.m;
	cout << m1.n;
	cout << "\nm2 ";
	cout << m2.m;
	cout << m2.n;
	cout << '\n';*/

	cout << "=== matrix_cp()" << endl;
	m1.print ();
	m2.print ();
	cout << "=== matrix_cp()" << endl;
	assert (m1.m == m2.m && m1.n == m2.n);

	int x, y;
	for (x = 0; x < m1.m; x++)
	{
		for (y = 0; y < m1.n; y++)
		{
			m2.entry_v.at(x).at(y) = m1.entry_v.at(x).at(y);
		}
	}
	
	cout << "=== matrix_cp()" << endl;
	m1.print ();
	m2.print ();
	cout << "=== matrix_cp()" << endl;
	assert (m1.m == m2.m && m1.n == m2.n);

}


__attribute__((flatten)) matrix matadd (matrix m1, matrix m2) // if flatten neccessary?
								// (matrix_cp !)
{
	assert (m1.m == m2.m && m1.n == m2.n);

	matrix mret (m1.m, m1.n);
	matrix_cp (mret, mret);
	mret.add (m2);

	return mret;
}

matrix matmul (matrix m1, matrix m2)
{
	assert (m1.n == m2.m);
	matrix mret(m1.m, m2.n);

	int x, y, i;
	for (x = 0; x < m1.m; x++)
	{
		for (y = 0; y < m2.n; y++)
		{
			for (i = 0; i < m1.n; i++)
			{
	mret.entry_v.at(x).at(y) += m1.entry_v.at(x).at(i) * m2.entry_v.at(i).at(y);
			}
		}
	}
	return mret;
}

matrix transpose (matrix m1)
{
	matrix tr(m1.n,m1.m);
	int x, y;
	for (x = 0; x < m1.m; x++)
	{
		for (y = 0; y < m1.n; y++)
		{
			tr.entry_v.at(y).at(x) = m1.entry_v.at(x).at(y);
		}
	}
	return tr;
}

LDU ldu (matrix a) // Why, Gauss, of course.
{
	vector<matrix> steps;
	vector<matrix> perm;
	matrix dummy (a.m, a.m);
	long x, y, z;
	int i;
	double l;
	LDU ret (a.m, a.n);

	// matrix_cp (a, *(ret.U)); // initing. ret

	// initing. ret
	for (x = 0; x < a.m; x++) // copying a to U
	{
		for (y = 0; y < a.n; y++)
		{
			ret.U->entry_v.at(x).at(y) = a.entry_v.at(x).at(y);
		}
	}
	ret.P->be_i ();
	ret.L->be_i ();
	ret.D->be_i ();

	ret.status = 0; // 0: OK, -1: singular, -2: row exchange req. or sing., -3: last pivot 0;

/*	cout << "===" << endl;
	a.print ();
	ret.U->print ();
	cout << "===" << endl; */

	for (y = 0; y < a.n; y++) // cycling through the columns
	{
		x = y;
		cout << "===" << endl;
		ret.U->print ();


		if (0 == ret.U->entry_v.at(x).at(y)) // checking if a row exchange is neccessary
		{
			for (; x < a.m && 0 == ret.U->entry_v.at(x).at(y) ; x++) // finding an appropriate row
			{}					// (The original value was
								// the same as that of why, and why shall not change.)
			if (x == a.m)
			{
				ret.status = -1; // No possible row exchange, the matrix is singular.
				return ret;
			}

			// exchanging rows
			ret.U->exchange_rows (x, y);

			// we must add a permutation matrix to perm
			dummy.be_i ();
			dummy.exchange_rows (x, y); // make it the appropriate perm. matrix
			perm.push_back(dummy);

			// and to also to steps
			dummy.transpose (); // The transpose is the inverse
			steps.push_back(dummy);

			x = y; // restore original value

			//ret.status = -2;
			//return ret;
		}

		// eliminating the entries below the pivot
		for (x++; x < a.m; x++)
		{
			//ret.U->print ();
			//assert (0 != ret.U->entry_v.at(y).at(y));
			l = ret.U->entry_v.at(x).at(y) / ret.U->entry_v.at(y).at(y);
			dummy.be_i ();
			dummy.entry_v.at(x).at(y) = l;
			steps.push_back (dummy);
			for (z = 0; z < a.n; z++)
			{
				ret.U->entry_v.at(x).at(z) -= l * ret.U->entry_v.at(y).at(z);
			}
		}

	}

	// Calculating P by multuplying the inverses of the perms. in reverse order
	while (0 != perm.size())
	{
		*(ret.P) = matmul (perm.back(), *(ret.P));
		perm.pop_back ();
	}

	// Calculating L by multuplying the inverses of the steps in reverse order
	while (0 != steps.size())
	{
		*(ret.L) = matmul (steps.back(), *(ret.L));
		steps.pop_back ();
	}
	// and multiplying by the inverse of P (which is the transpose)
	*(ret.L) = matmul (transpose (*(ret.P)), *(ret.L));

	// factoring DU into D and U
	if (0 == ret.U->entry_v.at(a.m - 1).at(a.n - 1))
	{
		ret.status = -3;
	}
	for (x = 0; x < a.m; x++)
	{
		ret.D->entry_v.at(x).at(x) = l = ret.U->entry_v.at(x).at(x);
		for (y = x; y < a.n; y++)
		{
			ret.U->entry_v.at(x).at(y) = ret.U->entry_v.at(x).at(y) / l;
		}
	}

	return ret;
}

matrix m_inverse (matrix m)
{
	return m;
}

LDU::LDU (long m, long n)
{
	P = new matrix (m, m);
	L = new matrix (m, m);
	D = new matrix (m, m);
	U = new matrix (m, n);
}

void LDU::destr ()
{
	delete P;
	delete L;
	delete D;
	delete U;
}
