# coding:utf-8
from mall import views
from django.urls import re_path


urlpatterns = [
    re_path(r'^product/(?P<id>\d+)', views.mall, name='mall')
]
