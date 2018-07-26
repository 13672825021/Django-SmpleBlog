from django.shortcuts import render
from django import forms
from app_R_and_L.models import User
from app_R_and_L.models import Comment
from app_R_and_L.models import Blog
from django.http import HttpResponse
from django.views.decorators.cache import cache_page
from django.http import HttpResponseRedirect
import json
from django.views.decorators.csrf import csrf_exempt
import time
import datetime as d
from django.http import JsonResponse

# Create your views here.
# class UserForm(forms.Form):
#     username=forms.CharField(label='用户名',max_length=50)
#     password=forms.CharField(label='密码',widget=forms.PasswordInput())#设置密码字段
#     email=forms.EmailField(label='邮箱')
#
# class UserForm_login(forms.Form):
#     username=forms.CharField(label='用户名',max_length=50)
#     password=forms.CharField(label='密码',widget=forms.PasswordInput())#设置密码字段
#
# class CommentForm(forms.Form):
#     comment=forms.CharField(label='评论',max_length=1000)

# @cache_page(60*15)#秒数，这里指缓存 15 分钟，不直接写900是为了提高可读性


def index1(request):
    blogs = Blog.objects.all()
    blogintroductionlist = []
    blogtitlelist = []
    publishtime = []
    authorname = []
    external_file_name = []
    for blog in blogs:
        filename = '无'
        if blog.external_file_name != '':
            filename = blog.external_file_name
        external_file_name.append(filename)
        publishtime.append(str(blog.publish_time))
        title = blog.title
        blogtitlelist.append(title)
        content = blog.content
        introduction = content[:40]
        blogintroductionlist.append(introduction)
        author_id = blog.author_id
        author_name = User.objects.get(userID=author_id).username
        authorname.append(author_name)
    return JsonResponse({'blogtitlelist':blogtitlelist,'blogintroductionlist':blogintroductionlist,'authorname':authorname,'publishtime':publishtime})

def index(request):
    blogs = Blog.objects.all()
    blogintroductionlist = []
    blogtitlelist = []
    publishtime = []
    authorname=[]
    external_file_name = []
    for blog in blogs:
        filename = '无'
        if blog.external_file_name != '':
            filename = blog.external_file_name
        external_file_name.append(filename)
        publishtime.append(str(blog.publish_time))
        title = blog.title
        blogtitlelist.append(title)
        content = blog.content
        introduction = content[:40]
        blogintroductionlist.append(introduction)
        author_id=blog.author_id
        author_name=User.objects.get(userID=author_id).username
        authorname.append(author_name)
    return render(request, 'index.html')

def regist(request):
    if request.method=='POST':
        username=request.POST['Username']
        password=request.POST['Password']
        re_password = request.POST['RePassword']
        email = request.POST['Email']
        if re_password!=password:
            return render(request, 'regist.html',{'message':'两次输入的密码不一致！请重新注册'})

        print(username)
        #在User表中创建一个样本
        newuser=User(username=username,password=password,email=email)
        newuser.save()
        return render(request,'r2l.html')
    return render(request,'regist.html',)#就是返回一个注册页面


def login(request):#登录
    if request.method=='POST':
        username = request.POST['Username']
        password = request.POST['Password']
        print(username)
        try:
            user=User.objects.get(username=username,password=password)
            request.session['CurUserId'] = user.userID  #设置session
            request.session['CurUserName'] = username
            print(request.session['CurUserId'])
            return HttpResponseRedirect('/index')
        except:
            message = '用户名或密码错误，(怎么回事你心里没点B数吗？)请重试';
            return render(request, 'login.html', {'message': message,})

    else:#第一次进入注册页面，没提交表单，是GET方式
        print("get")

    return render(request,'login.html',)

def logout(request):
    try:
        del request.session['CurUserId']
        del request.session['CurUserName']
    except KeyError:
        pass
    return HttpResponseRedirect('/index/')

def blogpage(request):
    return render(request, 'blogpage.html', )

def detail(request):
    print("detail...")
    return render(request, 'detail.html', )


def add(request):
    a=request.GET.get('a')
    b=request.GET.get('b')
    c=int(a)+int(b)
    print("here")
    return HttpResponse(str(c))

def personalcenter(request):
    CurUserId=request.session.get('CurUserId', None);
    if CurUserId==None:
        return HttpResponseRedirect('/login/')
    username = request.session['CurUserName']
    portrait_name=User.objects.get(userID=CurUserId).userImageName
    blogs = Blog.objects.filter(author_id=CurUserId)
    blogintroductionlist=[]
    blogtitlelist=[]
    publishtime=[]
    external_file_name=[]
    for blog in blogs:
        filename='无'
        if blog.external_file_name!='':
            filename=blog.external_file_name
        external_file_name.append(filename)
        publishtime.append(str(blog.publish_time))
        title=blog.title
        blogtitlelist.append(title)
        content=blog.content
        introduction=content[:40]
        blogintroductionlist.append(introduction)

    return render(request, 'personalcenter.html',
                  {'username':username,'portrait_name':portrait_name,'blogtitlelist':json.dumps(blogtitlelist),
                  'blogintroductionlist':json.dumps(blogintroductionlist),'publishtime':json.dumps(publishtime),
                   'external_file_name': json.dumps(external_file_name),})

