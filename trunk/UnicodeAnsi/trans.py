# -*- coding: UTF-8 -*-
#!/usr/bin/python

# liuw
# @ LOIS @ CAS

import sys
import getopt
from trans_table import unicode_to_ansi, ansi_to_unicode

# options here
OUT = sys.stdout
IN = sys.stdin
ERR = sys.stderr
CStyle = False
Table = unicode_to_ansi
UpperCase = False
ContinuallyMode = False
InteractiveMode = False
OneLineMode = False

def usage():
    print 'Usage: %s [OPTION] ...' % (sys.argv[0],)
    print
    print 'Here are the options: '
    print '-i, --input <FILE>       Specify an input file. Contents in this FILE should '
    print '                         be like:'
    print '                         E3A0E000    // Comment'
    print '                         Comment is automatically ignored.'
    print '-o, --output <FILE>      Specify a output file. Contents in this FILE are '
    print '                         formatted according to options.'
    print '-e, --err <FILE>         Specify an error log file.'
    print '-c, --c-style            Format output as c style hex string.'
    print '-r, --reverse            If specified, translate ANSI code to Unicode. By '
    print '                         default, translate Unicode to ANSI code.'
    print '-u, --upper              Upper case hex string. It not specified, output lower '
    print '                         case hex string.'
    print '-h, --help               This stuff...'
    print '-t, --interactive        Interactive translation.'
    print '-n, --one-line           DO NOT add carriage return. Not available '
    print '                         in interactive mode and c-style mode.'
    print
    print 'liuw'
    print '@ LOIS @ CAS'

def do_it():
    global OUT, IN, ERR, CStyle, Table, UpperCase
    line_num = 0
    got_error = False

    for l in IN.read().split('\n'):
        l = l[0:8] # here we allow comments following opcode
        if len(l) == 0:
            break
        line_num = line_num + 1
        high_word = l[0:4].lower()
        low_word = l[4:].lower()
        xcode = ''
        try:
            xcode = Table[low_word] + Table[high_word]
            if UpperCase is True:
                xcode = xcode.upper()
        except KeyError:
            ERR.write('[-] line %d: %s\n' % (line_num, l))
            ERR.write('[-] Instruction map not found, modify your shellcode\n')
            xcode = 'ERROR: ' + l
            got_error = True
            break
        if CStyle is True:
            if (line_num-1) % 4 == 0:
                OUT.write('"')
            nxcode = ''
            for i in xrange(0, len(xcode), 2):
                nxcode = nxcode + '\\x' + xcode[i:i+2]
            OUT.write(nxcode)
            if line_num % 4 == 0:
                OUT.write('"\n')
        else:
            OUT.write(xcode)
            if OneLineMode is False:
                OUT.write('\n')
    if CStyle is True and line_num % 4 != 0 and got_error is False:
        OUT.write('"')
    IN.close()
    OUT.close()
    ERR.close()
    print '[+] Done'


def process_interactive():
    global OUT, IN, ERR, CStyle, Table, UpperCase
    OUT.write('Input `exit\' to exit\n')
    arg = raw_input('Input: ')
    while arg != 'exit':
        xcode = ''
        try:
            if len(arg) != 4 and len(arg) != 8:
                raise KeyError
            high_word = arg[0:4].lower()
            xcode = Table[high_word]
            if len(arg) == 8:
                low_word = arg[4:].lower()
                xcode = Table[low_word] + xcode
            if UpperCase is True:
                xcode = xcode.upper()
            if CStyle is True:
##                OUT.write('"')
                nxcode = ''
                for i in xrange(0, len(xcode), 2):
                    nxcode = nxcode + '\\x' + xcode[i:i+2]
                OUT.write(nxcode)
##                OUT.write('"')
            else:
                OUT.write(xcode)
            OUT.write('\n')
        except KeyError:
            ERR.write('[-] Instruction map not found, modify your shellcode\n')
        arg = raw_input('Input: ')
    sys.exit(0)

if __name__ == '__main__':
    try:
        opts, args = getopt.getopt(sys.argv[1:], 'i:o:e:m:hcrutn', [
                               'input=', 'output=', 'err=',
                               'help', 'c-style', 'reverse',
                               'upper', 'immediate=', 'continually',
                               'one-line'])
    except getopt.GetoptError:
        usage()
        sys.exit(0)
##    global OUT, IN, ERR, CStyle, Table, UpperCase
    for o, a in opts:
        if o in ('-h', '--help'):
            usage()
            sys.exit(0)
        if o in ('-o', '--output'):
            OUT = a
        if o in ('-e', '--err'):
            ERR = a
        if o in ('-i', '--input'):
            IN = a
        if o in ('-c', '--c-style'):
            CStyle = True
        if o in ('-r', '--reverse'):
            Table = ansi_to_unicode
        if o in ('-u', '--upper'):
            UpperCase = True
        if o in ('-t', '--continually'):
            InteractiveMode = True
        if o in ('-n', '--one-line'):
            OneLineMode = True

    if IN is not sys.stdin:
        IN = open(IN, 'r')
    if OUT is not sys.stdout:
        OUT = open(OUT, 'w')
    if ERR is not sys.stderr:
        ERR = open(ERR, 'w')
    if InteractiveMode is True:
        process_interactive()
    else:
        do_it()

