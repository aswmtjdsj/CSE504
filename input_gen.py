#!/bin/bash/python
import sys, os
import struct

def num(s):
    try:
        return int(s)
    except ValueError:
        return float(s)

def gogogo():
    n = int(raw_input("input event number: "))
    opt = raw_input("manually(M)(default)? automatically(A)? ")
    event_list = {}
    if opt == 'M':
        m = int(raw_input("param number: "))
        for i in range(n):
            pass
    else :
        for i in range(n):
            name = raw_input("event name: ")
            m = int(raw_input("param number: "))
            pas = [num(raw_input("param {0}: ".format(j))) for j in range(m)]
            event_list['name'] = name
            event_list['params'] = pas
        print event_list

    file_name = raw_input("expected test file name: (default: xxx.i) ")
    if len(file_name) < 1 or file_name.count('.') > 1 or (file_name.count('.i') == 1 and len(file_name) <= 2):
        raise Exception("IllegalFileName")

    if file_name.count('.') < 1:
        file_name += '.i'

    f = open(file_name, 'wb')

    contents = ''
    contents += event_list['name']
    for j in event_list['params']:
        if isinstance(j, int):
            contents += (chr(j) + '\0' + '\0' + '\0')
        elif isinstance(j, float):
            temp = hex(struct.unpack('!i',struct.pack('!f',j))[0])
            print temp
            temp = temp[2:]
            temp = temp.zfill(8)
            contents += chr(int(temp[:2:], 16))
            contents += chr(int(temp[2:4:], 16))
            contents += chr(int(temp[4:6:], 16))
            contents += chr(int(temp[6::], 16))

    print contents
    print >> f, contents
    f.close()

if __name__ == '__main__':
    gogogo()