@csrf_exempt
def writeblog(request):
    print(d.datetime.now().strftime("%Y.%m.%d-%H:%M:%S"))
    CurUserId = request.session.get('CurUserId', None);
    if CurUserId == None:
        return HttpResponseRedirect('/login/')
    if request.method=='POST':
        blog_title = request.POST.get('blog_title')
        blog_content = request.POST.get('blog_content')
        if request.COOKIES.get('blog_file_name')==None:
            external_file_name = '无'
        else:
            external_file_name =request.COOKIES['blog_file_name']

        print(blog_title)
        print(blog_content)
        print(external_file_name)
        # 在Blog表中创建一个样本
        CurUser = User.objects.get(userID=CurUserId)
        newblog = Blog(author=CurUser, title=blog_title, content=blog_content,external_file_name=external_file_name)#还没有解决图片和文件的问题
        newblog.save()
        print('here?')
        return HttpResponse('发表成功')
    return render(request, 'writeblog.html')

@csrf_exempt
def uploadblogpic(request):
    if request.method == 'POST':
        file_obj = request.FILES.get('file') #获取文件本体
        newfilename=str(time.time())+'_'+file_obj.name
        import os
        f = open(os.path.join('static','BLOGIMAGES', newfilename), 'wb')#设定把文件上传到服务器对应的路径，这里是/static/FILES
        #print(file_obj,type(file_obj))
        for chunk in file_obj.chunks(): #开始上传/写文件
            f.write(chunk)
        f.close()
        print('文件上传完毕')
        print(newfilename)
        return HttpResponse('/static/BLOGIMAGES/'+newfilename)

@csrf_exempt
def uploadblogfile(request):
    if request.method == 'POST':
        print("comein")
        file_obj = request.FILES.get('file') #获取文件本体
        newfilename=str(time.time())+'_'+file_obj.name
        import os
        f = open(os.path.join('static','FILES', newfilename), 'wb')#设定把文件上传到服务器对应的路径，这里是/static/FILES
        #print(file_obj,type(file_obj))
        for chunk in file_obj.chunks(): #开始上传/写文件
            f.write(chunk)
        f.close()
        print('文件上传完毕')
        print(newfilename)
        response = HttpResponse("附件上传成功")
        response.set_cookie("blog_file_name", newfilename)
        return response

@csrf_exempt
def upload_user_image(request):
    print('views_upload_user_image')
    CurUserId = request.session.get('CurUserId', None);
    if request.method == 'POST':
        file_obj = request.FILES.get('file') #获取文件本体
        newfilename=str(time.time())+'_'+file_obj.name
        import os
        f = open(os.path.join('static','USERIMAGES', newfilename), 'wb')#设定把文件上传到服务器对应的路径，这里是/static/FILES
        #print(file_obj,type(file_obj))
        for chunk in file_obj.chunks(): #开始上传/写文件
            f.write(chunk)
        f.close()
        print('头像上传完毕')
        print(newfilename)
        if CurUserId!=None:
            User.objects.filter(userID=CurUserId).update(userImageName=newfilename)
        return HttpResponse("头像上传成功")





#
# def login(request):#登录
#     if request.method=='POST':
#         print("postttt")
#         userform=UserForm_login(request.POST)#得到表单里的信息
#         if userform.is_valid():#这个括号又漏掉了
#             username=userform.cleaned_data['username']
#             password=userform.cleaned_data['password']
#             print(username)
#             try:
#                 user=User.objects.get(username=username,password=password)
#                 request.session['CurUserId'] = user.userID
#                 print(request.session['CurUserId'])
#                 return HttpResponseRedirect('/index')
#             except:
#                 userform = UserForm_login
#                 message = '用户名或密码错误，怎么回事你心里没点B数吗？\n请重试';
#                 return render(request, 'login.html', {'message': message, 'userform': userform})
#
#     else:#第一次进入注册页面，没提交表单，是GET方式
#         print("get")
#         userform=UserForm_login()
#
#     return render(request,'login.html',{'userform':userform})



# def regist(request):
#     if request.method=='POST':
#         userform=UserForm(request.POST)
#         if userform.is_valid():
#             username=userform.cleaned_data['username']
#             password=userform.cleaned_data['password']
#             email=userform.cleaned_data['email']
#             print(username)
#             #在User表中创建一个样本
#             newuser=User(username=username,password=password,email=email)
#             newuser.save()
#             return render(request,'r2l.html')
#
#     else:       #非POST方式访问网站，一般是第一次进入网站，以GET方式，所以给他展示注册页面
#         userform=UserForm()         #少打个括号，debug了很久,上面的else对齐错了，也debug了很久
#
#     return render(request,'regist.html',{'userform':userform})#就是返回一个注册表单给访客填写

#
# def index(request):
#     if request.method=='POST':
#        commentform=CommentForm(request.POST)
#        if commentform.is_valid():
#            print("here")
#            comment=commentform.cleaned_data['comment']
#            userid = request.session['CurUserId']
#            CurUser=User.objects.get(userID=userid)
#            newcomment=Comment(user=CurUser,comment=comment)
#            newcomment.save()
#            commentform=CommentForm()
#
#            return render(request, 'index.html', {'commentform': commentform,'submit_message':'评论提交成功',})
#     else:
#         commentform=CommentForm()
#
#
#     Number=1002
#     Word='haha'
#     List=['List[0]','List[1]']
#     Dict={'site':'Site','author':'zhongzhh'};
#     return render(request,'index.html',{
#         'commentform':commentform,
#         'List':json.dumps(List),'Dict':json.dumps(Dict),'Word':json.dumps(Word),'Number':json.dumps(Number)
#     })