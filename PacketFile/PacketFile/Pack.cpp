#include "Pack.h"

Pack::Pack()
{
	memset(&Fhead, 0x0, sizeof(Fhead));
	memset(PackedPath, 0x0, sizeof(PackedPath));
}

//����ļ�
void Pack::AddFile(const char * filePath, const char* oriPath)
{
	if (Fhead.Fnum >= MAX_FILE_NUM - 1)
	{
		cout << "�ļ��������ޣ�" << MAX_FILE_NUM << endl;
		return;
	}
	strcpy(Fhead.Fname[Fhead.Fnum], filePath);
	cout << "[����ļ�]-"<<Fhead.Fnum+1<<" " << filePath << endl;
	/**************/
	string tmp = oriPath;
	tmp = tmp.erase(tmp.find_last_of("\\"));
	strcpy(Fhead.oriPath[Fhead.Fnum], tmp.c_str());
	//cout << "[test]   ԭʼ·����" << tmp << endl;
	/**************/
	Fhead.Fnum++;
}

//��ʼ������ļ�
void Pack::SetPackedFile(char * desFile)
{
	memset(PackedPath, 0x0, sizeof(PackedPath));
	strcpy(PackedPath, desFile);
}

//��ȡ�ļ���С
//pf���Զ����Ʒ�ʽ�򿪵��ļ�ָ��
long Pack::GetFileSize(FILE *pf)
{
	fseek(pf, 0,/*SEEK_END*/ 2); //ָ���Ƶ��ļ�β
	return ftell(pf);
}


//����ļ�
void Pack::PackFile()
{
	if (Fhead.Fnum < 1)
	{
		cout << "û������ļ�" << endl;
		return;
	}
	if (strlen(PackedPath) < 1)
	{
		cout << "û��ָ������ļ����λ��" << endl;
		return;
	}

	FILE *desFile = NULL;
	FILE *CurrentFile = NULL;

	//��ȡ�ļ���С
	for (int i = 0; i < Fhead.Fnum; i++)
	{
		if ((CurrentFile = fopen(Fhead.Fname[i], "rb")) == NULL)
		{
			cout << "�ļ�" << Fhead.Fname[i] << "��ʧ�� [" << strerror(errno) << "]" << endl;
			return;
		}
		Fhead.Size[i] = GetFileSize(CurrentFile);
		fclose(CurrentFile);
	}
	//���Ŀ���ļ����Ƿ����
	CheckPath(PackedPath);
	//д�ļ�
	if ((desFile = fopen(PackedPath, "wb")) == NULL)
	{
		cout << "����ļ�����ʧ�� [" << strerror(errno) << "]" << endl;
		return;
	}
	fwrite(&Fhead, sizeof(Fhead), 1, desFile);
	for (int i = 0; i < Fhead.Fnum; i++)
	{
		if ((CurrentFile = fopen(Fhead.Fname[i], "rb")) == NULL)
		{
			cout << "�ļ�" << Fhead.Fname[i] << "��ʧ�� [" << strerror(errno) << "]" << endl;
			fclose(CurrentFile);
			fclose(desFile);
			return;
		}
		unsigned char *tmp = new unsigned char[Fhead.Size[i]];
		fread(tmp, Fhead.Size[i], 1, CurrentFile);
		if (ferror(CurrentFile))
		{
			cout << "�ļ�" << Fhead.Fname[i] << "��ʧ�� [" << strerror(errno) << "]" << endl;
			fclose(CurrentFile);
			fclose(desFile);
			return;
		}
		fwrite(tmp, Fhead.Size[i], 1, desFile);
		if (ferror(desFile))
		{
			cout << "�ļ�" << PackedPath << "д��ʧ�� [" << strerror(errno) << "]" << endl;
			fclose(CurrentFile);
			fclose(desFile);
			return;
		}
		delete[] tmp;
		fclose(CurrentFile);
	}
	fclose(desFile);
	cout << "# ������ #" << endl << endl;
}

