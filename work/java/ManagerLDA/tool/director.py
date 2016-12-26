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


def extract_url(indexURL):
    soup = BeautifulSoup(open(indexURL))

    url_set = []

    for link in soup.find_all('a'):
        shtml = link.get('href')
        shtml = str(shtml)
        if shtml.endswith("shtml"):
            if shtml.startswith("http://www.chinanews.com/"):
                if "kong" not in shtml:
                    if "shipin" not in shtml:
                        if "/" + str(year) + "/" + str(month) in shtml:
                            url_set.append(shtml)

    return url_set


def read_html(indexURL, directory):
    url_set = extract_url(indexURL)
    for index in range(len(url_set)):
        title, content = read_news(url_set[index])
        if len(title) == 0 or len(content) == 0:
            continue
        content = str(content)
        filename = directory + "/" + title + ".txt"
        f = file(filename, 'w+')
        # print ("saving to %s" % filename)
        f.write(content)
        f.close()



def read_news(url):

    print (url)
    req = urllib2.Request(url)
    try:
        response = urllib2.urlopen(req, timeout=1)
        page = response.read()
    except Exception, e:
        title = ""
        content = ""
        return title, content

    soup = BeautifulSoup(page)

    if soup.title is None:
        title = ""
        content = ""
        return title, content

    title = soup.title.string

    title = str(title)

    content = ""

    news = soup.find_all('p')

    for text in news:
        segmentation = text.get_text()
        content += segmentation

    return title, content

sys.argv = list(sys.argv)
sys.argv.append("url")
sys.argv.append("keyword")

url = np.loadtxt("url", dtype=str)
keyword = np.loadtxt("keyword", dtype=str)

length = len(keyword)
for x in range(length):
    web_page = url[x]
    directory = keyword[x]
    os.system("wget " + web_page + " -O " + directory +"/index.html")
    print (x)
    print ("dealing the topic : %s " % keyword[x])
    read_html(directory + "/" + "index.html", directory)
