#pragma once
#ifndef _RAND_SUMMONER_
#define _RAND_SUMMONER_
// ��������������������㷨����ԭ��δ֪���������Ա���û����������

#include<iostream>
#include<stdio.h>
#include<fstream>
#include<set>

// �����˲���ȡֵ������ޣ���Ӧ�Ĳ������Ӹ���������ȡ256��������Ϊ��ѡ������һ������
#define RAND_SUMMONER_RANGE_HB 100000000
#define RAND_SUMMONER_MIN_HB 1000000
#define RAND_SUMMONER_CYCLE_HB 10000
#define RAND_SUMMONER_BASIS_HB 10000

class RandSummoner
{
	// ��ʼ��Ϊ����ĺ꣬���е��������󡢺���ʹ����4�����ԣ�������ֱ��ʹ�ú�
	// Ҳ��Ϊʶ����Ϣ����4�����ݲ�ͬ�Ķ����޷�����load
	int rangeHB;
	int minHB;
	int cycleHB;
	int basisHB;

	// ���������������������������4��ֵ
	double range;
	double min;
	double cycle;
	double basis;

	// ���ӣ�ֻ����resetSeed�����б��޸ģ�Ĭ��Ϊ0
	int seed;

	// ��¼ȡ�˶��ٸ��������ʵ����ֻ���¼����
	int stepAmt;
	double x;

	// range, min, cycle, basis��ȡֵ��
	std::set<int> rangeSeedSheet;
	std::set<int> minSeedSheet;
	std::set<int> cycleSeedSheet;
	std::set<int> basisSeedSheet;

	// ��������4�����������������x����x����һ�������
	// ��һ��������Ƿ�ΧΪ[0, 1]�е�doubleֵ
	// ������һ���������ֵ
	double fun(double x);

	// ��fun�Ļ����������������������ѭ���Ĺ���
	double funBreak(double x);

	// ����3���������ǻ����㷨������Ҫ����û��ֱ�ӹ�ϵ
	// �޷����������ٿ�ƽ��
	unsigned int sqrtInt(unsigned int x);
	// �ж�x�Ƿ�Ϊ����������ֵΪ1�����ǣ�Ϊ0�����ǣ�Ϊ-1�����������
	int judgePrimeNumber(int x);
	// �ҳ�l~r��ǰ����գ���Χ�ڵ���������������s�У�dir��ʾ����maxAmt��ʾ����Ҷ��ٸ�
	void makePrimeNumSheet(int l, int r, bool dir, std::set<int>& s, int maxAmt);

	// ���ݵ�ǰ��4���Ͻ�ֵ������4������������ȡֵ��
	void makeSeedSheet();

public:
	// ����һ�������������������Ĭ��Ϊ0������Ϊ������
	RandSummoner(int seed = 0);

	// ����ͨ��������ϣ������Զ���4���Ͻ�ֵ�����鲻Ҫʹ��
	RandSummoner(int newRangeHB, int newMinHB, int newCycleHB, int newBasisHB, int seed = 0);

	// �������죬����4���Ͻ�ֵ���ڵ����в���������ֱ�ӿ���
	RandSummoner(RandSummoner& another);

	~RandSummoner();
	
	// �������ӣ�stepAmt��x����һ������
	void resetSeed(int seed);

	// ����������ÿ�ε������ݵ�ǰxֵ��4����������������һ�������������stepAmt��1
	// ������һ���������ֵ
	double step();

	

	// ����seed��ֵ
	int getSeed();
	// ����stepAmt��ֵ
	int getStepAmt();
	// ����һ��RandSummoner�������ݣ����4���Ͻ�ֵ��ͬ���޷�����������false�����򷵻�true
	bool copy(RandSummoner& another);
	// ǿ�Ƽ��أ���ȫ������һ��RandSummoner��ֵ����������RandSummoner&Ϊ�����Ĺ��캯��
	void forceCopy(RandSummoner& another);

	// ���ݴ����seed��stepAmt����
	void load(int anotherSeed, int anotherStepAmt);

	// ����������
	void print();
};

#endif
