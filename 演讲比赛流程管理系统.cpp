#include <ctime>
#include "speechManager.h";

int main()
{
	srand((unsigned int)time(NULL));
	SpeechManager sm;
	
	sm.show_view();



	while (true)
	{
		int choice;
		cin >> choice;

		switch (choice)
		{
		case 1: sm.startSpeech();             //��ʼ����
			break;
		case 2: sm.showRecord();			  //�鿴��¼
			break;
		case 3: sm.clearRecord();             //��ռ�¼
			break;
		case 0: sm.exitSystem();			  //�˳�����
			break;
		}
	}

	system("pause");

	return 0;
}