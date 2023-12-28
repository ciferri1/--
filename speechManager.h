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

	//显示菜单
	void show_view();

	//退出程序
	void exitSystem();

	//初始化属性
	void initSpeech();

	//初始化选手
	void creatSpeaker();

	//开始比赛
	void startSpeech();

	//抽签
	void speechDraw();

	//评委评分
	void speechContest();

	//显示晋级结果
	void showScore();

	//保存记录
	void saveRecord();

	//加载记录
	void loadRecord();

	//显示往届记录
	void showRecord();

	//清空记录
	void clearRecord();

	~SpeechManager();
	



	//成员属性
	vector<int> v1;//比赛选手
	vector<int> v2;//第一轮晋级
	vector<int> winner;//前三名
	map<int,speaker> v;//存放编号和对应的选手名字
	map<int, vector<string>> m_Record;//往届记录

	int m_Index;     //比赛场次
	bool fileEmpty;
};
