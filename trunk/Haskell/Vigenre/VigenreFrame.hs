-- file: VigenreFrame.hs
-- author: LIU Wei liuw@liuw.name
{- demonstrates the use of a simple menu, statusbar, and dialog -}
module Main (main)
    where

import Graphics.UI.WX
import Graphics.UI.WXCore
import Vigenre

main :: IO ()
main
  = start gui

gui :: IO ()
gui = do 
  -- the application frame
  f <- frame         [text := "Vigenre Encryption", resizeable := False]
  p <- panel f []
  label1 <- staticText p [text := "Enter your message: "]
  label2 <- staticText p [text := "Enter your key: "]
  label3 <- staticText p [text := "Output: "]
  inputArea <- textCtrl p [enabled := True]
  keyArea <- textEntry p [enabled := True]
  outputArea <- textCtrl p [enabled := True]
  encryptButton <- button p [text := "Encrypt", on command := doEncrypt inputArea keyArea outputArea]
  decryptButton <- button p [text := "Decrypt", on command := doDecrypt inputArea keyArea outputArea]
  set f [layout := 
                container p $
                margin 10 $ column 1 
                           [
                            widget label1, 
                            minsize (sz 300 120) $ widget inputArea, 
                            widget label2, 
                            widget keyArea, 
                            widget label3, 
                            minsize (sz 300 120) $ widget outputArea, 
                            glue, 
                            hfill $ row 1 
                                      [
                                       widget encryptButton, glue, widget decryptButton
                                      ]
                           ]
        ]

  -- create file menu  
  file   <- menuPane      [text := "&File"]
  quit   <- menuQuit file [help := "Quit", on command := close f]

  -- create Help menu
  hlp    <- menuHelp      []
  about  <- menuAbout hlp [help := "About"]

  -- create statusbar field
  status <- statusField   [text := "Author: LIU Wei"]

  set f [
       clientSize := sz 300 400, 
       statusBar := [status],
       menuBar   := [file,hlp], 
       on (menu about) := infoDialog f "About" "Vigenre Encryption\n\nDeveloped by LIU Wei\nliuw@liuw.name\n\nwith Haskell and wxHaskell"
      ]

  return ()

doEncrypt i k o = do
  msg <- get i text
  key <- get k text
  let result = encrypt msg key
  set o [text := result]

doDecrypt i k o = do
  msg <- get i text
  key <- get k text
  let result = decrypt msg key
  set o [text := result]
