#pragma once
#include "StdAfx.h"

struct Record
{
	char Fname[MAX_FILE_NUM][MAX_PATH_LEN];//�ļ���
	unsigned int Size[MAX_FILE_NUM];//�ļ���С
	unsigned int Fnum;//�ļ�����
	char oriPath[MAX_FILE_NUM][MAX_PATH_LEN];//��¼ÿ���ļ���ԭʼ·��
};

class Pack
{
	Record Fhead;//�ļ�ͷ
	char PackedPath[MAX_PATH_LEN]; //���ɵĴ���ļ���·��

public:
	Pack();
	~Pack() {}
	void AddFile(const char * filePath, const char* oriPath); //����ļ�
	void SetPackedFile(char * desFile);//��ʼ������ļ�
	long GetFileSize(FILE *pf); //��ȡ�ļ���С pf���Զ����Ʒ�ʽ�򿪵��ļ�ָ��
	void PackFile();//����ļ�
	void UnpackFile(char *packedPathName, char *unpackedPathName);//���

private:
	void PrintInfo();//���pack�ڵ��ļ���Ϣ
	void CheckPath(string desPath);//��鲢�����ļ���
};


