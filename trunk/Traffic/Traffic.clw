; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTrafficDlg
LastTemplate=CButton
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Traffic.h"

ClassCount=4
Class1=CTrafficApp
Class2=CTrafficDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=TrafficButton
Resource3=IDD_TRAFFIC_DIALOG

[CLS:CTrafficApp]
Type=0
HeaderFile=Traffic.h
ImplementationFile=Traffic.cpp
Filter=N

[CLS:CTrafficDlg]
Type=0
HeaderFile=TrafficDlg.h
ImplementationFile=TrafficDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_STATIC_OUTPUT

[CLS:CAboutDlg]
Type=0
HeaderFile=TrafficDlg.h
ImplementationFile=TrafficDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_TRAFFIC_DIALOG]
Type=1
Class=CTrafficDlg
ControlCount=9
Control1=IDC_STATIC_FILTER,static,1342308352
Control2=IDC_EDIT_FILTER,edit,1350631552
Control3=IDC_BTN_START,button,1342242816
Control4=IDC_BTN_STOP,button,1342242816
Control5=IDC_LIST_DEVICES,listbox,1352728835
Control6=IDC_STATIC_STATUS,static,1342308352
Control7=IDC_STATIC_DEVICES,static,1342308352
Control8=IDC_BTN_TOP,button,1342242816
Control9=IDC_GRAPH,button,1342242816

[CLS:TrafficButton]
Type=0
HeaderFile=TrafficButton.h
ImplementationFile=TrafficButton.cpp
BaseClass=CButton
Filter=W

