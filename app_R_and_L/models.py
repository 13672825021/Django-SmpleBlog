from django.db import models
from django.contrib import admin
# Create your models here.

#创建User类，存放 username、password、email三个字段
class User(models.Model):
    userID=models.AutoField(primary_key=True)
    username=models.CharField(max_length=50)
    password=models.CharField(max_length=50)
    email=models.EmailField()
    userImageName=models.CharField(max_length=100)

#然后同步数据库
#makemigrations:在该app下建立 migrations目录，并记录下你所有的关于modes.py的改动
#migrate:执行migrate，这时候才真的把作用到数据库文件，产生对应的表

class UserAdmin(admin.ModelAdmin):
    list_display=('username','password','email')

class Comment(models.Model):
    commentID=models.AutoField(primary_key=True)
    user=models.ForeignKey(User, on_delete=models.CASCADE)
    comment=models.CharField(max_length=1000)

class Blog(models.Model):
    blogID = models.AutoField(primary_key=True)
    author=models.ForeignKey(User,on_delete=models.CASCADE)
    title=models.CharField(max_length=40)
    content=models.CharField(max_length=5000)
    external_file_name=models.CharField(max_length=100)
    publish_time=models.DateField(auto_now = True )
    agree=models.IntegerField(default= 0)
    oppose=models.IntegerField(default= 0)

admin.site.register(User,UserAdmin)