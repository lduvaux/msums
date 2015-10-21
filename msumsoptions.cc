#include <iostream>


#include "msumsoptions.h"

using namespace std;


void MSUMSOptions::do_print_help()
	{
	cout <<
	"msums [-i FILE] [-o FILE] [-h] [-l] [[-s|-S STATLIST]...] "
	"[[-p|-P POPLIST]...]\n\n";
	cout <<
	"-i, --init FILE       Use this initialization file. [spinput.txt]\n"
	"-o, --output FILE     Use this output file. [ABCstat.txt]\n"
	"-h, --help            Print the help text and exit.\n"
	"-a, --list_stats      Print list of available stats and exit.\n"
	"-l, --print_per_locus Print stats per locus, don't print aggregate values.\n"
	"                      [false]\n"
	"-S, --keepStats LIST  Print stats in LIST. LIST is a space-separated list of\n"
	"                      stat names. 'all' selects all stats.\n"
	"-s, --dropStats LIST  Do *not* print stats in LIST (see above).\n"
	"-P, --keepPops LIST   Show populations or pairs in LIST. Populations can be\n"
	"                      specified as single number (e.g. '2'), or range \n"
	"                      (e.g. '1-5'). Pairs are specifies as p1xp2 (e.g. '1x2').\n"
	"                      'all' selects all populations, 'allxall' all pairs.\n"
	"-p, --dropPops LIST   Do *not* show populations/pairs in LIST (see above).\n"
	"-m, --multiStats LIST Show multi-population statistics in LIST. Use e.g. as:\n"
	"                      -m fst 1x2x3 3x4x5 -m f4 1x4x5x6\n";
	}

void MSUMSOptions::do_list_stats()
	{
	cout <<
    "### Conventions\n"
    "- The suffixes 'mean' and 'std' stand for mean and standard deviation,\n"
    "    respectively.\n"
    "- 'pop' and 'pops' stand for population and populations, respectively.\n"
    "- Populations are referred by indexes _i_ and _j_ and can range from\n"
    "    0 to n, where n is the number of sampled populations.\n"
    "    E.g. 'FST_ixj_mean': mean Fst across loci between\n"
    "    populations _i_ and _j_.\n"
    "- The coding of ancestral/derived alleles follow the ms convention:\n"
    "    0 -> ancestral\n"
    "    1 -> derived\n"
    "- Sampled alleles at a given SNP are represented by strings of 0s and 1s,\n"
    "    where populations are separated by a slash.\n"
    "    E.g., '0100/110101' represents the alleles of a SNP for which one\n"
    "    has sampled 4 and 6 chromosomes from population _i_ and _j_,\n"
    "    respectively.\n\n"
    "#### Within population statistics\n"
    "pairdif         sum of pairwise difference. (?)\n"
    "                    [to be checked, Martin can you confirm?]\n"
    "segr            number of segregating sites (i.e. SNPs) per locus.\n"
    "singlet         number of singletons sites per locus. (?)\n"
    "                    [to be checked Martin can you confirm?]\n"
    "thpi            Tajima's Theta, i.e. nucleotide diversity.\n"
    "thW             Watterson Theta.\n"
    "flDstar         Fu & Li’s D*.\n"
    "flFstar         Fu & Li’s F*.\n"
    "tD              Tajima's D. (?)\n"
    "                    [to be checked, Martin can you confirm?]\n"
    "R2              Ramos-Onsins R2 test.\n"
    "                    (Ramos-Onsins & Rozas, Mol.Biol.Evol 2002).\n"
    "                    [to be checked Martin can you confirm?\n"
    "                    Notably, I guess it's not the r2 estimates of\n"
    "                    linkage disequilibrium, right?]\n\n"
    "#### Between population statistics\n"
    "d_ixj           Raw nucleotidic divergence between pops i and j\n"
    "                    (Nei's Dxy, eq. 12.66, Nei and Kumar 2000).\n"
    "dn_ixj          Net nucleotidic divergence between pops i and j\n"
    "                    (Nei's DA, eq. 12.67, Nei and Kumar 2000).\n"
    "FST_ixj         FST sensu Hudson or Nst: (1-(pi_i+pi_j)/2)/pi_total.\n"
    "bialsites_ixj   mean number of bi-allelic sites per pop\n"
    "                    (infinite site model [**useful precision?**]).\n"
    "                    (number of bi-allelic sites in pop_i +\n"
    "                    number of bi-allelic sites in pop_j)/2\n"
    "multisites_ixj  mean number of multi-allelic (more than 2 alleles)\n"
    "                    sites per pop (infinite site model).\n"
    "                    I.e. (number of multi-allelic sites in pop_i +\n"
    "                    number of multi-allelic sites in pop_j)/2\n"
    "                    [to be checked]\n"
    "sfA_ixj         number of sites fixed for the derived allele in\n"
    "                    pop_A  and fixed for the ancestral allele in\n"
    "                    pop_B (1111/0000), where A=i and B=j.\n"
    "sfB_ixj         number of sites fixed for the ancestral allele in\n"
    "                    pop_A and fixed for the derived allele in\n"
    "                    pop_B (0000/1111), where A=i and B=j.\n"
    "sfout_ixj       **?** [to be checked]\n"
    "sxA_ixj         number of sites polymorphic in pop_A and fixed\n"
    "                    for the ancestral allele in pop_B (0101/0000),\n"
    "                    where A=i and B=j .\n"
    "sxB_ixj         number of sites fixed for the ancestral allele in\n"
    "                    pop_A and polymorphic in pop_B (0000/0101),\n"
    "                    where A=i and B=j .\n"
    "sxAfB_ixj       number of sites polymorphic in pop_A and fixed\n"
    "                    for the derived allele in pop_B (0101/1111),\n"
    "                    where A=i and B=j.\n"
    "sxBfA_ixj       number of sites fixed for the derived allele in\n"
    "                    pop_A and polymorphic in pop_B (1111/0010),\n"
    "                    where A=i and B=j.\n"
    "ss_ixj          number of sites with shared derived alleles between\n"
    "                    pop_i and pop_j (1010/1110). Mean over pops.\n"
    "                    [to be checked this stat should be symetrical\n"
    "                    between pops, so that the mean equal the value in\n"
    "                    each pop_Actually unless we divide by the total\n"
    "                    number of pops (that might be different from 2 but\n"
    "                    that would be surprising.]\n"
    "Rf_ixj          see Navascues et al. BMC Evol. Biol. 2014.\n"
    "                    [to be detailled]\n"
    "Rs_ixj          see Navascues et al. BMC Evol. Biol. 2014.\n"
    "                    [to be detailled]\n"
    "Wx2s1_ixj       see Navascues et al. BMC Evol. Biol. 2014.\n"
    "                    [to be detailled]\n"
    "Wx1s2_ixj       see Navascues et al. BMC Evol. Biol. 2014.\n"
    "                    [to be detailled]\n"
    "pattD_ixj       Patterson's D statistic used in the 'ABBA-BABA' test\n"
    "                    (Patterson et al. Genetics 2012).\n"
    "                    [How it is implemented, does it not need 4 pops?\n"
    "                    Is it F2 maybe?]\n";
	}
