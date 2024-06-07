#ifndef MATRIX_H_SEEN
#define MATRIX_H_SEEN

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

class asdLDU{
	public:
	matrix *P;
	matrix *L;
	matrix *D;
	matrix *U;
	int status;

	asdLDU (long m, long n);
	void destr ();
};

//typedef struct struct_LDU LDU;

/*class matrix: public matrix_list
{
	public:
	matrix_list *next;
};*/

void matrix_cp (matrix m1, matrix m2);

matrix matadd (matrix m1, matrix m2);
matrix matmul (matrix m1, matrix m2);
matrix transpose (matrix m1);
asdLDU ldu (matrix m);
matrix m_inverse (matrix m);

#endif /* MATRIX_H_SEEN */
