//////////////////////////////////////////////////////////////////////////
//
//	OpenFile.h
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//				宽字符文件读取类
//	返回值为0，正常返回，其他为非正常
//
//
//////////////////////////////////////////////////////////////////////////


#pragma once




class COpenFile
{
public:
	COpenFile();
	~COpenFile();

private:
	CString m_LastError;

public:
	CString &GetLastError(){	return m_LastError;	}

	//测试一个文件是否存在，参数为文件路径
	UINT TestFileStatus( CString &strFilePath );

	//参数1：文件路径。参数2：读取方式。参数3：返回参数，读取出来的信息
	UINT OpenFileForRead( CString &strFilePath , UINT mode , CString &strFileText );

	//参数1：文件路径。参数2：保存方式。参数3：要保存的信息
	UINT OpenFileForSave( CString &strFilePath , UINT mode , CString &strFileText );
};
