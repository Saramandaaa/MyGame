// 2021.12.7, 20:20. By 唐梓皓，构造。
// 2021.12.7, 21:25. By 唐梓皓，sl部分重构。

#include "randsummoner.h"

RandSummoner::RandSummoner(int seed) :
	rangeHB(RAND_SUMMONER_RANGE_HB),
	minHB(RAND_SUMMONER_MIN_HB),
	cycleHB(RAND_SUMMONER_CYCLE_HB),
	basisHB(RAND_SUMMONER_BASIS_HB)
{
	makeSeedSheet();
	resetSeed(seed);
}

RandSummoner::RandSummoner(int newRangeHB, int newMinHB, int newCycleHB, int newBasisHB, int seed) :
	rangeHB(newRangeHB),
	minHB(newMinHB),
	cycleHB(newCycleHB),
	basisHB(newBasisHB)
{
	makeSeedSheet();
	resetSeed(seed);
}

RandSummoner::RandSummoner(RandSummoner& another) :
	rangeHB(another.rangeHB),
	minHB(another.minHB),
	cycleHB(another.cycleHB),
	basisHB(another.basisHB)
{
	range = another.range;
	min = another.min;
	cycle = another.cycle;
	basis = another.basis;

	seed = another.seed;
	stepAmt = another.stepAmt;
	x = another.x;

	rangeSeedSheet = another.rangeSeedSheet;
	minSeedSheet = another.minSeedSheet;
	cycleSeedSheet = another.cycleSeedSheet;
	basisSeedSheet = another.basisSeedSheet;
}

RandSummoner::~RandSummoner() {
	
}

void RandSummoner::resetSeed(int seed) {
	this->seed = seed;
	int rangeSeed = seed >> 24;
	int minSeed = (seed >> 16) & 255;
	int cycleSeed = (seed >> 8) & 255;
	int basisSeed = seed & 255;
	
	std::set<int>::iterator it;
	it = rangeSeedSheet.begin();
	for (int i = 0; i < rangeSeed; i++) {
		it++;
	}
	range = *it;
	it = minSeedSheet.begin();
	for (int i = 0; i < minSeed; i++) {
		it++;
	}
	min = *it;
	it = cycleSeedSheet.begin();
	for (int i = 0; i < cycleSeed; i++) {
		it++;
	}
	cycle = *it;
	it = basisSeedSheet.begin();
	for (int i = 0; i < basisSeed; i++) {
		it++;
	}
	basis = *it;

	stepAmt = 0;
	x = funBreak(basis);
}

double RandSummoner::fun(double x) {
	x = x * range + min;
	int multi = (int)(x / cycle);
	x = x / cycle - multi;
	return x;
}

double RandSummoner::funBreak(double x) {
	x = fun(x);
	if (x == fun(x)) x += cycle / 100;
	return x;
}

double RandSummoner::step() {
	x = funBreak(x);
	stepAmt++;
	return x;
}

unsigned int RandSummoner::sqrtInt(unsigned int x) {
	unsigned int res = 0;
	unsigned int remainer = 0;
	unsigned int divisor = 0;

	for (int i = 0; i < 16; i++) {
		remainer = (remainer << 2) + (x >> 30);
		x <<= 2;
		divisor = (res << 2) + 1;
		res <<= 1;
		if (remainer >= divisor) {
			remainer = remainer - divisor;
			res++;
		}
	}
	return res;
}
int RandSummoner::judgePrimeNumber(int x) {
	if (x < 2) return -1;
	if (x == 2 || x == 3) return 1;
	if (x % 2 == 0 || x % 3 == 0) return 0;

	int sqrtNum = sqrtInt(x);
	for (int i = 5; i <= sqrtNum; i += 6) {
		if (x % i == 0 || x % (i + 2) == 0) return 0;
	}
	return 1;
}
void RandSummoner::makePrimeNumSheet(int l, int r, bool dir, std::set<int>& s, int maxAmt) {
	int amt = 0;
	if (dir) {
		for (l; l < r && amt < maxAmt; l++) {
			if (!judgePrimeNumber(l)) continue;
			s.insert(l);
			amt++;
		}
	}
	else {
		for (r; r > l && amt < maxAmt; r--) {
			if (!judgePrimeNumber(r)) continue;
			s.insert(r);
			amt++;
		}
	}
}

void RandSummoner::makeSeedSheet() {
	minSeedSheet.clear();
	rangeSeedSheet.clear();
	cycleSeedSheet.clear();
	basisSeedSheet.clear();
	makePrimeNumSheet(0, rangeHB, false, rangeSeedSheet, 256);
	makePrimeNumSheet(0, minHB, false, minSeedSheet, 256);
	makePrimeNumSheet(0, cycleHB, false, cycleSeedSheet, 256);
	makePrimeNumSheet(0, basisHB, false, basisSeedSheet, 256);
}

int RandSummoner::getSeed() {
	return seed;
}

int RandSummoner::getStepAmt() {
	return stepAmt;
}

bool RandSummoner::copy(RandSummoner& another) {
	if (rangeHB != another.rangeHB || minHB != another.minHB || cycleHB != another.cycleHB || basisHB != another.basisHB) return false;
	range = another.range;
	min = another.min;
	cycle = another.cycle;
	basis = another.basis;

	seed = another.seed;
	stepAmt = another.stepAmt;
	x = another.x;

	rangeSeedSheet = another.rangeSeedSheet;
	minSeedSheet = another.minSeedSheet;
	cycleSeedSheet = another.cycleSeedSheet;
	basisSeedSheet = another.basisSeedSheet;
	
	return true;
}

void RandSummoner::forceCopy(RandSummoner& another) {
	rangeHB = another.rangeHB;
	minHB = another.minHB;
	cycleHB = another.cycleHB;
	basisHB = another.basisHB;

	range = another.range;
	min = another.min;
	cycle = another.cycle;
	basis = another.basis;

	seed = another.seed;
	stepAmt = another.stepAmt;
	x = another.x;

	rangeSeedSheet = another.rangeSeedSheet;
	minSeedSheet = another.minSeedSheet;
	cycleSeedSheet = another.cycleSeedSheet;
	basisSeedSheet = another.basisSeedSheet;
}

void RandSummoner::load(int anotherSeed, int anotherStepAmt) {
	resetSeed(anotherSeed);
	while (stepAmt != anotherStepAmt) {
		step();
	}
}

void RandSummoner::print() {
	using namespace std;
	cout << rangeHB << endl << minHB << endl << cycleHB << endl << basisHB << endl << endl;
	cout << range << endl << min << endl << cycle << endl << basis << endl << endl;
	cout << seed << endl << endl;
	cout << stepAmt << endl << x << endl << endl;
}
