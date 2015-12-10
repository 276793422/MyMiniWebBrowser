//////////////////////////////////////////////////////////////////////////
//
//	OpenFile.h
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//				���ַ��ļ���ȡ��
//	����ֵΪ0���������أ�����Ϊ������
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

	//����һ���ļ��Ƿ���ڣ�����Ϊ�ļ�·��
	UINT TestFileStatus( CString &strFilePath );

	//����1���ļ�·��������2����ȡ��ʽ������3�����ز�������ȡ��������Ϣ
	UINT OpenFileForRead( CString &strFilePath , UINT mode , CString &strFileText );

	//����1���ļ�·��������2�����淽ʽ������3��Ҫ�������Ϣ
	UINT OpenFileForSave( CString &strFilePath , UINT mode , CString &strFileText );
};
