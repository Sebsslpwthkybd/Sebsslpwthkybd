# coding:utf-8
from django.shortcuts import render


class Customer(object):
    def __init__(self, customer_name, customer_tel, customer_address, contact_name, contact_tel, contact_email, relationship):
        self.customer_name = customer_name
        self.customer_tel = customer_tel
        self.customer_address = customer_address
        self.contact_name = contact_name
        self.contact_tel = contact_tel
        self.contact_email = contact_email
        self.relationship = relationship


def customer(request):
    person = Customer('sebastian', '111', 'home', 'dad', '222', '12345@qq.com', 'father')
    return render(request, template_name='customer/customer.html', context={
        'customer_name': person.customer_name,
        'customer_tel': person.customer_tel,
        'customer_address': person.customer_address,
        'contact_name': person.contact_name,
        'contact_tel': person.contact_tel,
        'contact_email': person.contact_email,
        'relationship': person.relationship
    })

# Create your views here.


