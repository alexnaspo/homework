# CS288 Homework 7 - counted as two homework
# Out 6 pm, Mon, 4/15/2013, due 11:59 pm, Sun, 4/27/2013

# Read the skeleton code carefully and try to follow the structure
# You may modify the code but try to stay within the framework.

import libxml2
import sys
import os
import commands
import re

import MySQLdb

from xml.dom.minidom import parse, parseString

# for converting dict to xml
from cStringIO import StringIO
from xml.parsers import expat


def get_elms_for_atr_val(tag, atr, val):
    lst = []
    elms = dom.getElementsByTagName(tag)
    for node in elms:
        if node.childNodes[0].getAttribute(atr) == val:
            lst.append(node)
    return lst


# get all text recursively to the bottom
def get_text(e):
    lst = []
    if e.nodeType in (3, 4):
        if e.data != ' ':
            return [e.data]
    else:
        for x in e.childNodes:
            lst = lst + get_text(x)
    return lst


# replace whitespace chars
def replace_white_space(str):
    p = re.compile(r'\s+')
    new = p.sub(' ', str)  # a lot of \n\t\t\t\t\t\t
    return new.strip()


# replace but these chars including ':'
def replace_non_alpha_numeric(s):
    p = re.compile(r'[^a-zA-Z0-9:-]+')
    #   p = re.compile(r'\W+') # replace whitespace chars
    new = p.sub(' ', s)
    return new.strip()


# convert to xhtml
# use: java -jar tagsoup-1.2.jar --files html_file
def html_to_xml(fn):
    xhtml_file = os.system('java -jar tagsoup-1.2.1.jar --files %s' % (fn))
    fn = fn.replace('.html', '.xhtml')
    # return xhtml_file
    return fn


def extract_values(dm):
    lst = []
    l = get_elms_for_atr_val('tr', 'class', 'lft')
    for x in l:
        item = get_text(x)
        lst.append(item)
    return lst

# mysql> describe most_active;
def insert_to_db(l, tbl):
    db = MySQLdb.connect(host="localhost", user="root", passwd="", db="stocks")
    c = db.cursor()
    c.execute(
        """CREATE TABLE IF NOT EXISTS `%s` (
        symbol varchar(4),
        title varchar(250),
        price varchar(50),
        diff varchar(50),
        perc_diff varchar(50),
        volume varchar(50)
        )""" % (tbl))
    for d in l:
        query = """INSERT INTO `%s` (%s) VALUES('%s','%s','%s','%s','%s','%s');""" % (tbl, ",".join(d.keys()), d['title'], d['symbol'], d['volume'], d['diff'], d['perc_diff'], d['price'])
        print query
        c.execute(query)
        db.commit()
    c.close()
    db.close()
    print "DB function"
   # ............


# show databases;
# show tables;

def to_dict(l):
    keys = ['symbol','title','price','diff','perc_diff','volume']
    d = [dict(zip(keys,x)) for x in l]
    return d


def main():
    html_fn = sys.argv[1]
    fn = html_fn.replace('.html', '')
    xhtml_fn = html_to_xml(html_fn)
    global dom
    dom = parse(xhtml_fn)
    # print dom

    lst = extract_values(dom)
    # print "after EXTRACT"
    lst.pop(0)

    # make sure your mysql server is up and running
    lst = to_dict(lst)
    cursor = insert_to_db(lst, fn)  # fn = table name for mysql

    # l = select_from_db(cursor, fn)  # display the table on the screen

    # make sure the Apache web server is up and running
    # write a PHP script to display the table(s) on your browser

    # return xml
    return True
    # end of main()

if __name__ == "__main__":
    main()

# end of hw7.py
