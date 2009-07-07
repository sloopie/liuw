// TrafficButton.cpp : implementation file
//

#include "stdafx.h"
#include "TrafficButton.h"
#include "MemDC.h"
#include <math.h>
#include "NT.h"

#ifndef _WIN32_IE
	#define _WIN32_IE 0x0500
#endif
#include <commctrl.h>
#include <intshcut.h>
#include <wininet.h> 


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// TrafficButton

TrafficButton::TrafficButton()
{
	brushInitalized = FALSE;
	gridxstartpos = 0;
	gridystartpos = 0;
	gridxresolution		=	GRIDXRESOLUTION;
	gridyresolution		=	GRIDYRESOLUTION;
	gridscrollxspeed	=	GRIDSCROLLXSPEED;
	gridscrollyspeed	=	GRIDSCROLLYSPEED; 
	plotgranularity		=	PLOTGRANULATRITY;
	netupdatespeed		=	NETUPDATESPEED;
	gridupdatespeed		=	GRIDUPDATESPEED;
}

TrafficButton::~TrafficButton()
{
	delete [] TrafficStats;
}


BEGIN_MESSAGE_MAP(TrafficButton, CButton)
	//{{AFX_MSG_MAP(TrafficButton)
	ON_WM_TIMER()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TrafficButton message handlers



void TrafficButton::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CButton::PreSubclassWindow();

	// make sure we are an owner draw button
	ModifyStyle( 0 , BS_OWNERDRAW );

	this->GetWindowRect(&TrafficDrawRectangle);
	this->GetWindowRect(&TrafficDrawUpdateRectangle);
	ScreenToClient(&TrafficDrawUpdateRectangle);
	ScreenToClient(&TrafficDrawRectangle);

	TGSize.cx = TrafficDrawRectangle.right - TrafficDrawRectangle.left;
	TGSize.cy = TrafficDrawRectangle.bottom - TrafficDrawRectangle.top;

	initalized = FALSE;
	MaxTrafficAmount = 0.0;

	smallFont.CreateFont(-10,0,0,0,FW_THIN, FALSE, FALSE, FALSE, DEFAULT_CHARSET,OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH, "Arial");

	red		= RGB(255,125,125);
	green	= RGB(125,255,125);
	cyan	= RGB(0,255,255);
	darkblue= RGB(0,0,75);
	darkgray= RGB(50,50,50);
	white	= RGB(255,255,255);
	black	= RGB(0,0,0);
	lightgreen	= RGB(156,255,156);
	darkgreen	= RGB(32,64,32);

	greenbrush.CreateSolidBrush(green);
	redbrush.CreateSolidBrush(red);

	GridPen.CreatePen(PS_SOLID ,1 , darkgreen);

	GetWindowRect(&TrafficDrawRectangle);
	ScreenToClient(&TrafficDrawRectangle);

	
	TGSize.cx = TrafficDrawRectangle.right - TrafficDrawRectangle.left;
	TGSize.cy = TrafficDrawRectangle.bottom - TrafficDrawRectangle.top;
	
	
	TrafficEntries = TGSize.cx / plotgranularity;
	TrafficStats = new TRAFFICENTRY[TrafficEntries+1];
	
	for(DWORD x=0; x<TrafficEntries; x++)
	{
		TrafficStats[x].connected = TRUE;//FALSE;
		TrafficStats[x].value	= 0.0;//(float)x * (float)TrafficEntries*0.05;//;10.0 + 10.0*(sin(5.0*(float)x*3.14/180.0));
	}
	
	MaxTrafficAmount = 0.0;

	CRgn rectRgn, ellRgn, finalRgn;
	rectRgn.CreateRectRgn(0,0,TGSize.cx, TGSize.cy);
	ShapeWNDRegion.CreateRectRgn(0,0,TGSize.cx, TGSize.cy);;
	ShapeDCRegion.CreateRectRgn(0,0,TGSize.cx, TGSize.cy);;

	int x1,x2,y1,y2,xe,ye,xs,ys;
	int xof, yof;
	int r;
	xs = TGSize.cx;
	ys = TGSize.cy;
	x1 = 0;
	y1 = 0;
	x2 = xs;
	y2 = ys;
	xe = 5;//Radius of edge
	ye = 5;//Radius of edge
	xof = (int)( (float)xs*0.0);
	yof = (int)( (float)ys*0.0);
	r = ellRgn.CreateRoundRectRgn(x1,y1,x2,y2,xe,ye);
	r = ellRgn.OffsetRgn(-xof, -yof);
	r = ShapeWNDRegion.CombineRgn(&rectRgn, &ellRgn,RGN_AND );
	r = ShapeDCRegion.CombineRgn(&rectRgn, &ellRgn,RGN_AND );

	this->SetWindowRgn((HRGN)ShapeWNDRegion, TRUE);
	initalized = TRUE;

	SetTimer(GRIDTIMER,	gridupdatespeed,	0);
	SetTimer(NETTIMER,	netupdatespeed,		0);

}


void TrafficButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default

	ASSERT( lpDrawItemStruct != NULL );

	CDC * pDC   = CDC::FromHandle( lpDrawItemStruct -> hDC );
	int erg = pDC->SelectClipRgn(&ShapeDCRegion);

	CRect rect = lpDrawItemStruct -> rcItem;
	UINT state = lpDrawItemStruct -> itemState;
	UINT nStyle = GetStyle( );

	int nSavedDC = pDC -> SaveDC( );

	// Create the brush for the color bar
	if(brushInitalized == FALSE)
	{
		CBitmap bmp;
		CMemDC *memDC = new CMemDC(pDC);
		
		RECT clipRect;
		memDC->GetClipBox(&clipRect);

		if(clipRect.right - clipRect.left > 1)
		{
			bmp.CreateCompatibleBitmap(memDC,plotgranularity, TGSize.cy);
			CBitmap *pOld = memDC->SelectObject(&bmp);
			
			CSize bmps = bmp.GetBitmapDimension();		
			
			// Need for scaling the color to the size of button
			double factor = 255.0 / (float)TGSize.cy;
			BYTE r,g,b;
			for(int x = 0; x<TGSize.cy; x++)
			{
				g = (BYTE)(255-factor*x);
				r = (BYTE)(factor*x);
				b = (BYTE)64;
				
				memDC->SetPixelV(0,x,RGB(r,g,b));
				memDC->SetPixelV(1,x,RGB(r,g,b));
				
			}
			memDC->SelectObject(pOld);

			colorbrush.CreatePatternBrush(&bmp);	
			brushInitalized = TRUE;
		}

		delete memDC;
	}

	if(initalized == TRUE)
	{
		COLORREF backcolor = GetSysColor(COLOR_BTNFACE);
		
		CBrush brush;
		CMemDC *memDC = new CMemDC(pDC);
		
		RECT clipRect;
		memDC->GetClipBox(&clipRect);
		memDC->FillSolidRect(&clipRect,backcolor);
		
		CFont *oldFont;
		int xp, yp, xx, yy;
		orgBrushOrigin = memDC->GetBrushOrg();
		
		oldFont = memDC->SelectObject(&smallFont);
		
		double scale = (double)TGSize.cy / (double)MaxTrafficAmount;
		
		yp = TrafficDrawRectangle.bottom;
		xp = TrafficDrawRectangle.left;
		
		RECT fillrect;
		
		CString tmp;
		
		// Fill the background
		back = memDC->GetBkColor();
		brush.CreateSolidBrush(darkblue);//back);
		memDC->FillRect(&TrafficDrawRectangle, &brush);

		// draw the grid
		int xgridlines, ygridlines;
		
		xgridlines = TGSize.cx / gridxresolution;
		ygridlines = TGSize.cy / gridyresolution;
		CPen* oldPen = memDC->SelectObject(&GridPen);
		// Create the vertical lines
		for (int x=0; x<= xgridlines; x++)
		{
			memDC->MoveTo(x*gridxresolution + gridxstartpos, 0			);
			memDC->LineTo(x*gridxresolution + gridxstartpos, TGSize.cy	);
		}
		// And the horizontal lines
		for (int y=0; y<= ygridlines; y++)
		{
			memDC->MoveTo(0			, gridystartpos + TGSize.cy - y*gridyresolution - 2);
			memDC->LineTo(TGSize.cx	, gridystartpos + TGSize.cy - y*gridyresolution - 2);
		}

		gridxstartpos += gridscrollxspeed;
		gridystartpos += gridscrollyspeed;
		if(gridxstartpos < 0				) gridxstartpos = gridxresolution;
		if(gridxstartpos > gridxresolution	) gridxstartpos = 0;
		if(gridystartpos < 0				) gridystartpos = gridyresolution;
		if(gridystartpos > gridyresolution	) gridystartpos = 0;


		memDC->SelectObject(oldPen );

		for(DWORD cnt=0; cnt<TrafficEntries; cnt++)
		{
			xx = xp + cnt*plotgranularity;
			double traffic = (double)TrafficStats[cnt].value; 
			yy = yp - (int)((double)TrafficStats[cnt].value * scale);
				
			fillrect.bottom = yp;
			fillrect.top	= yy;
			fillrect.left	= xx;
			fillrect.right	= xx+plotgranularity;
			memDC->SetBrushOrg(xx,yp);
			if(TrafficStats[cnt].value > 0.0) 
			{
				memDC->FillRect(&fillrect, &colorbrush);
				memDC->SetPixelV(xx, yy, cyan);
			}
		
		}
		
		// last print the textual statistic
		tmp.Format("%8.1f",TrafficStats[TrafficEntries-1].value);
		COLORREF textcolor = memDC->GetTextColor();
		int bkmode = memDC->GetBkMode();
		memDC->SetBkMode(TRANSPARENT);
		memDC->SetTextColor(darkblue);
		memDC->TextOut(6,5,AllTraffic);
		memDC->SetTextColor(cyan);
		memDC->TextOut(5,5,AllTraffic); 
		memDC->SetTextColor(textcolor);
		memDC->SetBkMode(bkmode);
		
		memDC->SelectObject(oldFont);
		memDC->SetBrushOrg(orgBrushOrigin.x, orgBrushOrigin.y);
	
		delete memDC;
	}	
	pDC -> RestoreDC( nSavedDC );

}