//���
void Pack::UnpackFile(char *packedPathName, char *unpackedPathName)
{
	FILE *Packed = NULL;
	FILE *Current = NULL;

	//���ļ�
	if ((Packed = fopen(packedPathName, "rb")) == NULL) {
		cout << "�ļ�" << packedPathName << "��ʧ�� [" << strerror(errno) << "]" << endl;
		return;
	}
	memset(&Fhead, 0x0, sizeof(Fhead));
	fread(&Fhead, sizeof(Fhead), 1, Packed);
	PrintInfo();//��ӡ�ļ���Ϣ
	//cout << "# ��ʼ��� #" << endl;
	//cout << "[test] ԭ·��:" << packedPathName << endl;

	//����ļ���Ŀ��·��
	for (int i = 0; i < Fhead.Fnum; i++)
	{
		unsigned char *tmp = new unsigned char[Fhead.Size[i]];
		fread(tmp, Fhead.Size[i], 1, Packed);

		//��ȡ�ļ�����������·����
		//char tmpFileName[MAX_PATH_LEN];

		//string s1;
		//s1.assign(Fhead.Fname[i], strlen(Fhead.Fname[i]));
		//char s2[MAX_PATH_LEN];
		//strcpy(s2, getName(s1).c_str());
		//string str.assign(packedPathName,0,length(packedPathName)-length(s2));

		////string str = "C:\\Users\\15228\\Desktop\\software\\test_folder\\";
		//string aaa;
		//aaa.assign(Fhead.Fname[i], strlen(Fhead.Fname[i]));
		//const char *chaaaaa = aaa.replace(0, str.length(), "\\").c_str();
		//char tmpChar[MAX_PATH_LEN];
		//strcpy(tmpChar, chaaaaa);
		//memset(tmpFileName, 0x0, sizeof(tmpFileName));

		//cout << "-----------Unpack Processing-----------" << endl;
		string aaa;
		aaa.assign(Fhead.Fname[i], strlen(Fhead.Fname[i]));
		//cout << "[test] aaa:" << aaa << endl;
		/*char tmpFileName[MAX_PATH_LEN];
		int l = aaa.length(), j;
		for (j = l - 1; j >= 0; j--)
			if (aaa[j] == '\\') break;
		strcpy(tmpFileName,(aaa.substr(j + 1, l - j - 1)).c_str());
		cout << "[test] tmpFileName:" << tmpFileName << endl;*/

		/**************/
		char tmpFileName[MAX_PATH_LEN];
		string sss = Fhead.oriPath[i];
		string s = (aaa).erase(0, sss.length()+1);//�����ļ���
		strcpy(tmpFileName, s.c_str());
		//cout << "[test] tmpFileName:" << tmpFileName << endl; 
		/**************/

		//��ȡĿ��·��
		/*char tmpPathName[MAX_PATH_LEN];
		memset(tmpPathName, 0x0, sizeof(tmpPathName));
		strcpy(tmpPathName, packedPathName);
		cout << "tmpPathName 1:" << tmpPathName << endl;
		char* tmpC = tmpPathName + strlen(tmpPathName);
		while ('\\' != *tmpC)
			tmpC--;
		tmpC++;
		*tmpC = '\0';
		cout << "tmpPathName 2:" << tmpPathName << endl;
		strcat(tmpPathName, tmpFileName);
		cout << "tmpPathName 3:" << tmpPathName << endl;*/
		char tmpPathName[MAX_PATH_LEN];
		memset(tmpPathName, 0x0, sizeof(unpackedPathName));
		strcpy(tmpPathName, unpackedPathName);
		if (tmpPathName[strlen(tmpPathName) - 1] != '\\')
			strcat(tmpPathName,"\\");

		//cout << "[test] tmpPathName: " << tmpPathName << endl;
		strcat(tmpPathName, tmpFileName);
		//cout << "[test]            : " << tmpPathName << endl;

		Current = fopen(tmpPathName, "wb");
		if (Current == NULL)
		{
			CheckPath(tmpPathName);
			Current = fopen(tmpPathName, "wb");
		}
		fwrite(tmp, Fhead.Size[i], 1, Current);
		fclose(Current);
		delete[] tmp;
	}
	fclose(Packed);
	cout << "# ������ #" << endl<<endl;
}


//���pack�ڵ��ļ���Ϣ
void Pack::PrintInfo()
{
	cout <<endl<< "----------Information List----------" << endl;
	cout << "Tol:" << Fhead.Fnum << endl;
	for (int i = 0; i < Fhead.Fnum; i++)
		cout << Fhead.Fname[i] << "\t\t\t\t" << Fhead.Size[i] << "B" << endl;
	cout << "------------------------------------" << endl<<endl;
}

//��鲢�����ļ���
void Pack::CheckPath(string desPath)
{
	//Log &log = Log::getLog("main", "CheckPath");
	int loc = desPath.length();
	int f_loc = desPath.find("\\", 0);
	string subDIR;
	do
	{
		loc = desPath.find("\\", f_loc + 2);
		if (loc != -1)
		{
			subDIR = desPath.substr(0, loc);
			if (_mkdir(subDIR.c_str()) == 0)
				cout << "[����Ŀ¼] " << subDIR.c_str() << endl;
		}
		f_loc = loc;
	} while (f_loc != -1);
}
