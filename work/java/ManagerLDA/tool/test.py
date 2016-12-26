import numpy as np
import datetime
import sys
import os
from bs4 import BeautifulSoup
import urllib2

reload(sys)
sys.setdefaultencoding("utf-8")

time = datetime.datetime.today()
year = time.year
month = time.month
day = time.day

url = "http://www.chinanews.com/gj/2016/12-19/8097815.shtml"

print (url)
req = urllib2.Request(url)
response = urllib2.urlopen(req)
page = response.read()

print page
raw_input()

soup = BeautifulSoup(page)

print soup.find_all('title')

title = soup.title.string


title = str(title)

content = ""
news = soup.find_all('p')
for text in news:
    segmentation = text.get_text()
    content += segmentation

print title
raw_input()
print content
