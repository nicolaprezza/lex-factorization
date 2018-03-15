#include <iostream>
#include <sdsl/suffix_arrays.hpp>
#include "internal/e_csa.hpp"

using namespace std;
using namespace bwsnp;
using namespace sdsl;

/*
 * usage: lex input_file
 */
int main(int argc, char** argv){

	string input = argv[1];

	e_csa<> salcp(input);
	auto n = salcp.size()-1;//text's size

	/*cout << "SA size = " << salcp.size() << endl;
	cout << "SA = " << endl;
	for(uint64_t i=0;i<n+1;++i) cout << salcp.SA(i) << " ";cout << endl;

	cout << "ISA = " << endl;
	for(uint64_t i=0;i<n+1;++i) cout << salcp.ISA(i) << " ";cout << endl;


	cout << "\nLCP = " << endl;
	for(uint64_t i=0;i<n+1;++i) cout << salcp.LCP(i) << " ";cout << endl;

	cout << "\ntext = " << endl;
	for(uint64_t i=0;i<n;++i) cout << salcp.TEXT(i); cout << endl;

	cout << "\nBWT = " << endl;
	for(uint64_t i=0;i<n+1;++i) cout << (salcp.BWT(i)==0?'#':salcp.BWT(i));cout << endl;*/


	uint64_t j_=0, l_=0, s_=0, v=0;
	uint64_t j=0, l=0, s=0;

	char c;


	while(j+l < n){

		j_=j;
		l_=l;
		s_=s;

		j = v == 0 ? 0 : j_ + l_+1;
		l = salcp.LCP(salcp.ISA(j));
		s = l > 0 ? salcp.SA(salcp.ISA(j)-1) : 0;
		c = j+l < n ? salcp.TEXT(j+l) : '#';

		//cout << "(" << s << "," << l << "," << c << ")  ";

		v++;

	}

	cout << endl;

	cout << "Number of phrases: " << v << endl;


}