void TrafficButton::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent == NETTIMER)
	{
	
		double traffic = g_totaltraffic;
		DWORD totaltraffic = g_totaltraffic;
		
		double delta1;
		double divisor = (1000.0/(double)NETUPDATESPEED);
		delta1 = (double)(traffic * divisor) / 1024.0;

		
		for(DWORD x=0; x<TrafficEntries; x++)
		{
			TrafficStats[x].connected = TrafficStats[x+1].connected;
			TrafficStats[x].value	= TrafficStats[x+1].value;
			if(TrafficStats[x].value > MaxTrafficAmount)
				MaxTrafficAmount = TrafficStats[x].value;
		}
		
		if(isOnline == TRUE)
		{
			TrafficStats[TrafficEntries].connected = TRUE;
			TrafficStats[TrafficEntries].value = traffic;
			if(TrafficStats[TrafficEntries].value > MaxTrafficAmount)
				MaxTrafficAmount = TrafficStats[TrafficEntries].value;
		}
		else
		{
			TrafficStats[TrafficEntries].connected = FALSE;
			TrafficStats[TrafficEntries].value = traffic;
			if(TrafficStats[TrafficEntries].value > MaxTrafficAmount)
				MaxTrafficAmount = TrafficStats[TrafficEntries].value;
		}

		double delta2;
		divisor = (1000.0/(double)NETUPDATESPEED);
		delta2 = (double)(MaxTrafficAmount * divisor) / 1024.0;
		AllTraffic.Format("CUR: %.1f KB/SEC   HHG: %.1f KB/SEC",delta1, delta2);
		
	}

	// Force a redraw
	Invalidate(FALSE);

	CButton::OnTimer(nIDEvent);
}

void TrafficButton::SetUpdateSpeed(UINT netspeed, UINT gridspeed)
{
	gridupdatespeed	= gridspeed;
	netupdatespeed	= netspeed;
	KillTimer(GRIDTIMER);
	KillTimer(NETTIMER);
	SetTimer(GRIDTIMER,	gridupdatespeed,	0);
	SetTimer(NETTIMER,	netupdatespeed,		0);
}


void TrafficButton::ClearResult()
{
	MaxTrafficAmount = 0;
	g_totaltraffic = 0;
	for(DWORD x=0; x<TrafficEntries; x++)
		TrafficStats[x].value = 0;
	Invalidate(FALSE);
}