# coding:utf-8
from branch_management_system import views
from django.urls import path


urlpatterns = [
    path('branch_operating/', views.branch_operating, name='branch_operating')
]
