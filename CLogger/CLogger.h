#pragma once
#define _CRT_SECURE_NO_WARNINGS             //消除4996错误
#define  ContentSize  100									//vector中的存储数								
#define _Delay 2000                                         //延时2000毫秒

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
	void SetLogFilePath(const std::string &szFileName);									//设置打开文件
	friend CLogger& operator<<(CLogger &out, const std::string &szContent);
	
private:
	CLogger();
	~CLogger();
    std::string GetFormatTime();
	void OutLogFile();			//输出到文件

private:
    std::mutex m_mut;
    std::queue<std::string> m_QueueContainer;             //队列容器
    std::string m_szFileContent;			                       
    std::fstream m_fs;
};