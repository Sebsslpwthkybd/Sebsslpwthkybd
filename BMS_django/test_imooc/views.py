from django.shortcuts import render
from django.http import HttpResponse


# Create your views here.

def is_even(request, num):
    if num % 2 != 0:
        html = """  <html>
                        <body>
                            <h1>%s不是偶数</h1>
                        </body>
                    </html>""" % num
    else:
        html = """  <html>
                        <body>
                            <h1>%s是偶数</h1>
                        </body>
                    </html>""" % num

    return HttpResponse(html)
