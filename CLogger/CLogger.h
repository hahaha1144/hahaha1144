#pragma once
#define _CRT_SECURE_NO_WARNINGS             //����4996����
#define  ContentSize  100									//vector�еĴ洢��								
#define _Delay 2000                                         //��ʱ2000����

#include<iostream>
#include <fstream>
#include <windows.h>
#include <thread>
#include<ctime>
#include <chrono>
#include <iomanip>
#include <string>
#include <sstream>
#include <queue>
#include <mutex>

class CLogger
{
public:
	static CLogger &Instance()
	{
		static CLogger instance;
		return instance;
	}
	void SetLogFilePath(const std::string &szFileName);									//���ô��ļ�
	friend CLogger& operator<<(CLogger &out, const std::string &szContent);
	
private:
	CLogger();
	~CLogger();
    std::string GetFormatTime();
	void OutLogFile();			//������ļ�

private:
    std::mutex m_mut;
    std::queue<std::string> m_QueueContainer;             //��������
    std::string m_szFileContent;			                       
    std::fstream m_fs;
};