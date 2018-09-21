#pragma once
#include "resource.h"

// CPage3_SetAddressCAN �Ի���

class CPage3_SetAddressCAN : public CDialogEx
{
	DECLARE_DYNAMIC(CPage3_SetAddressCAN)

public:
	CPage3_SetAddressCAN(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPage3_SetAddressCAN();

// �Ի�������
	enum { IDD = IDD_DIALOG3 };
	void setStateRect(CRect &rect);//����group�߿�
	void setSendFun(SENDCOMMAND fun){ m_pPrintfFun = fun; }//���÷��ͺ���ָ��

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();


private:
	SENDCOMMAND m_pPrintfFun = NULL; //���ͺ���
	CWnd* m_pParent;
public:
	afx_msg void OnBnClickedBtnOpenCan();
	afx_msg void OnBnClickedBtnCloseCan();
};