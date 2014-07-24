#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include "msdatafile.h"
#include "sputil.h"

using namespace std;

typedef SPIOException SPIOE;


/** Reads datasetfile and extracts DNA sequences from all population and 
	the outgroup.
	@param inp file to read data from.
	@param dataset number of current data set.
	@param n_sequences #sequences[population][locus].
	@param n_sites number of sites[locus].
	@param sequences sequences[population][locus][number].
	@param outgroup outgroup data[locus].
	*/
void read_dataset(istream & inp, size_t dataset, 
	const vector<vector<size_t> > & n_sequences, const vector<size_t> & n_sites, 
	vector<vector<Sample<string, char> > > & sequences, vector<string> & outgroup)
	{
	size_t nseg;

	const string match_segsites = "segsites:";
	const string match_positions = "positions:";
	string str;

	// this is a bit non-obvious
	const size_t n_pops = n_sequences.size();
	const size_t n_loci = n_sites.size();

	// loop over all loci
	for (size_t l=0; l<n_loci; l++)
		{
		istringstream itmp;
		string stmp;
		// skip all lines that don't start with 'segsites:'
		do
			{
			// next non-empty line
			skip_space(inp, str);
			itmp.clear();
			itmp.str(str);
			// get first part of line
			stmp = "";
			itmp >> stmp;

			if (!inp.good() || itmp.fail())
				throw SPIOE(string(ERR_LOC " Error in reading dataset ") +
					lexical_cast<string>(dataset) + " at locus " +
					lexical_cast<string>(l) + ": expected '" + match_segsites +
					"', found '" + stmp + "'");
			}
		while (stmp != match_segsites);

		itmp >> nseg;

		if (itmp.fail())
			throw SPIOE(string(ERR_LOC " Error in reading dataset ") + 
				lexical_cast<string>(dataset) + " at locus " + 
				lexical_cast<string>(l) +  ": couldn't read number of seg sites ");

		if (nseg > n_sites[l]) 
			{	/*if too many segregating sites*/
			nseg = n_sites[l];
			// TODO: ask Ludovic whether error message in this case
			//errorfile << "\nerror in reading dataset: nseg=" << nseg 
			//	<< " > total number of sites=" << n_sites[l] 
			//	<< " in locus " << l;
			}

		skip_space(inp, str); // skip blanks

		// for all population
		for (size_t p=0; p<n_pops; p++)
			{
			sequences[p][l].set_n_poly_sites(nseg);
			// all sequences of population p
			for (size_t h=0; h<n_sequences[p][l]; h++) 
				{	
				string & seq = sequences[p][l].sequence(h);
				seq.reserve(n_sites[l]);

				// careful, this is two things in one
				if (nseg>0 && !getline(inp, seq))
					throw SPIOE(
						string(ERR_LOC 
							" error in reading dataset: cannot read seq of "
							"haplotype ") + 
						lexical_cast<string>(h) + " in population " +
						lexical_cast<string>(p) + " at locus " +
						lexical_cast<string>(l));

				//cerr << nseg << " #### " << seq << "\n";

				// pad with 0s
				seq.resize(n_sites[l], '0');

				}
			}	/* end loop over haplotypes in population A*/
			
		outgroup[l].clear();
		outgroup[l].resize(n_sites[l], '0');
		}	/*end loop over loci*/
	}		 /*end of get_dataset*/


