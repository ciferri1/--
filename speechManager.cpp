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
	cout << "********** ��ӭ�μ��ݽ����� ************" << endl;
	cout << "********** 1����ʼ�ݽ����� *************" << endl;
	cout << "********** 2���鿴�����¼ *************" << endl;
	cout << "********** 3����ձ�����¼ *************" << endl;
	cout << "********** 0���˳��������� *************" << endl;
	cout << "***************************************" << endl;
}

//�˳�����
void SpeechManager::exitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

//��ʼ������
void SpeechManager::initSpeech()
{
	this->v1.clear();
	this->v2.clear();
	this->winner.clear();
	this->v.clear();
	this->m_Record.clear();

	m_Index = 1;
}

//��ʼ��ѡ��
void SpeechManager::creatSpeaker()
{
	string nameseed = "ABCEDFGHIJKL";
	for (int i = 0; i < nameseed.size(); i++)
	{
		string name = "ѡ��";
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

//��ʼ����
void SpeechManager::startSpeech()
{
	//��һ�ֱ���

	//1����ǩ
	this->speechDraw();
	//2����ʾ�������
	this->speechContest();
	this->showScore();

	//�ڶ��ֱ���
	this->m_Index++;
	//1����ǩ
	this->speechDraw();
	//2������
	this->speechContest();
	//3����ʾ���ս��
	this->showScore();
	//4��������
	this->saveRecord();

	//���ñ���
	this->initSpeech();
	this->creatSpeaker();
	this->loadRecord();
}

//��ǩ
void SpeechManager::speechDraw()
{
	cout << "��" << this->m_Index << "�ֱ�����ѡ�����ڳ�ǩ" << endl;
	cout << "-------------------------------------------" << endl;
	cout << "��ǩ���ݽ�˳������" << endl;
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

//��ί����
void SpeechManager::speechContest()
{
	cout << "-----------------��" << this->m_Index << "�ֱ�����ʽ��ʼ-----------------" << endl;

	multimap<double, int, greater<double>> groupScore;

	int num = 0;//��¼����

	vector<int> v_Src;
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}

	//����ÿһ��ѡ��
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;

		//��ί���
		deque<double> d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;    //600-1000����
			d.push_back(score);
		}
		//ȥ����߷ֺ���ͷ�
		sort(d.begin(), d.end(), greater<double>());
		d.pop_back();
		d.pop_front();

		//��ȡ�ֺܷ�ƽ����
		double sum = accumulate(d.begin(), d.end(),0.0f);
		double avg = sum / (double)d.size();

		this->v[*it].m_score[this->m_Index - 1] = avg;

		//6����һ��
		groupScore.insert({ avg,*it });
		if (num % 6 == 0)
		{
			cout << "��" << num / 6 << "С���������" << endl;

			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "��ţ� " << it->second << " ������ " << this->v[it->second].m_name << " �ɼ��� " << this->v[it->second].m_score[this->m_Index - 1]<<endl;
			}

			//ȡǰ����
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

//��ʾ�������
void SpeechManager::showScore()
{
	cout << "-----------------��" << this->m_Index << "�ֱ����Ľ����������-----------------" << endl;

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
		cout << "ѡ�ֱ�ţ� " << *it << " ������ " << this->v[*it].m_name << " �÷֣� " << this->v[*it].m_score[this->m_Index-1] << endl;
	}
	
	cout << endl;

	system("pause");
	system("cls");

	this->show_view();
}

//�����¼
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

	cout << "��¼�ѱ���!" << endl;
	this->fileEmpty = false;
}

//���ؼ�¼
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

	//�ļ���Ϊ��
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


//��ʾ�����¼
void SpeechManager::showRecord()
{

	if (this->fileEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		for (map<int, vector<string>>::iterator it = this->m_Record.begin(); it != this->m_Record.end(); it++)
		{
			cout << "��" << it->first << "�� " <<
				" �ھ���� " << it->second[0] << " �÷֣�" << it->second[1] <<
				" �Ǿ���� " << it->second[2] << " �÷�: " << it->second[3] <<
				" ������� " << it->second[4] << " �÷�: " << it->second[4] << endl;
		}
		
	}

	system("pause");
	system("cls");

	this->show_view();
}

//��ռ�¼
void SpeechManager::clearRecord()
{
	cout << "ȷ�����? " << endl;
	cout << "1��ȷ�� " << endl;
	cout << "2������ " << endl;

	int select;
	cin >> select;

	if (select == 1)
	{
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
		//��������е����� 
		this->initSpeech();
		this->creatSpeaker();
		this->loadRecord();

		cout << "��ճɹ�! " << endl;
	}
	system("pause");
	system("cls");
	this->show_view();
}