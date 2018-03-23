#include <iostream>
#include <sdsl/suffix_arrays.hpp>
#include "internal/e_csa.hpp"

using namespace std;
using namespace lex;
using namespace sdsl;

/*
 * usage: lex input_file [opt]
 *
 * options:
 *
 *  -t	trailing character at the end of phrases (by default: no trailing char).
 *
 */
int main(int argc, char** argv){

	if(argc==1){

		cout << "Usage: lex input [opt]" << endl;
		cout << "options:"<<endl;
		cout << "   -t   trailing character at the end of phrases (by default: no trailing char)." << endl;

		exit(1);

	}


	string input = argv[1];

	bool trailing = false;

	if(argc==3) trailing = true;

	e_csa<csa_sada<> > csa(input);
	//e_csa<csa_wt<> > salcp(input);
	//e_csa<> salcp(input);

	auto n = csa.size()-1;//text's size

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

	//count BWT runs


	uint64_t R = 1;

	char prev = csa.BWT(0);

	for(uint64_t j=0;j<n+1;++j){

		char c = csa.BWT(j);

		if(c != prev){

			++R;
			prev = c;

		}

	}

	uint64_t j_=0, l_=0, s_=0, v=0;
	uint64_t j=0, l=0, s=0;

	char c;



	 //With trailing char

	if(trailing){

	 while(j+l < n){

			j_=j;
			l_=l;
			s_=s;

			j = v == 0 ? 0 : j_ + l_+1;
			l = csa.LCP(csa.ISA(j));
			s = l > 0 ? csa.SA(csa.ISA(j)-1) : 0;
			c = j+l < n ? csa.TEXT(j+l) : '#';

			//cout << "(" << s << "," << l << "," << c << ")  ";

			v++;

		}

	}else{


		while(j < n){

			l = csa.LCP(csa.ISA(j));

			//smallest char in lex order
			if(l == 0){

				//cout << "("  << salcp.TEXT(j) << ")  ";
				j++;

			}else{

				s = csa.SA(csa.ISA(j)-1);
				j = j + l;

				//cout << "(" << s << "," << l << ")  ";

			}

			v++;

		}

	}

	cout << endl;

	cout << "Computed parse " << (trailing?" with ":" without ") << "trailing character." << endl;
	cout << "Number of BWT runs: r = " << R << endl;
	cout << "Number of phrases: v = " << v << endl;


}
