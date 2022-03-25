# coding:utf-8
from customer_management_system import views
from django.urls import path


urlpatterns = [
    path('1/', views.customer, name='customer')
]