import sys

f = file(sys.argv[1])
url = file(sys.argv[2], 'w+')
keyword = file(sys.argv[3], 'w+')

while True:
    content = f.readline()
    if len(content) == 0:
        break

    content = str(content)
    content = content.replace(" ", "")
    content = content.replace("<li>", "")
    content = content.replace("</li>", "")
    content = content.replace("</a>", "")
    content = content.replace("<ahref=", "")
    content = content.replace("\"", " ")
    content = content.replace(">", " ")
    content = content.strip()
    x = content.split(' ')
    url.write(x[0] + "\n")
    keyword.write(x[2] + "\n")
f.close()
url.close()
keyword.close()