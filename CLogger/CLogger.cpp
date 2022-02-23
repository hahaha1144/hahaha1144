#include "CLogger.h"

 CLogger::CLogger()
 {
     std::thread WriteLogFile(&CLogger::OutLogFile , this);
     WriteLogFile.detach();
 }

 CLogger::~CLogger()
 {
	 m_fs.close();
 }

 std::string CLogger::GetFormatTime()
 {
	 DWORD id = ::GetCurrentThreadId();						//获取线程ID
	 DWORD dwError = ::GetLastError();

	 auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
     std::ostringstream oss;
     oss << "[" << std::put_time(std::localtime(&time), "%Y-%m-%d %X") << " " << id << "]";

	 return oss.str() ;
 }

void CLogger::OutLogFile()
{
    std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now();

    while (1)
    {
        std::unique_lock<std::mutex> lock(m_mut);
        while (m_QueueContainer.size() > 0)
        {
            m_szFileContent += m_QueueContainer.front();
            m_QueueContainer.pop();              
        }
        lock.unlock();
      
        if (m_szFileContent.size() >= ContentSize || (std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - lastTime).count() >= _Delay && !m_szFileContent.empty()))
        {      
            m_fs << m_szFileContent;
            m_fs.flush();
            lastTime = std::chrono::steady_clock::now();
            m_szFileContent.clear();        
        }
        else
        {                        
            std::this_thread::sleep_for(std::chrono::milliseconds(40));      
        }
    }
}

void CLogger::SetLogFilePath(const std::string &szFileName)
{
	m_fs.open(szFileName, std::ios::app);
	if (!m_fs)
	{
        std::cout << "no" << "\n";
	}  
}

CLogger& operator<<(CLogger &out, const std::string &szContent)
{
    std::unique_lock<std::mutex> lock(out.m_mut);
    std::string szLog = out.GetFormatTime() + szContent + "\n";
    out.m_QueueContainer.push(szLog);
    std::cout << szLog;
    std::cout.flush();
           
	return out;
}

