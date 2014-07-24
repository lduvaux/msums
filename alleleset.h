#ifndef ALLELESET_H
#define ALLELESET_H


// Default implementation for AlleleSet. Note that this will become rather
// inefficient for larger alphabets (e.g. microsatellites).
template<class STATE>
class AlleleSet
	{
public:
	typedef STATE state_t;

protected:
	int _n_alleles;
	vector<int> _count;

public:
	void add(const state_t & a)
		{
		_count.resize(a, 0);
		_count[a]++;
		}

	int count(const state_t & a) const
		{
		return _count.size() > a ? _count[a] : 0;
		}

	// unsafe version
	int operator[](const state_t & a) const
		{
		return _count[a];
		}

	state_t find(size_t start = 0) const
		{
		for (size_t i=start; i<_count.size(); i++)
			if (_count[i] != 0)
				return state_t(i);
		
		return state_t(_count.size());
		}

	size_t size() const
		{
		return _count.size();
		}

	void resize(size_t size)
		{
		_count.resize(size);
		}

	void clear()
		{
		_count.clear();
		_n_alleles = 0;
		}

	void do_count()
		{
		_n_alleles = 0;

		for (size_t i=0; i<_count.size(); i++)
			if (_count[i] != 0)
				_n_alleles++;
		}

	int pairwise_difference() const
		{
		int diff = 0;

		for (size_t i=0; (i+1)<_count.size(); i++)
			for (size_t j=i+1; j<_count.size(); j++)
				diff += _count[i] * _count[j];
		
		return diff;
		}

	int n_singletons() const
		{
		int n = 0;

		for (size_t i=0; i<_count.size(); i++)
			if (_count[i] == 1) n++;

		return n;
		}

	bool is_singleton(const state_t & s) const
		{
		return count(s) == 1;
		}

	int n_alleles() const
		{
		return _n_alleles;
		}
	};

#endif	// ALLELESET_H
