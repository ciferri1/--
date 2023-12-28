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
		case 1: sm.startSpeech();             //开始比赛
			break;
		case 2: sm.showRecord();			  //查看记录
			break;
		case 3: sm.clearRecord();             //清空记录
			break;
		case 0: sm.exitSystem();			  //退出程序
			break;
		}
	}

	system("pause");

	return 0;
}