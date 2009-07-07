// TrafficDlg.h : header file
//

#if !defined(AFX_TRAFFICDLG_H__6ADC6CCF_EB0B_408D_BDDC_D159200B87F2__INCLUDED_)
#define AFX_TRAFFICDLG_H__6ADC6CCF_EB0B_408D_BDDC_D159200B87F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTrafficDlg dialog
//#include "NetTraffic.h"
#include "TrafficButton.h"

class CTrafficDlg : public CDialog
{
// Construction
public:
	CTrafficDlg(CWnd* pParent = NULL);	// standard constructor
	
// Dialog Data
	//{{AFX_DATA(CTrafficDlg)
	enum { IDD = IDD_TRAFFIC_DIALOG };
	TrafficButton	m_graph;
	CButton	m_bTop;
	CStatic	m_static_status;
	CListBox	m_list_devices;
	CEdit	m_edit_output;
	CEdit	m_edit_filter;
	CButton	m_bStop;
	CButton	m_bStart;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrafficDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;



	// Generated message map functions
	//{{AFX_MSG(CTrafficDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnStart();
	afx_msg void OnBtnStop();
	afx_msg void OnBtnTop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRAFFICDLG_H__6ADC6CCF_EB0B_408D_BDDC_D159200B87F2__INCLUDED_)
