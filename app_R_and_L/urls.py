from django.conf.urls import url,include
from django.contrib import admin
from app_R_and_L import views
admin.autodiscover()
#上面这个函数遍历INSTALLED_APPS配置，并且寻找相关的admin.py文件。
# 如果在指定的app目录下找到admin.py，它就执行其中的代码。

urlpatterns=[
    url(r'^index/$',views.index),
    url(r'^$',views.login),
    url(r'^login/$',views.login),
    url(r'logout/$',views.logout),
    url(r'^regist/$',views.regist),
    url(r'add/$',views.add),
    url(r'^personalcenter/$',views.personalcenter),
    url(r'^writeblog/$', views.writeblog),
    url(r'^uploadblogpic/$', views.uploadblogpic),
    url(r'^uploadblogfile/$', views.uploadblogfile),
    url(r'^blogpage/$', views.blogpage),
    url(r'^upload_user_image/$', views.upload_user_image),
    url(r'^index1/$', views.index1),
    url(r'^detail/$', views.detail),
]