#ifndef _OPTION_H_
#define _OPTION_H_

#include<stdio.h>
#include<vector>
#include<string>

#define MAX_OPTION_NUM 5

class OptionSet
{
private:
	// 选项为<int, std::string>型的对组，分别表示其id和描述，所有选项由std::vector型的选项集维护
	std::vector<std::pair<int, std::string>> optionSet; 
public:
	OptionSet();
	~OptionSet();

	// 插入选项，若id与已存在的选项重复，则插入失败
	bool insertOption(int id, std::string description);
	
	// 删除选项，若id不存在，则删除失败
	bool removeOption(int id);
	
	//清空选项集
	void clearOption();
	
	// 根据id找选项，返回对组地址
	std::pair<int, std::string>* findOption(int id);

	// 遍历选项集
	void traverse();
    int size();
};

#endif

