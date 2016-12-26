import urllib
import urllib2
import sys
import re


def getPage(url):
    request = urllib2.Request(url)
    response = urllib2.urlopen(request)
    return response.read()

url = 'http://www.chinanews.com/'
result = getPage(url)

f = file(sys.argv[1], 'w+')
f.write(result)
f.close()
