#pragma once
#ifndef _RAND_SUMMONER_
#define _RAND_SUMMONER_
// 此类用于生成随机数，算法具体原理未知，初步测试表明没有特殊种子

#include<iostream>
#include<stdio.h>
#include<fstream>
#include<set>

// 定义了参数取值表的上限，对应的参数表将从该上限向下取256个质数作为候选参数，一旦更改
#define RAND_SUMMONER_RANGE_HB 100000000
#define RAND_SUMMONER_MIN_HB 1000000
#define RAND_SUMMONER_CYCLE_HB 10000
#define RAND_SUMMONER_BASIS_HB 10000

class RandSummoner
{
	// 初始化为上面的宏，类中的其他对象、函数使用这4个属性，而不会直接使用宏
	// 也作为识别信息，这4个数据不同的对象无法互相load
	int rangeHB;
	int minHB;
	int cycleHB;
	int basisHB;

	// 基本参数，随机数生成依赖于这4个值
	double range;
	double min;
	double cycle;
	double basis;

	// 种子，只能在resetSeed函数中被修改，默认为0
	int seed;

	// 记录取了多少个随机数，实际上只需记录种子
	int stepAmt;
	double x;

	// range, min, cycle, basis的取值表
	std::set<int> rangeSeedSheet;
	std::set<int> minSeedSheet;
	std::set<int> cycleSeedSheet;
	std::set<int> basisSeedSheet;

	// 依据类中4个基本参数和输入的x生成x的下一个随机数
	// 下一个随机数是范围为[0, 1]中的double值
	// 返回下一个随机数的值
	double fun(double x);

	// 在fun的基础上添加了跳出单个数字循环的功能
	double funBreak(double x);

	// 下面3个函数都是基本算法，与主要功能没有直接关系
	// 无符号整数快速开平方
	unsigned int sqrtInt(unsigned int x);
	// 判断x是否为素数，返回值为1代表是，为0代表不是，为-1代表输入错误
	int judgePrimeNumber(int x);
	// 找出l~r（前开后闭）范围内的所有素数，放入s中，dir表示方向，maxAmt表示最多找多少个
	void makePrimeNumSheet(int l, int r, bool dir, std::set<int>& s, int maxAmt);

	// 根据当前的4个上界值，构造4个基本参数的取值表
	void makeSeedSheet();

public:
	// 产生一个随机数生成器，种子默认为0，类型为长整型
	RandSummoner(int seed = 0);

	// 在普通构造基础上，允许自定义4个上界值，建议不要使用
	RandSummoner(int newRangeHB, int newMinHB, int newCycleHB, int newBasisHB, int seed = 0);

	// 拷贝构造，包括4个上界值在内的所有参数都将被直接拷贝
	RandSummoner(RandSummoner& another);

	~RandSummoner();
	
	// 重设种子，stepAmt和x将被一起重置
	void resetSeed(int seed);

	// 步增函数，每次调用依据当前x值和4个基本参数产生下一个随机数，并令stepAmt加1
	// 返回下一个随机数的值
	double step();

	

	// 返回seed的值
	int getSeed();
	// 返回stepAmt的值
	int getStepAmt();
	// 从另一个RandSummoner拷贝数据，如果4个上界值不同将无法拷贝并返回false，否则返回true
	bool copy(RandSummoner& another);
	// 强制加载，完全拷贝另一个RandSummoner的值，类似于以RandSummoner&为参数的构造函数
	void forceCopy(RandSummoner& another);

	// 依据传入的seed和stepAmt加载
	void load(int anotherSeed, int anotherStepAmt);

	// 仅供测试用
	void print();
};

#endif
