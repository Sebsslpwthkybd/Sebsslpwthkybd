# coding:utf-8
from test_imooc import views
from django.urls import path


urlpatterns = [
    path('<int:num>/', views.is_even, name='is_even')
]