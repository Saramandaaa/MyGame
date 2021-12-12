#ifndef _OPTION_H_
#define _OPTION_H_

#include<stdio.h>
#include<vector>
#include<string>

#define MAX_OPTION_NUM 5

class OptionSet
{
private:
	// ѡ��Ϊ<int, std::string>�͵Ķ��飬�ֱ��ʾ��id������������ѡ����std::vector�͵�ѡ�ά��
	std::vector<std::pair<int, std::string>> optionSet; 
public:
	OptionSet();
	~OptionSet();

	// ����ѡ���id���Ѵ��ڵ�ѡ���ظ��������ʧ��
	bool insertOption(int id, std::string description);
	
	// ɾ��ѡ���id�����ڣ���ɾ��ʧ��
	bool removeOption(int id);
	
	//���ѡ�
	void clearOption();
	
	// ����id��ѡ����ض����ַ
	std::pair<int, std::string>* findOption(int id);

	// ����ѡ�
	void traverse();
    int size();
};

#endif

