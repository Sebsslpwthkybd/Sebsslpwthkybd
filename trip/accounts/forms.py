import re

from django import forms
from django.contrib.auth import authenticate, login
from django.utils.timezone import now

from accounts.models import User


class LoginForm(forms.Form):
    """ 登录表单 """
    username = forms.CharField(label='用户名',
                               max_length=100,
                               required=False,
                               help_text='使用帮助',
                               initial='admin')
    password = forms.CharField(label='密码', max_length=200, min_length=6,
                               widget=forms.PasswordInput)

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        # 当前登录的用户
        self.user = None

    def clean_username(self):
        """ 验证用户名 hook 钩子函数 """
        username = self.cleaned_data['username']
        pattern = r'^1[0-9]{10}$'
        if not re.search(pattern, username):
            raise forms.ValidationError('手机号%s输入不正确',
                                        code='invalid_phone',
                                        params=(username, ))
        return username

    def clean(self):
        data = super().clean()
        print(data)
        # 如果单个字段有错误，直接返回，不执行后面的验证
        if self.errors:
            return
        username = data.get('username', None)
        password = data.get('password', None)
        user = authenticate(username=username, password=password)
        if user is None:
            raise forms.ValidationError('用户名或者是密码不正确')
        else:
            if not user.is_active:
                raise forms.ValidationError('该用户已经被禁用')
        self.user = user
        return data

    def do_login(self, request):
        """ 执行用户登录 """
        user = self.user
        # 调用登录
        login(request, user)
        # 修改最后登录的时间
        user.last_login = now()
        user.save()
        # TODO 保存登录历史
        return user