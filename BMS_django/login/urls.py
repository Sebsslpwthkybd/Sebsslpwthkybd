# coding:utf-8
from login import views
from django.urls import path


urlpatterns = [
    path('', views.login, name='home')
]
