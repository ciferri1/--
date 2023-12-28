#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <deque>
#include <functional>
#include <numeric>
#include <fstream>
#include "speaker.h"

using namespace std;

class SpeechManager
{
public:
	SpeechManager();

	//��ʾ�˵�
	void show_view();

	//�˳�����
	void exitSystem();

	//��ʼ������
	void initSpeech();

	//��ʼ��ѡ��
	void creatSpeaker();

	//��ʼ����
	void startSpeech();

	//��ǩ
	void speechDraw();

	//��ί����
	void speechContest();

	//��ʾ�������
	void showScore();

	//�����¼
	void saveRecord();

	//���ؼ�¼
	void loadRecord();

	//��ʾ�����¼
	void showRecord();

	//��ռ�¼
	void clearRecord();

	~SpeechManager();
	



	//��Ա����
	vector<int> v1;//����ѡ��
	vector<int> v2;//��һ�ֽ���
	vector<int> winner;//ǰ����
	map<int,speaker> v;//��ű�źͶ�Ӧ��ѡ������
	map<int, vector<string>> m_Record;//�����¼

	int m_Index;     //��������
	bool fileEmpty;
};
