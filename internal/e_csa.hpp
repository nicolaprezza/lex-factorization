#include <iostream>
#include <sdsl/lcp.hpp>
#include <sdsl/suffix_arrays.hpp>

using namespace std;
using namespace sdsl;

namespace lex{

/*
 * extended compressed suffix array: SA, LCP, text, BWT
 *
 * the LCP is stored using less bits for shorter values
 * the SA by default is not compressed. Specify csa_sada<> or csa_wt<> in template arg
 */
template<class sa_type = csa_bitcompressed<> >
class e_csa{

public:

	e_csa(){}

	e_csa(string file){

		    cache_config cc(false); // do not delete temp files after SA_ construction
		    construct(SA_, file, 1);

		    cc.delete_files = true; // delete temp files after LCP_ construction
		    construct(LCP_, file, 1);

	}


	uint64_t SA(uint64_t i){

		return SA_[i];

	}

	uint64_t ISA(uint64_t i){

		return SA_.isa[i];

	}

	char BWT(uint64_t i){

		return SA_.bwt[i];

	}

	char TEXT(uint64_t i){

		return SA_.text[i];

	}

	uint64_t LCP(uint64_t i){

		return LCP_[i];

	}

	uint64_t size(){

		return SA_.size();

	}


	sa_type SA_;
	lcp_bitcompressed<> LCP_;


};

}
