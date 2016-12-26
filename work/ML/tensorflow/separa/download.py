import urllib
import urllib2


def getPage(url):
    request = urllib2.Request(url)
    response = urllib2.urlopen(request)
    return response.read()


url = 'http://www.chinanews.com/cj/2016/12-18/8097420.shtml'
result = getPage(url)

f = file("out.txt", 'w+')
f.write(result)
f.close()

print result