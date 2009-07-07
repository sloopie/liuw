
#if !defined(AFX_MFTRAFFICBUTTON_H__9F2EABAA_E8C7_48B4_94A5_EC279905F50C__INCLUDED_)
#define AFX_MFTRAFFICBUTTON_H__9F2EABAA_E8C7_48B4_94A5_EC279905F50C__INCLUDED_

#include "Globals.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TrafficButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// TrafficButton window

//VOID CALLBACK InterfaceChanged(int newInterface);

//typedef FARPROC INTERFACECHANCEDPROC;
typedef VOID (CALLBACK* INTERFACECHANCEDPROC)(int);

class TrafficButton : public CButton
{
// Construction
public:
	TrafficButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TrafficButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:

	void SetUpdateSpeed(UINT netspeed, UINT gridspeed);
	void ClearResult();
	virtual ~TrafficButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(TrafficButton)
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:

	CFont	smallFont;
	CBrush	colorbrush;

	COLORREF red, green, back, cyan, darkblue, darkgray, white, black, lightgreen, darkgreen;
	CBitmap	colorbrushbmp;
	CPen	GridPen;
	CSize	TGSize;

	CBrush	greenbrush;
	CBrush	redbrush;
	CPoint	orgBrushOrigin; 

	RECT	TrafficDrawRectangle;
	RECT	TrafficDrawUpdateRectangle;


	CString AllTraffic;

	DWORD	TrafficEntries;

	BOOL	initalized;
	BOOL	isOnline;
	BOOL	brushInitalized;

	CRgn	ShapeWNDRegion;
	CRgn	ShapeDCRegion;

	double	MaxTrafficAmount;

	TRAFFICENTRY* TrafficStats;

	int gridxstartpos;		
	int gridystartpos;
	int plotgranularity;		

	// Public modification variables
public:
	int gridxresolution;		// The size of grid raster
	int gridyresolution;
	int gridscrollxspeed;		// Scroll speed of the grid
	int gridscrollyspeed; 
	int netupdatespeed;			// Should be set via SetUpdateSpeet method
	int gridupdatespeed;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFTRAFFICBUTTON_H__9F2EABAA_E8C7_48B4_94A5_EC279905F50C__INCLUDED_)
