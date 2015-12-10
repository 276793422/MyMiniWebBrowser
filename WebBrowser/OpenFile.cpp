//////////////////////////////////////////////////////////////////////////
//
//	OpenFile.cpp
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "OpenFile.h"

COpenFile::COpenFile()
{
}

COpenFile::~COpenFile()
{
}

UINT COpenFile::TestFileStatus( CString &strFilePath )
{
	CFile file;
	if ( !file.Open( strFilePath , CFile::modeWrite | CFile::modeRead ) )
	{
		m_LastError = _T("�ļ����ܲ�����");
		return 1;
	}
	m_LastError = _T("�ļ�����");
	file.Close();
	return 0;
}

UINT COpenFile::OpenFileForRead( CString &strFilePath , UINT mode , CString &strFileText )
{
	CFile file;
	if ( !file.Open( strFilePath , mode ) )
	{
		m_LastError = _T("���ļ�ʧ�ܣ��������ļ�����");
		return 1;
	}
	UINT nlong = (UINT)file.GetLength();
	char *szFile = new char[nlong + 1];
	file.Read( szFile , nlong );
	szFile[nlong] = '\0';
	CStringA strA ;
	strA = szFile;
	strFileText = strA;
	file.Close();
	delete szFile;
	m_LastError = _T("");
	return 0;
}


UINT COpenFile::OpenFileForSave( CString &strFilePath , UINT mode , CString &strFileText )
{
	CFile file;
	if ( !file.Open( strFilePath , mode ) )
	{
		m_LastError = _T("���ļ�ʧ�ܣ��������ļ�����");
		return 1;
	}
	CStringA strA;
	strA = strFileText;
	file.Write( strA.GetBuffer() , strA.GetLength() );
	strA.ReleaseBuffer();
	file.Close();
	m_LastError = _T("");
	return 0;
}