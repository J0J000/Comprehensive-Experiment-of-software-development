#pragma once
#include "StdAfx.h"

class Search
{
public:
	Search() {}
	~Search() {}
	static Search *getInstance();//����ʵ��
	void GetFileList(char *dir, vector<string> &filelist); //�����ļ����µ��ļ����б�(����Ƕ���ļ���)

	//void find(char *lpPath);
	//void _find(string path);
	//void ReadFile(const char* fileName);
	//void WriteFile(string fileName);
};
