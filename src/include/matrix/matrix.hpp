#ifndef __DBPL_MATRIX_HPP_SEEN
#define __DBPL_MATRIX_HPP_SEEN

#include <vector>

//#include "matrix_list.h"

using namespace::std;

class matrix
{
	public:

	long m, n;
	vector<vector<double>> entry_v;

	double entry (unsigned int Im, unsigned int In);

	void add (matrix mat);
	void scale (double sc);
	void times (matrix mat);
	void transpose ();
	void transpose_old ();
	void print ();
	matrix** lpu ();
	matrix inverse ();

	void resize (long Im, long In);
	void be_i ();
	void be_i (long Im, long In);
	void be_null ();
	void be_null (long Im, long In);
	__attribute__((always_inline)) inline void exchange_rows (long x, long y);

	int is_square ();
	int is_symmetric ();
	int is_skew_symmetric ();

	matrix (unsigned int Im, unsigned int In);
	~matrix ();
};

class LDU{
	public:
	matrix *P;
	matrix *L;
	matrix *D;
	matrix *U;
	int status;

	LDU (long m, long n);
	void destr ();
};

void matrix_cp (matrix m1, matrix m2);

matrix matadd (matrix m1, matrix m2);
matrix matmul (matrix m1, matrix m2);
matrix transpose (matrix m1);
LDU ldu (matrix m);
matrix m_inverse (matrix m);

#endif /* __DBPL_MATRIX_HPP_SEEN */
