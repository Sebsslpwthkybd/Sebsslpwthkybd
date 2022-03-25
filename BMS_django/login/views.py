from django.contrib.auth.models import AbstractUser
from django.shortcuts import render
from django.http import HttpResponse, HttpResponseRedirect


def login(request):
    if request.method == 'POST':
        return HttpResponseRedirect("/customer/")
    return render(request, template_name='login/login.html')

class User(AbstractUser):
    s
# Create your views here.
