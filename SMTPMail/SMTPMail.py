# -*- coding: GBK -*-
'''
Created on 2009-5-15

@author: liuw
'''
import wx
import mysmtp
import email.MIMEMultipart
import email.MIMEText
import email.MIMEBase
import os.path

class NewMailFrame(wx.Frame):
    def __init__(self,parent,id):

        wx.Frame.__init__(self,parent,id,u'SMTP发送邮件 - liuw',size=(400,500))
        panel = wx.Panel(self,-1)
        vbox = wx.BoxSizer(wx.VERTICAL)
        
        hbox1 = wx.BoxSizer(wx.HORIZONTAL)
        st1 = wx.StaticText(panel, -1, u'收件人')
        hbox1.Add(st1, 0, wx.RIGHT, 8)
        self.rcvman = wx.TextCtrl(panel, -1)
        hbox1.Add(self.rcvman, 1)
        vbox.Add(hbox1, 0, wx.EXPAND | wx.LEFT | wx.RIGHT | wx.TOP, 10)

        hbox2 = wx.BoxSizer(wx.HORIZONTAL)
        st2 = wx.StaticText(panel, -1, u'主   题')
        hbox2.Add(st2, 0, wx.RIGHT, 8)
        self.theme = wx.TextCtrl(panel, -1)
        hbox2.Add(self.theme, 1)
        vbox.Add(hbox2, 0, wx.EXPAND | wx.LEFT | wx.RIGHT | wx.TOP, 10)

        hbox6 = wx.BoxSizer(wx.HORIZONTAL)
        st6 = wx.StaticText(panel, -1, u'发信人地址')
        hbox6.Add(st6, 0, wx.RIGHT, 8)
        self.senderaddr = wx.TextCtrl(panel, -1)
        hbox6.Add(self.senderaddr, 1)
        vbox.Add(hbox6, 0, wx.EXPAND | wx.LEFT | wx.RIGHT | wx.TOP, 10)

        hbox3 = wx.BoxSizer(wx.HORIZONTAL)
        st3 = wx.StaticText(panel, -1, u'服务器')
        hbox3.Add(st3, 0, wx.RIGHT, 8)
        self.serveraddr = wx.TextCtrl(panel, -1)
        hbox3.Add(self.serveraddr, 1)
        vbox.Add(hbox3, 0, wx.EXPAND | wx.LEFT | wx.RIGHT | wx.TOP, 10)

        hbox4 = wx.BoxSizer(wx.HORIZONTAL)
        st4 = wx.StaticText(panel, -1, u'用户名')
        hbox4.Add(st4, 0, wx.RIGHT, 8)
        self.user = wx.TextCtrl(panel, -1)
        hbox4.Add(self.user, 1)
        vbox.Add(hbox4, 0, wx.EXPAND | wx.LEFT | wx.RIGHT | wx.TOP, 10)

        hbox5 = wx.BoxSizer(wx.HORIZONTAL)
        st5 = wx.StaticText(panel, -1, u'密   码')
        hbox5.Add(st5, 0, wx.RIGHT, 8)
        self.pswd = wx.TextCtrl(panel, -1)
        hbox5.Add(self.pswd, 1)
        vbox.Add(hbox5, 0, wx.EXPAND | wx.LEFT | wx.RIGHT | wx.TOP, 10)
         
        vbox.Add((-1, 10))
         
        hbox7 = wx.BoxSizer(wx.HORIZONTAL)
        self.content = wx.TextCtrl(panel, -1, style=wx.TE_MULTILINE)
        hbox7.Add(self.content, 1, wx.EXPAND)
        vbox.Add(hbox7, 1, wx.LEFT | wx.RIGHT | wx.EXPAND, 10)
         
        vbox.Add((-1, 25))

         
        hbox8 = wx.BoxSizer(wx.HORIZONTAL)
        btn1 = wx.Button(panel, -1, u'发送', size=(70, 30))
        hbox8.Add(btn1, 0)
        btn2 = wx.Button(panel, -1, u'关闭', size=(70, 30))
        hbox8.Add(btn2, 0, wx.LEFT | wx.BOTTOM , 5)
        vbox.Add(hbox8, 0, wx.ALIGN_RIGHT | wx.RIGHT, 10)
         
        self.Bind(wx.EVT_BUTTON, self.sendmail, btn1)
        self.Bind(wx.EVT_BUTTON, self.frmclose, btn2)
      
        panel.SetSizer(vbox)
        self.Centre()
         
    def frmclose(self,event):
        self.Close()
    
    
    def sendmail(self,event):
        username = self.user.Value
        password = self.pswd.Value
        smtpserver = self.serveraddr.Value
        
        sender = self.senderaddr.Value
        
        
        receiver = self.rcvman.Value
        theme = self.theme.Value
        content = self.content.Value

        server = mysmtp.SMTP(smtpserver)
        server.login(username, password)

        main_msg = email.MIMEMultipart.MIMEMultipart()
        text_msg = email.MIMEText.MIMEText(content)
        main_msg.attach(text_msg)
        
        # 设置根容器属性
        main_msg['From'] = sender
        main_msg['To'] = receiver
        main_msg['Subject'] = theme
        main_msg['Date'] = email.Utils.formatdate()
        
        # 得到格式化后的完整文本
        fullText = main_msg.as_string()
        
        # 用smtp发送邮件
        try:
            server.sendmail(sender, receiver, fullText)
            # print "send success"
            # self.Close()
        finally:
            server.quit()

if __name__ == '__main__':
    app = wx.PySimpleApp()
    frame = NewMailFrame(None,-1)
    frame.Show()
    app.MainLoop()

