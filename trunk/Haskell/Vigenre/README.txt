Vigenre Encryption 简介

本软件使用 Haskell 语言编写核心算法，wxHaskell 编写界面。
Vigenre.hs 为算法实现，VigenreFrame.hs 为界面实现。

使用方法是按照软件的提示，把明文、密钥输入到对应的文本框中，然后点 Encrypt 进行加密，或者点 Decrypt 进行解密。现在本软件仅支持对大写字母进行操作，输入的小写字母都会自动转化成为大写字母，对标点符号没有提供支持。也就是说，输入的文本只能是英文字母。

使用的时候，请把 VigenreFrame.ex_ 改名为 VigenreFrame.exe，并保证和 wxc-msw2.6.4-0.10.3.dll 放在同一文件夹下，这样才可以执行。

06信安2
200632530055
刘炜
