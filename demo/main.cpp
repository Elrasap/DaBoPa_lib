#include <iostream>
#include <string>
#include <vector>
#include <assert.h>

#include "DaBoPa_lib.hpp"

using namespace::std;

int main ()
{
	matrix m(3, 3);
m.entry_v.at(0).at(0) = 1; m.entry_v.at(0).at(1) = 2; m.entry_v.at(0).at(2) = 2;
m.entry_v.at(1).at(0) = 1; m.entry_v.at(1).at(1) = 2; m.entry_v.at(1).at(2) = 3;
m.entry_v.at(2).at(0) = 1; m.entry_v.at(2).at(1) = 3; m.entry_v.at(2).at(2) = 1;

/*	matrix m2(3, 3);
m2.entry_v.at(0).at(0) = 1; m2.entry_v.at(0).at(1) = 1; m2.entry_v.at(0).at(2) = 1;
m2.entry_v.at(1).at(0) = 1; m2.entry_v.at(1).at(1) = 1; m2.entry_v.at(1).at(2) = 1;
m2.entry_v.at(2).at(0) = 0; m2.entry_v.at(2).at(1) = 1; m2.entry_v.at(2).at(2) = 1; */
/*
	matrix m3 = matmul (m, m2);
	m.print ();
	m2.print ();
	m3.print ();
	m3 = 
*/

	LDU ret (3, 3);
	ret = ldu (m);
	m.print ();
	cout << ret.status << endl;
	cout << "P =" << endl;
	ret.P->print ();
	cout << "L =" << endl;
	ret.L->print ();
	cout << "D =" << endl;
	ret.D->print ();
	cout << "m =" << endl;
	ret.U->print ();
	ret.destr ();

/*
	cout << "m =" << endl;
	m.print();

	cout << "u =" << endl;
	ret.U.at(3).print();
*/
	return 0;
}
