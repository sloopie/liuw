# -*- coding: UTF-8 -*-
'''
Created on 2009-5-6

@author: liuw
'''
import wx
import subprocess
import email
import os, sys,StringIO,datetime,time
import mypop
from wx.lib.mixins.listctrl import ListCtrlAutoWidthMixin

STORE_PATH = 'c:\\pymail'

class AutoWidthListCtrl(wx.ListCtrl, ListCtrlAutoWidthMixin):
    def __init__(self, parent):
        wx.ListCtrl.__init__(self, parent, -1, style=wx.LC_REPORT,size=(250,300))
        ListCtrlAutoWidthMixin.__init__(self)

class MainFrame(wx.Frame):
    def __init__(self,parent,id):
        wx.Frame.__init__(self,parent,id,u"POP3收取邮件 - liuw",size=(400,300))
                
        #定义整体布局，整体上就是一个大的panel，然后装了上下两个小panel   
        panel = wx.Panel(self,-1)
        self.upanel = wx.Panel(panel,-1, style=wx.BORDER_SUNKEN,size=(150,150))
        self.dpanel = wx.Panel(panel,-1, style=wx.BORDER_SUNKEN)

        uvbox = wx.BoxSizer(wx.VERTICAL)
        
        hbox1 = wx.BoxSizer(wx.HORIZONTAL)
        st1 = wx.StaticText(self.upanel, -1, u'服务器')
        hbox1.Add(st1, 0, wx.RIGHT, 8)
        self.serveraddr = wx.TextCtrl(self.upanel, -1)
        hbox1.Add(self.serveraddr, 1)      
        uvbox.Add(hbox1, 0, wx.EXPAND | wx.LEFT | wx.RIGHT | wx.TOP, 10)
        
        hbox2 = wx.BoxSizer(wx.HORIZONTAL)
        st2 = wx.StaticText(self.upanel, -1, u'用户名')
        hbox2.Add(st2, 0, wx.RIGHT, 8)
        self.user = wx.TextCtrl(self.upanel, -1)
        hbox2.Add(self.user, 1)      
        uvbox.Add(hbox2, 0, wx.EXPAND | wx.LEFT | wx.RIGHT | wx.TOP, 10)        

        hbox3 = wx.BoxSizer(wx.HORIZONTAL)
        st3 = wx.StaticText(self.upanel, -1, u'密   码')
        hbox3.Add(st3, 0, wx.RIGHT, 8)
        self.pswd = wx.TextCtrl(self.upanel, -1)
        hbox3.Add(self.pswd, 1)      
        uvbox.Add(hbox3, 0, wx.EXPAND | wx.LEFT | wx.RIGHT | wx.TOP, 10)

        uvbox.Add((-1, 10))

        hbox4 = wx.BoxSizer(wx.HORIZONTAL)
        btn1 = wx.Button(self.upanel, -1, u'收取', size=(70, 30))
        hbox4.Add(btn1, 0)
        btn2 = wx.Button(self.upanel, -1, u'删除', size=(70, 30))
        hbox4.Add(btn2, 0, wx.LEFT | wx.BOTTOM, 5)
        btn3 = wx.Button(self.upanel, -1, u'关闭', size=(70, 30))
        hbox4.Add(btn3, 0, wx.LEFT | wx.BOTTOM , 5)
        uvbox.Add(hbox4, 0, wx.ALIGN_RIGHT | wx.RIGHT, 10)

        self.Bind(wx.EVT_BUTTON, self.rcvmail, btn1)
        self.Bind(wx.EVT_BUTTON, self.delmail, btn2)
        self.Bind(wx.EVT_BUTTON, self.frmclose, btn3)
            

        self.upanel.SetSizer(uvbox)

        mailbox = wx.BoxSizer(wx.HORIZONTAL)
        self.list = AutoWidthListCtrl(self.dpanel)
        self.list.InsertColumn(0, u'发件人', width=100)
        self.list.InsertColumn(1, u'标题', width=90)
        self.list.InsertColumn(2, u'时间', 60)

        self.list.Bind(wx.EVT_LIST_ITEM_SELECTED, self.optSelected, self.list)
        self.list.Bind(wx.EVT_LEFT_DCLICK, self.dClick, self.list)
  
        mailbox.Add(self.list, 1, wx.EXPAND | wx.ALL, 0)
        self.dpanel.SetSizer(mailbox)
        
        #整体布局
        vbox = wx.BoxSizer(wx.VERTICAL)
        vbox.Add(self.upanel, 0, wx.EXPAND | wx.ALL, 0)
        vbox.Add(self.dpanel, 1, wx.EXPAND | wx.ALL, 0)
        
        panel.SetSizer(vbox)
        self.Centre()
        self.Show(True)

    def delmail(self, event):
        try:
            index = self.currentItem
            host = self.serveraddr.Value
            username = self.user.Value
            password = self.pswd.Value

            if not (host and username and password):
                return

            pp = mypop.POP3(host)
            pp.user(username)
            pp.pass_(password)
            pp.dele(index+1)
            os.system('del '+STORE_PATH+'\\email*.eml')
            mailtotal = pp.stat()[0]
            for i in range(mailtotal):
                down = pp.retr(i+1)
                filename = STORE_PATH + "\\email"+str(i)+".eml"
                self.writeOnefile(filename, down[1])
            pp.quit()
        except:
            pass
            self.showMailList()
