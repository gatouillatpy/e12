
#include "impulse.h"
#include "indexer.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID INDEXER12::Collapse ( NODE12* _pNode )
{
	if ( _pNode->pA )
		Collapse( _pNode->pA );

	if ( _pNode->pB )
		Collapse( _pNode->pB );

	delete _pNode;
}



VOID INDEXER12::Free ( NODE12* _pNode )
{
	if ( _pNode->pA )
		Free( _pNode->pA );

	if ( _pNode->pB )
		Free( _pNode->pB );

	_pNode->pEntity->Release();
}



INDEXER12::NODE12* INDEXER12::Extract ( NODE12* & _pNode )
{
	NODE12* tNode;

	if ( _pNode->pA )
	{
		tNode = Extract( _pNode->pA );
		Evaluate(_pNode);
	}
	else
	{
		tNode = _pNode;
		_pNode = _pNode->pB;
	}	

	return tNode;
}



inline VOID INDEXER12::Evaluate ( NODE12* t )
{
	if ( t->pA )
	{
		SHORT lh = t->pA->nHeight;

		if ( t->pB )
		{
			SHORT rh = t->pB->nHeight;

			if ( lh >= rh )
				t->nHeight = 1 + lh;
			else
				t->nHeight = 1 + rh;

			t->nFactor = rh - lh;
		}
		else
		{
			t->nHeight = 1 + lh;

			t->nFactor = -lh;
		}
	}
	else
	{
		if ( t->pB )
		{
			SHORT rh = t->pB->nHeight;

			t->nHeight = 1 + rh;

			t->nFactor = rh;
		}
		else
		{
			t->nHeight = 1;

			t->nFactor = 0;
		}
	}
}

inline VOID INDEXER12::RotateLeft ( NODE12* & p )
{
	NODE12* q = p->pB;
	p->pB = q->pA;
	q->pA = p;
	Evaluate(p);
	p = q;
	Evaluate(q);
}

inline VOID INDEXER12::RotateRight ( NODE12* & q )
{
	NODE12* p = q->pA;
	q->pA = p->pB;
	p->pB = q;
	Evaluate(q);
	q = p;
	Evaluate(p);
}



VOID INDEXER12::Normalize ( NODE12* & t )
{
	SHORT bf = t->nFactor;
	if ( bf == -2 ) // left case
	{
		SHORT sbf = t->pA->nFactor;
		if ( sbf == -1 ) // left left case
		{
			RotateRight( t );
		}
		else if ( sbf == 1 ) // left right case
		{
			RotateLeft( t->pA );
			RotateRight( t );
		}
	}
	else if ( bf == 2 ) // right case
	{
		SHORT sbf = t->pB->nFactor;
		if ( sbf == -1 ) // right left case
		{
			RotateRight( t->pB );
			RotateLeft( t );
		}
		else if ( sbf == 1 ) // right right case
		{
			RotateLeft( t );
		}
	}
}
