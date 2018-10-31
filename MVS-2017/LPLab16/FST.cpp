#include "stdafx.h"


namespace FST
{
	RELATION::RELATION(char c = 0x00, short ns = NULL)
	{
		this->symbol = c;
		this->nnode = ns;
	};

	NODE::NODE() {	};

	NODE::NODE(short n, RELATION rel, ...)
	{

		RELATION* temp = &rel;
		int i = 0;
		this->relations = new RELATION[n];
		this->n_relation = n;
		while (i < n)
		{
			this->relations[i] = *(temp + i);
			i++;
		};
	};

	FST::FST(char* s, short ns, NODE n, ...)
	{
		this->nodes = new NODE[ns];
		NODE* temp = &n;
		short i = 0;
		this->string = s;
		this->nstates = ns;
		this->rstates = new short[ns];
		while (i < ns)
		{
			this->nodes[i] = *(temp + i);
			i++;
		};

	};

	FST::FST(short ns, NODE n, ...)
	{
		this->nodes = new NODE[ns];
		NODE* temp = &n;
		short i = 0;
		this->nstates = ns;
		this->rstates = new short[ns];
		while (i < ns)
		{
			this->nodes[i] = *(temp + i);
			i++;
		};

	}

	FST::FST(char* s, FST& fst)
	{
		this->nodes = new NODE[fst.nstates];
		NODE* temp = fst.nodes;
		short i = 0;
		this->string = s;
		this->nstates = fst.nstates;
		this->rstates = new short[this->nstates];
		while (i < nstates)
		{
			this->nodes[i] = *(temp + i);
			i++;
		};
	}

	bool execute(FST& fst)
	{
		int i, j;
		short* rstates2 = new short[fst.nstates];
		memset(fst.rstates, -1, fst.nstates * sizeof(short));
		memset(rstates2, -1, fst.nstates * sizeof(short));
		for (fst.rstates[0] = 0, fst.position = 0; fst.position < (strlen(fst.string)); fst.position++)
		{
			for (i = 0; i < fst.nstates; i++)
			{
				if (fst.rstates[i] == fst.position)
				{
					for (j = 0; j < fst.nodes[i].n_relation; j++)
					{
						if (fst.nodes[i].relations[j].symbol == fst.string[fst.position])
							rstates2[fst.nodes[i].relations[j].nnode] = fst.position + 1;
					};
				};
			};
			swap(fst.rstates, rstates2);
		};
		return (fst.rstates[fst.nstates - 1] == (strlen(fst.string)));
	};
}