##        try:
##            index = self.currentItem
##            try:
##                cmd = 'del '+STORE_PATH+'\\email'+str(index)+'.eml'
####                os.system('del '+STORE_PATH+'\\email'+str(index)+'.eml')
##                subprocess.Popen(cmd, shell=True)
##                self.showMailList()
##            except:
##                pass
##        except:
##            pass


    def frmclose(self, event):
        self.Close()
            
    #收取邮件
    def rcvmail(self, event):
        # pop3服务器地址
        host = self.serveraddr.Value
        username = self.user.Value
        password = self.pswd.Value

        if not (host and username and password):
            return

        pp = mypop.POP3(host)
        pp.user(username)
        pp.pass_(password)
        mailtotal = pp.stat()[0]
        for i in range(mailtotal):
            down = pp.retr(i+1)
            filename = STORE_PATH + "\\email"+str(i)+".eml"
            self.writeOnefile(filename, down[1])
        pp.quit()
        
        #前面是处理收取的，收取完毕都存放在一个文件夹下面，然后调用showMailList方法来展示这些邮件
        self.showMailList()
    
    #收取单一邮件
    def writeOnefile(self,filename,mailinfo):
        newfile = open(filename,"w")
        line_list = []
        j=0
        for line in mailinfo:
            line_list.insert(j,line)
            j+=1
        line_list = [line+'\n' for line in line_list]
        newfile.writelines(line_list)
        
    #邮件的列表展示
    def showMailList(self):
        self.list.DeleteAllItems()
        self.currentItem = 0
        
        filedec = STORE_PATH
        mllist = []
        for i in os.listdir(filedec):
            flname = filedec+"\\"+i
            fp = open(flname, "r")
            msg = email.message_from_file(fp)
            
            #获得标题
            subject = msg.get("Subject")
            h = email.Header.Header(subject)
            dh = email.Header.decode_header(h)
            subject = dh[0][0]
            
            #邮件发送者
            senderx = email.utils.parseaddr(msg.get("From"))[1]

            #邮件发送时间
            datex = msg.get("Date")
            datewww = time.mktime(email.Utils.parsedate(datex))
            finaldt = time.strftime("%Y.%m.%d %H:%M:%S",time.gmtime(datewww))
            
            tupleone = (senderx,subject,finaldt)
            mllist.append(tupleone)

        for i in mllist:
            index = self.list.InsertStringItem(sys.maxint, i[0])
            self.list.SetStringItem(index, 1, i[1])
            self.list.SetStringItem(index, 2, i[2])
            
    
    def optSelected(self,event):
        self.currentItem = event.m_itemIndex
        
    def dClick(self, event):
        index = self.currentItem
        filename = STORE_PATH + '\\email' + str(index) + '.eml'
        subprocess.Popen(filename, shell=True)
        
               
if __name__ == "__main__":
    import os
    os.system('md '+STORE_PATH)
    app = wx.PySimpleApp()
    frame = MainFrame(None,-1)
    frame.Show()
    app.SetTopWindow(frame)
    app.MainLoop()
