#include "dali-common.h"
#include <stdarg.h>
#include <sstream>
#include <app.h>

void (*DaliCheckFailCB)(void*)=NULL;

char* getAppDataPath()
{
	char* pPath = NULL;
	pPath = app_get_data_path();
	return pPath;
}
string getResourceFullPath(string strFile)
{
	string strActualPathOne="";
	char* pchPath = getAppDataPath();
	if(pchPath == NULL || strlen(pchPath) == 0)
	{
		if(pchPath != NULL)
		{
			free(pchPath);
			pchPath = NULL;
		}		
		return strActualPathOne;
	}
	strActualPathOne = string( pchPath ) + strFile;
	free(pchPath);
	pchPath = NULL;
	return strActualPathOne;
}

bool getSystemInfoFeature(char* pszKey, char* strModuleName, int nLine)
{
	bool bValue=false;
	if ( NULL == pszKey )
	{
		//FPRINTF("[Line : %d][%s] Key is NULL\\n", nLine, strModuleName);
		DaliLog::PrintV(LOG_INFO, strModuleName, "[Line: %d] Key is NULL.", nLine);
		return false;
	}
	int nRet = system_info_get_platform_bool (pszKey, &bValue);
	
	if ( nRet != SYSTEM_INFO_ERROR_NONE )
	{
		//FPRINTF("[Line : %d][%s] Unable to get system info by system_info_get_platform_bool() with key = '%s'\\n", nLine, strModuleName, pszKey);
		DaliLog::PrintV(LOG_INFO, strModuleName, "[Line: %d] Unable to get system info by system_info_get_platform_bool() with key = '%s'", nLine, pszKey);
		return false;
	}

	if ( bValue )
	{
		//FPRINTF("[I][%s][Line: %d] Feature '%s' is supported.\\n",strModuleName, nLine, pszKey);
		DaliLog::PrintV(LOG_INFO, strModuleName, "[Line: %d]Feature '%s' is supported.", nLine, pszKey);
	}
	
	return bValue;
}

// DaliLog class implemented below
DaliLog::DaliLog()
{
}
DaliLog::~DaliLog()
{
}

string DaliLog::mstrModuleName="";
string DaliLog::mstrTcName="";

void DaliLog::Print(ELogType eLogType, string strModuleName, string strLogMessage)
{
	string strLogType = "I";
	FILE *fpLog;
	fpLog = fopen(ERR_LOG,"a");
	if(!fpLog)
		return;
	
	if(eLogType	== LOG_ERROR)
	{
		strLogType = "E";
		fprintf(fpLog,"[%s][%s]%s", strLogType.c_str(), strModuleName.c_str(), strLogMessage.c_str());
	}
	else if(eLogType	== LOG_RESULT)
	{
		strLogType = "R";
		fprintf(fpLog,"[%s][%s]%s", strLogType.c_str(), strModuleName.c_str(), strLogMessage.c_str());
	}
	else
	{
		fprintf(fpLog,"[%s][%s]%s\\n", strLogType.c_str(), strModuleName.c_str(), strLogMessage.c_str());
	}
	cout << "\n[" << strLogType << strModuleName << "] " << strLogMessage << endl;
	
	fclose(fpLog);
	
	strLogType.clear();
}

void DaliLog::Print(ELogType eLogType, string strModuleName, string strLogMessage, int nLine)
{
	std::ostringstream ossLogWithLinePos;
	//ossLogWithLinePos << " , at [ LINE: " << nLine << " ]";
	strLogMessage += ossLogWithLinePos.str();
	//Print(eLogType, strModuleName, strLogMessage);
	
	string strLogType = "I";
	FILE *fpLog;
	fpLog = fopen(ERR_LOG,"a");
	if(!fpLog)
		return;
	
	if(eLogType	== LOG_ERROR)
	{
		strLogType = "E";
		fprintf(fpLog,"[%s][%s][Line: %d]%s", strLogType.c_str(), strModuleName.c_str(), nLine, strLogMessage.c_str());
	}
	else if(eLogType	== LOG_RESULT)
	{
		strLogType = "R";
		fprintf(fpLog,"[%s][%s][Line: %d]%s", strLogType.c_str(), strModuleName.c_str(), nLine, strLogMessage.c_str());
	}
	else
	{
		fprintf(fpLog,"[%s][%s][Line: %d]%s\\n", strLogType.c_str(), strModuleName.c_str(), nLine, strLogMessage.c_str());
	}
		
	fclose(fpLog);
}

