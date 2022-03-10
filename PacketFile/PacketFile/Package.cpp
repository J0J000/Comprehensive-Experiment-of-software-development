#include "StdAfx.h"
#include "SearchFile.h"
#include "Pack.h"


int main()
{
	char flag[10];
	while (1)
	{
		printf("��ѡ��\n1������� 2������� 3�����˳�  ");
		scanf("%s", flag);
		switch (flag[0]) {
		case '1':
		{
			Pack pf;
			vector<string> vec_file;
			vector<string>::iterator f;
			char fileSrcPath[MAX_FILE_NUM][MAX_PATH_LEN];
			char fileDesPath[MAX_PATH_LEN] = "";
			int fNum = 0;

			while (1) {
				printf("\n�������Ҫ������ļ�·����������������롮#����:");
				scanf("%s", fileSrcPath[fNum]);
				if (!strcmp(fileSrcPath[fNum], "#"))
					break;
				vec_file.clear();
				Search::getInstance()->GetFileList(fileSrcPath[fNum], vec_file);
				//���Ҫ������ļ�
				for (f = vec_file.begin(); f < vec_file.end(); f++) {
					pf.AddFile((*f).c_str(), fileSrcPath[fNum]);
				}
				fNum++;
			}
			cout << endl<<"��" << fNum << "���ļ��������:";
			scanf("%s", fileDesPath);
			pf.SetPackedFile(fileDesPath);//��������ļ�
			pf.PackFile();//ִ�д��
			break;
		}
		case '2':
		{
			char fileSrcPath[MAX_PATH_LEN] = "";
			char fileDesPath[MAX_PATH_LEN] = "";
			printf("\n��������Ҫ������ļ�·��:");
			scanf("%s", fileSrcPath);
			printf("�����:");
			scanf("%s", fileDesPath);

			Pack upf;
			upf.UnpackFile(fileSrcPath, fileDesPath);//ִ�н��
			break;
		}
		case '3': 
		{
			cout<<"Exit..."<<endl; 
			exit(0);
		}
		default:
			cout << flag[0] << "�������" << endl;
		}
	}

	cin.clear();
	cin.get();

	system("pause");
	return 0;
}

