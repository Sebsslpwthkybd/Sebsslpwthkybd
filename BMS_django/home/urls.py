# coding:utf-8
from home import views
from django.urls import path


urlpatterns = [
    path('', views.home, name='home')
]
