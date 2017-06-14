// konsument_producent_projektDlg.h : header file
//

#pragma once
#include "afxwin.h"


// Ckonsument_producent_projektDlg dialog
class Ckonsument_producent_projektDlg : public CDialog
{
// Construction
public:
	Ckonsument_producent_projektDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_KONSUMENT_PRODUCENT_PROJEKT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_OknoCzasProdukcji;
	CEdit m_OknoCzasKonsumpcji;
	CEdit m_OknoProdukcji;
	CEdit m_OknoKonsumpcji;
	CEdit m_OknoIloscWBuforze;
	CEdit m_OknoBufora;
	CButton m_pn_Producent;
	CButton m_pn_Konsument;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnEnChangeEdit6();
	afx_msg void OnEnChangeEdit5();
protected:
	static UINT Producent(void* pParametr);
	static UINT Konsument(void* pParametr);	
};
