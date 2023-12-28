#include "speechManager.h"

SpeechManager::SpeechManager()
{
	this->initSpeech();
	this->creatSpeaker();
	this->loadRecord();
}

SpeechManager::~SpeechManager()
{

}

void SpeechManager::show_view()
{
	cout << "********** 欢迎参加演讲比赛 ************" << endl;
	cout << "********** 1、开始演讲比赛 *************" << endl;
	cout << "********** 2、查看往届记录 *************" << endl;
	cout << "********** 3、清空比赛记录 *************" << endl;
	cout << "********** 0、退出比赛程序 *************" << endl;
	cout << "***************************************" << endl;
}

//退出程序
void SpeechManager::exitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

//初始化属性
void SpeechManager::initSpeech()
{
	this->v1.clear();
	this->v2.clear();
	this->winner.clear();
	this->v.clear();
	this->m_Record.clear();

	m_Index = 1;
}

//初始化选手
void SpeechManager::creatSpeaker()
{
	string nameseed = "ABCEDFGHIJKL";
	for (int i = 0; i < nameseed.size(); i++)
	{
		string name = "选手";
		name += nameseed[i];

		speaker sp;
		sp.m_name = name;

		for (int i = 0; i < 2; i++)
		{
			sp.m_score[i] = 0;
		}
		this->v1.push_back(i + 1000);
		this->v.insert({ i + 1000,sp });
	}
}

//开始比赛
void SpeechManager::startSpeech()
{
	//第一轮比赛

	//1、抽签
	this->speechDraw();
	//2、显示晋级结果
	this->speechContest();
	this->showScore();

	//第二轮比赛
	this->m_Index++;
	//1、抽签
	this->speechDraw();
	//2、比赛
	this->speechContest();
	//3、显示最终结果
	this->showScore();
	//4、保存结果
	this->saveRecord();

	//重置比赛
	this->initSpeech();
	this->creatSpeaker();
	this->loadRecord();
}

//抽签
void SpeechManager::speechDraw()
{
	cout << "第" << this->m_Index << "轮比赛的选手正在抽签" << endl;
	cout << "-------------------------------------------" << endl;
	cout << "抽签后演讲顺序如下" << endl;
	if (this->m_Index == 1)
	{
		random_shuffle(v1.begin(), v1.end());
		for (int i = 0; i < v1.size(); i++)
		{
			cout << v1[i] << ' ';
		}
		cout << endl;
	}
	else
	{
		random_shuffle(v2.begin(), v2.end());
		for (int i = 0; i < v2.size(); i++)
		{
			cout << v2[i] << ' ';
		}
		cout << endl;
	}
	cout << "-------------------------------------------" << endl;
	system("pause");
	cout << endl;
}

//评委评分
void SpeechManager::speechContest()
{
	cout << "-----------------第" << this->m_Index << "轮比赛正式开始-----------------" << endl;

	multimap<double, int, greater<double>> groupScore;

	int num = 0;//记录人数

	vector<int> v_Src;
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}

	//遍历每一个选手
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;

		//评委打分
		deque<double> d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;    //600-1000的数
			d.push_back(score);
		}
		//去除最高分和最低分
		sort(d.begin(), d.end(), greater<double>());
		d.pop_back();
		d.pop_front();

		//获取总分和平均分
		double sum = accumulate(d.begin(), d.end(),0.0f);
		double avg = sum / (double)d.size();

		this->v[*it].m_score[this->m_Index - 1] = avg;

		//6个人一组
		groupScore.insert({ avg,*it });
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "小组比赛名次" << endl;

			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "编号： " << it->second << " 姓名： " << this->v[it->second].m_name << " 成绩： " << this->v[it->second].m_score[this->m_Index - 1]<<endl;
			}

			//取前三名
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++)
			{
				if (this->m_Index == 1)
				{
					this->v2.push_back((*it).second);
				}
				else
				{
					this->winner.push_back((*it).second);
				}
			}
			groupScore.clear();

			cout << endl;
		}
	}
}

//显示晋级结果
void SpeechManager::showScore()
{
	cout << "-----------------第" << this->m_Index << "轮比赛的晋级结果如下-----------------" << endl;

	vector<int> vtemp;
	if (this->m_Index == 1)
	{
		vtemp = this->v2;
		
	}
	else
	{
		vtemp = winner;
		
	}


	for (vector<int>::iterator it = vtemp.begin(); it != vtemp.end(); it++)
	{
		cout << "选手编号： " << *it << " 姓名： " << this->v[*it].m_name << " 得分： " << this->v[*it].m_score[this->m_Index-1] << endl;
	}
	
	cout << endl;

	system("pause");
	system("cls");

	this->show_view();
}

//保存记录
void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);

	for (vector<int>::iterator it = this->winner.begin(); it != winner.end(); it++)
	{
		ofs << *it << ","
			<< this->v[*it].m_score[1] << ",";
	}
	ofs << endl;

	ofs.close();

	cout << "记录已保存!" << endl;
	this->fileEmpty = false;
}

//加载记录
void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);

	if (!ifs.is_open())
	{
		this->fileEmpty = true;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		this->fileEmpty = true;
		ifs.close();
		return;
	}

	//文件不为空
	this->fileEmpty = false;
	ifs.putback(ch);

	string data;
	int index = 1;
	while (ifs >> data)
	{
		vector<string> temp;

		int pos = -1;
		int start = 0;

		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				break;
			}
			string tmp = data.substr(start,pos-start);

			temp.push_back(tmp);
			start = pos + 1;
		}
		this->m_Record.insert({index,temp});
		index++;
	}
	ifs.close();

	
}


//显示往届记录
void SpeechManager::showRecord()
{

	if (this->fileEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		for (map<int, vector<string>>::iterator it = this->m_Record.begin(); it != this->m_Record.end(); it++)
		{
			cout << "第" << it->first << "届 " <<
				" 冠军编号 " << it->second[0] << " 得分：" << it->second[1] <<
				" 亚军编号 " << it->second[2] << " 得分: " << it->second[3] <<
				" 季军编号 " << it->second[4] << " 得分: " << it->second[4] << endl;
		}
		
	}

	system("pause");
	system("cls");

	this->show_view();
}

//清空记录
void SpeechManager::clearRecord()
{
	cout << "确认清空? " << endl;
	cout << "1、确认 " << endl;
	cout << "2、返回 " << endl;

	int select;
	cin >> select;

	if (select == 1)
	{
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
		//清空容器中的数据 
		this->initSpeech();
		this->creatSpeaker();
		this->loadRecord();

		cout << "清空成功! " << endl;
	}
	system("pause");
	system("cls");
	this->show_view();
}