void DaliLog::Print(ELogType eLogType, string strModuleName, string strLogMessage, string strFuncName)
{
	std::ostringstream ossLogWithLinePos;
	ossLogWithLinePos << " , at [ FUNCTION: " << strFuncName << " ]";
	strLogMessage += ossLogWithLinePos.str();
	//Print(eLogType, strModuleName, strLogMessage);
	
	string strLogType = "I";
	FILE *fpLog;
	fpLog = fopen(ERR_LOG,"a");
	if(!fpLog)
		return;
	
	if(eLogType	== LOG_ERROR)
	{
		strLogType = "E";
		fprintf(fpLog,"[%s][%s][Function: %s]%s", strLogType.c_str(), strModuleName.c_str(), strFuncName.c_str(), strLogMessage.c_str());
	}
	else if(eLogType	== LOG_RESULT)
	{
		strLogType = "R";
		fprintf(fpLog,"[%s][%s][Function: %s]%s", strLogType.c_str(), strModuleName.c_str(), strFuncName.c_str(), strLogMessage.c_str());
	}
	else
	{
		fprintf(fpLog,"[%s][%s][Function: %s]%s\\n", strLogType.c_str(), strModuleName.c_str(), strFuncName.c_str(), strLogMessage.c_str());
	}
	
	fclose(fpLog);
}

void DaliLog::PrintV(ELogType eLogType, string strModuleName, string strLogMessage, ...)
{
	string strLogType = "I", strLog = "";
	char strvLog[512];
	va_list arg;
	
	FILE *fpLog;
	fpLog = fopen(ERR_LOG,"a");
	if(!fpLog)
		return;
	
	va_start(arg, strLogMessage);
	if(eLogType	== LOG_ERROR)
	{
		strLogType = "E";
		strLog = "\n[" + strLogType + "][" + strModuleName + "] " + strLogMessage;
		vsnprintf(strvLog, 512, strLog.c_str(), arg ); 
		fprintf(fpLog,"%s", strvLog);
	}
	else if(eLogType	== LOG_RESULT)
	{
		strLogType = "R";
		strLog = "\n[" + strLogType + "][" + strModuleName + "] " + strLogMessage;
		vsnprintf(strvLog, 512, strLog.c_str(), arg );   
		fprintf(fpLog,"%s", strvLog);
	}
	else
	{
		strLog = "\n[" + strLogType + "][" + strModuleName + "] " + strLogMessage;
		vsnprintf(strvLog, 512, strLog.c_str(), arg );    
		fprintf(fpLog,"%s\\n", strvLog);
	}
       
	fclose(fpLog);    
    va_end(arg);
    
	strLogType.clear();
	strLog.clear();
}

void DaliLog::PrintPass(string strModuleName, string strTcName)
{
	string strMessage(strTcName);
	strMessage += " is passed";
	//Print(LOG_RESULT, strModuleName, strMessage);
	FILE *fpLog;
	fpLog = fopen(ERR_LOG,"a");
	if(!fpLog)
		return;
		
	fprintf(fpLog,"[R][%s]%s", strModuleName.c_str(), strMessage.c_str());
	fclose(fpLog);
	strMessage.clear();
}
void TcResult()
{
	FILE *fres = fopen(TC_RESULT,"w");
	fprintf(fres, "%d", test_return_value);
	fclose(fres);
}
void DaliLog::PrintPass()
{
	string strMessage(DaliLog::mstrTcName);
	strMessage += " is passed";
	//Print(LOG_RESULT, strModuleName, strMessage);
	
	TcResult(); //print tc result into "/tmp/tcresult"
	
	FILE *fpLog;
	fpLog = fopen(ERR_LOG,"a");
	if(!fpLog)
		return;
		
	fprintf(fpLog,"[R][%s]%s", DaliLog::mstrModuleName.c_str(), strMessage.c_str());
	fclose(fpLog);
	strMessage.clear();
}

void DaliLog::PrintExecStarted(string strModuleName, string strTcName)
{
	DaliLog::mstrModuleName=strModuleName;
	DaliLog::mstrTcName=strTcName;
	string strMessage = "";
	//strMessage = "Executing TC - " + strTcName;
	strMessage = strTcName+ " is executing";
	Print(LOG_INFO, strModuleName, strMessage);
	strMessage.clear();
}
void DaliLog::PrintMgs(string strMgs)
{
	string strMessage(strMgs);
	FILE *fpLog;
	
	fpLog = fopen(ERR_LOG,"a");
	if(!fpLog)
		return;
		
	fprintf(fpLog,"%s\n", strMessage.c_str());
	fclose(fpLog);
	strMessage.clear();
}
